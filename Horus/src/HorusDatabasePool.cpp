/// -----------------------------------------------------------------------------
///
/// \file HorusDatabasePool.cpp
///
/// \copyright Copyright (c) 2016-2017 Daniel Caujolle-Bert <daniel.caujolle-bert@unibas.ch>
/// \brief Horus, a Cassette Logger
/// \author Daniel Caujolle-Bert <daniel.caujolle-bert@unibas.ch>
///
/// \license
/// All rights reserved. This program and the accompanying materials
/// are made available under the terms of the GNU Public License v2.0
/// which accompanies this distribution, and is available at
/// http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
///
/// This file is part of Horus Logger.
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
///
///

#include "../HorusMain.h"

namespace Horus
{

DEFINE_EVENT_TYPE(wxEVT_HORUS_CASSETTE); ///< Event that receiver may handle
DEFINE_EVENT_TYPE(wxEVT_HORUS_DATABASEPOOL); ///< Event that receiver may handle


HorusDatabasePool::HorusDatabasePool(wxWindow *parent) : m_parent(parent), m_id(wxNewId()), m_initialized(false), m_cassette(NULL)
{
    //ctor

    m_dbPath = wxStandardPaths::Get().GetUserDataDir() + wxFILE_SEP_PATH + wxT("Databases");
    m_dbBackupPath = m_dbPath + wxFILE_SEP_PATH + wxT("Backups");

    if (! wxFileName::DirExists(m_dbPath))
        wxFileName::Mkdir(m_dbPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);

    if (! wxFileName::DirExists(m_dbBackupPath))
        wxFileName::Mkdir(m_dbBackupPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
}

HorusDatabasePool::~HorusDatabasePool()
{
    //dtor
    if (m_dbCassette.IsOpen())
        m_dbCassette.Close();

    if (m_dbOperators.IsOpen())
        m_dbOperators.Close();

    wxSQLite3Database::ShutdownSQLite();
}

bool HorusDatabasePool::IsOK()
{
    return m_initialized;
}

bool HorusDatabasePool::Initialize(HorusCassette *cassette)
{
    if (m_initialized)
        return false;

    m_cassette = cassette;

    wxSQLite3Database::InitializeSQLite();

    m_initialized = _initializeDatabases();

    return m_initialized;
}

wxString const HorusDatabasePool::GetBackupPath()
{
    return m_dbBackupPath;
}

wxWindowID HorusDatabasePool::GetId()
{
    return m_id;
}

bool HorusDatabasePool::ReloadData(wxArrayOperator &operators, HorusDatabaseEventRestore *receiver)
{
    if (!m_initialized)
        return false;

    return _reloadCassette() && _reloadOperators(operators) && _reloadEvents(receiver);
}

bool HorusDatabasePool::UpdateCartridge(HorusCartridge *cartridge)
{
    if (! m_initialized)
        return false;

    return _updateCartridgeData(cartridge);
}

bool HorusDatabasePool::AddOperator(const wxString &name, const wxString &uuid)
{
    if (! m_initialized)
        return false;

    return _insertOperator(name, uuid);
}

bool HorusDatabasePool::UpdateOperator(const wxString &name, const wxString &uuid)
{
    if (! m_initialized)
        return false;

    return _updateOperator(name, uuid);
}

bool HorusDatabasePool::DeleteOperator(const wxString &uuid)
{
    if (! m_initialized)
        return false;

    return _deleteOperator(uuid);
}

bool HorusDatabasePool::SetCassetteOperator(const wxString &uuid)
{
    if (! m_initialized)
        return false;

    return _updateCassetteOperator(uuid);
}

wxString const HorusDatabasePool::GetCassetteOperator()
{
    if (! m_initialized)
        return wxEmptyString;

    return _getCassetteOperator();
}

bool HorusDatabasePool::LogCassetteEvent(time_t ts, const wxString &op, const wxString &message)
{
    if (! m_initialized)
        return false;

    return _logCassetteEvent(ts, op, message);
}

bool HorusDatabasePool::SetCassetteDocked(bool docked)
{
    if (! m_initialized)
        return false;

    return _setCassetteDocked(docked);
}

bool HorusDatabasePool::SetCassetteRedocked()
{
    if (! m_initialized)
        return false;

    return _setCassetteRedocked();
}

bool HorusDatabasePool::GetCassetteDocked()
{
    if (! m_initialized)
        return false;

    return _getCassetteDocked();
}

bool HorusDatabasePool::GetCassetteDockTimeStamp(time_t &ts)
{
    if (! m_initialized)
        return false;

    return _getCassetteDockTimeStamp(ts);
}

bool HorusDatabasePool::SetKeepOnStage(bool keep)
{
    if (! m_initialized)
        return false;

    return _setKeepOnStage(keep);
}

bool HorusDatabasePool::GetKeepOnStage()
{
    if (! m_initialized)
        return false;

    return _getKeepOnStage();
}

bool HorusDatabasePool::_setKeepOnStage(bool keep)
{
    bool        ok = true;
    wxString    sqlUpdate = wxString(wxT("UPDATE informations SET keepOnStage=?;"));

    try
    {
        wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(sqlUpdate);

        updateStatement.BindBool(1, keep);

        int ret = updateStatement.ExecuteUpdate();

        //wxLogStatus(updateStatement.GetSQL());
        //wxLogStatus(wxT("CassetteKeepOnStage Updated: ") + wxString::Format(wxT("%d"), ret));

        if (ret == 0)
        {
            wxMessageBox(wxT("Cassette DB update failed: unable to update keepOnStage value"), wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }
    return ok;
}

bool HorusDatabasePool::_getKeepOnStage()
{
    bool        keep = false;
    wxString    selcmd = wxString(wxT("SELECT i.keepOnStage FROM informations i;"));

    try
    {
        wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);
        wxSQLite3ResultSet q = stmt.ExecuteQuery();

        if (q.NextRow())
        {
            keep = q.GetBool(0);
        }
    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Cassette DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
    }

    return keep;
}

bool HorusDatabasePool::_rotateCassette()
{
    bool                ok = true;
    int                 state = 0;
    int                 timestamp = 0;
    wxString            op = wxEmptyString;
    wxString            text = wxEmptyString;
    wxDateTime          dt = wxDateTime::Now();
    wxString            backupName = wxT("cassette_") + hUtils::GetTimeStampString(dt, true) + wxT(".db3");
    wxSQLite3Database   backupDB;

    try
    {
        //
        // Backup the Cassette database
        //
        m_dbCassette.Backup(m_dbBackupPath + wxFILE_SEP_PATH + backupName);

        state = 1;

        //
        // Open the backup database
        //
        backupDB.Open(m_dbBackupPath + wxFILE_SEP_PATH + backupName);

        state = 2;

        //
        // Define funeral date and unset docked flag in backup database
        //
        {
            wxString  sqlUpdate = wxString(wxT("UPDATE informations SET funeral=?, docked=?;"));
            wxSQLite3Statement updateStatement = backupDB.PrepareStatement(sqlUpdate);

            updateStatement.Bind(1, static_cast<int>(dt.GetTicks()));
            updateStatement.BindBool(2, false);

            int ret = updateStatement.ExecuteUpdate();

            //wxLogStatus(updateStatement.GetSQL());
            //wxLogStatus(wxT("CassetteFunerals Updated: ") + wxString::Format(wxT("%d"), ret));

            // Remote last event
            {
                int idx = backupDB.ExecuteScalar("SELECT COUNT(*) FROM events;");

                state = 3;

                // event log is non empty
                if (idx)
                {
                    wxString delcmd = wxString(wxT("DELETE FROM events WHERE idx=?;"));
                    wxSQLite3Statement updateStatement = backupDB.PrepareStatement(delcmd);

                    updateStatement.Bind(1, idx - 1);

                    updateStatement.ExecuteUpdate();
                }

            }

            backupDB.Close();

            _sendBackupEvent(m_dbBackupPath + wxFILE_SEP_PATH + backupName);
        }

        state = 4;

        //
        // Change dockTS in cassette database (reset to 0), will be changed further.
        //
        {
            wxString sqlUpdate = wxString(wxT("UPDATE informations SET dockTS=?;"));

            wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(sqlUpdate);

            updateStatement.Bind(1, 0);

            int ret = updateStatement.ExecuteUpdate();

            //wxLogStatus(updateStatement.GetSQL());
            //wxLogStatus(wxT("CassetteDockTS Updated: ") + wxString::Format(wxT("%d"), ret));
        }

        state = 5;

        //
        // Flush events in cassette database, except last event (and change its index to 0)
        //
        {

            // get max count
            int idx = m_dbCassette.ExecuteScalar("SELECT COUNT(*) FROM events;");

            // event log is non empty
            if (idx)
            {
                // store value of last

                wxString selcmd = wxString(wxT("SELECT e.idx, e.timestamp, e.operator, e.text FROM events e WHERE e.idx=?;"));

                wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);

                stmt.Bind(1, idx - 1);

                wxSQLite3ResultSet q = stmt.ExecuteQuery();

                state = 6;

                if (! q.NextRow())
                {
                    throw wxSQLite3Exception(WXSQLITE_ERROR, wxString(wxT("Invalid row index")));
                }

                timestamp = q.GetInt(1);
                op = q.GetString(2);
                text = q.GetString(3);
            }
        }

        //
        // erase all events
        {
            wxString delcmd = wxString(wxT("DELETE FROM events;"));
            wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(delcmd);
            updateStatement.ExecuteUpdate();
        }

        state = 7;

        //
        // add last event, 0 indexed
        {
            wxString    sqlInsert = wxString(wxT("INSERT OR IGNORE INTO events (idx, timestamp, operator, text) VALUES (?,?,?,?);"));
            wxSQLite3Statement insertStatement = m_dbCassette.PrepareStatement(sqlInsert);

            insertStatement.Bind(1, 0);
            insertStatement.Bind(2, timestamp);
            insertStatement.Bind(3, op);
            insertStatement.Bind(4, text);

            int ret = insertStatement.ExecuteUpdate();
        }

        state = 8;

        // Vacuum cassette database
        {
            m_dbCassette.Vacuum();
        }
    }
    catch (wxSQLite3Exception& e)
    {
        wxString msg;

        if (state == 0)
            msg = wxString(wxT("Error while creating the Cassette backup database.\n"));

        if (state == 1)
            msg = wxString(wxT("Error while opening the Cassette backup database.\n"));

        if (state == 2)
            msg = wxString(wxT("Error while closing the Cassette backup coffin.\n"));

        if (state == 3)
            msg = wxString(wxT("Error while deleting last event in Cassette backup database.\n"));

        if (state == 4)
            msg = wxString(wxT("Error while Cassette database reborn.\n"));

        if (state == 5)
            msg = wxString(wxT("Error while getting last event in Cassette database.\n"));

        if (state == 6)
            msg = wxString(wxT("Error while deleting all event in Cassette database.\n"));

        if (state == 7)
            msg = wxString(wxT("Error while adding first event in Cassette database.\n"));

        if (state == 8)
            msg = wxString(wxT("Error while Vacuum in Cassette database.\n"));

        msg << e.GetMessage();

        wxMessageBox(msg, wxT("Database Error"), wxOK|wxICON_ERROR);

        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_setCassetteDocked(bool docked, bool self)
{
    bool        hasBeenDocked = false;
    time_t      dts = 0;
    bool        ok = true;

    // Check if this cassette has already been docked
    if (docked && _getCassetteDockTimeStamp(dts))
        hasBeenDocked = (dts != time_t(0));

    wxString    dockTS = (docked && ! hasBeenDocked) ? wxT(", dockTS=?") : wxEmptyString;
    wxString    sqlUpdate = wxString(wxT("UPDATE informations SET docked=?")) + dockTS + wxString(wxT(";"));

    try
    {
        wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(sqlUpdate);

        updateStatement.BindBool(1, docked);

        // Update dockTS only on {Docking && Never docked} conditions
        if (docked && ! hasBeenDocked)
        {
            updateStatement.Bind(2, static_cast<int>(wxDateTime::Now().GetTicks()));
        }

        int ret = updateStatement.ExecuteUpdate();

        //wxLogStatus(updateStatement.GetSQL());
        //wxLogStatus(wxT("CassetteDocked Updated: ") + wxString::Format(wxT("%d"), ret));

        if (ret == 0)
        {
            wxMessageBox(wxT("Cassette DB update failed: unable to update docked value"), wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    if ((docked && hasBeenDocked) && ! self)
    {
        _rotateCassette();
        _setCassetteDocked(docked, true);
    }

    return ok;
}

bool HorusDatabasePool::_setCassetteRedocked()
{
    bool        ok = true;
    wxString    sqlUpdate = wxString(wxT("UPDATE informations SET docked=?;"));

    try
    {
        wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(sqlUpdate);

        updateStatement.BindBool(1, true);

        int ret = updateStatement.ExecuteUpdate();

        //wxLogStatus(updateStatement.GetSQL());
        //wxLogStatus(wxT("CassetteRedocked Updated: ") + wxString::Format(wxT("%d"), ret));

        if (ret == 0)
        {
            wxMessageBox(wxT("Cassette DB update failed: unable to update docked value"), wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_getCassetteDocked()
{
    bool        docked = false;
    wxString    selcmd = wxString(wxT("SELECT i.docked FROM informations i;"));

    try
    {
        wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);
        wxSQLite3ResultSet q = stmt.ExecuteQuery();

        if (q.NextRow())
        {
            docked = q.GetBool(0);
        }
    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Cassette DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
    }

    return docked;
}

bool HorusDatabasePool::_getCassetteDockTimeStamp(time_t &ts)
{
    bool        ok = true;
    wxString    selcmd = wxString(wxT("SELECT i.dockTS FROM informations i;"));

    try
    {
        wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);
        wxSQLite3ResultSet q = stmt.ExecuteQuery();

        if (q.NextRow())
        {
            ts = static_cast<time_t>(q.GetInt(0));
        }
    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Cassette DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_logCassetteEvent(time_t ts, const wxString &op, const wxString &message)
{
    bool        ok = true;
    int         idx = m_dbCassette.ExecuteScalar("SELECT COUNT(*) FROM events;");
    wxString    sqlInsert = wxString(wxT("INSERT OR IGNORE INTO events (idx, timestamp, operator, text) VALUES (?,?,?,?);"));

    try
    {
        wxSQLite3Statement insertStatement = m_dbCassette.PrepareStatement(sqlInsert);

        insertStatement.Bind(1, idx);
        insertStatement.Bind(2, static_cast<int>(ts));
        insertStatement.Bind(3, op);
        insertStatement.Bind(4, message);

        int ret = insertStatement.ExecuteUpdate();

        //wxLogStatus(insertStatement.GetSQL());
        //wxLogStatus(wxT("Event Changed: ") + wxString::Format(wxT("%d"), ret));

        if (ret == 0)
        {
            wxMessageBox(wxT("Cassette DB event insertion failed: unable to insert "), wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_updateCassetteOperator(const wxString &uuid)
{
    bool        ok = true;
    wxString    sqlUpdate = wxString(wxT("UPDATE informations SET operatorUUID=?;"));

    try
    {
        wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(sqlUpdate);

        updateStatement.Bind(1, uuid != wxEmptyString ? uuid : wxT("-1"));

        int ret = updateStatement.ExecuteUpdate();

        //wxLogStatus(updateStatement.GetSQL());
        //wxLogStatus(wxT("CassetteOperator Inserted: ") + wxString::Format(wxT("%d"), ret));

        if (ret == 0)
        {
            wxMessageBox(wxT("Operators DB update failed: unable to insert ")
                         + uuid, wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    return ok;
}

wxString const HorusDatabasePool::_getCassetteOperator()
{
    wxString    uuid = wxEmptyString;
    wxString    selcmd = wxString(wxT("SELECT i.operatorUUID FROM informations i;"));

    try
    {
        wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);
        wxSQLite3ResultSet q = stmt.ExecuteQuery();

        if (q.NextRow())
        {
            uuid = q.GetString(0);
        }
    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Cassette DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
    }

    return uuid;
}

bool HorusDatabasePool::_reloadCassette()
{
    // Restore data from DB
    bool    ok = true;
    size_t  cartCnt = static_cast<size_t>(m_dbCassette.ExecuteScalar("SELECT COUNT(*) FROM cartridges;"));

    //wxLogStatus(wxT("Cassette DB Count: ") + wxString::Format(wxT("%zu"), cartCnt));

    if ((cartCnt > 0) && (cartCnt <= MAX_CARTRIDGE_SLOTS))
    {
        for (size_t i = 0; i < cartCnt; i++)
        {
            HorusCartridge *slot = m_cassette->GetCartridge(i);

            if (slot)
            {
                size_t          cid;
                wxString        text;
                bool            keepFlag;
                bool            emptyFlag;
                bool            loadedFlag;
                //wxBusyCursor    cr;
                size_t          cartridgeCount = 0;
                wxString        selcmd = wxString(wxT("SELECT c.cid, c.text, c.keep, c.empty, c.loaded"))
                                         + wxString(wxT(" FROM cartridges c WHERE cid=?;"));

                try
                {
                    wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);

                    stmt.Bind(1, static_cast<int>(i + 1));

                    wxSQLite3ResultSet q = stmt.ExecuteQuery();

                    if (q.NextRow())
                    {
                        wxString str;

                        cid         = q.GetInt(0);
                        text        = q.GetString(1);
                        keepFlag    = q.GetBool(2);
                        emptyFlag   = q.GetBool(3);
                        loadedFlag  = q.GetBool(4);


                        if (cid != slot->GetNumber())
                        {
                            str = wxT("Slot number mismatch: ");
                            str << cid << wxT(" / ") << slot->GetNumber();
                            wxMessageBox(str, wxT("Error"), wxOK|wxICON_ERROR);
                        }
                        else
                        {
                            slot->SetText(text);
                            slot->SetKeepItFlag(keepFlag);
                            slot->SetEmptyFlag(emptyFlag);
                            slot->SetLoaded(loadedFlag);
                        }

                        //str = wxT("Cartridge #");
                        //str << cid << wxT(", Text: ") << text;
                        //str << wxT(", Keep: ") << wxString::Format(wxT("%s"), keepFlag ? wxT("YES") : wxT("NO"));
                        //str << wxT(", Empty: ") << wxString::Format(wxT("%s"), emptyFlag ? wxT("YES") : wxT("NO"));
                        //str << wxT(", Loaded: ") << wxString::Format(wxT("%s"), loadedFlag ? wxT("YES") : wxT("NO"));

                        //wxLogStatus(str);

                        cartridgeCount++;
                    }
                }
                catch (wxSQLite3Exception e)
                {
                    wxMessageBox(wxT("Cassette DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);

                    ok = false;
                }

                //wxLogStatus(wxT("CartridgeCount: ") + wxString::Format(wxT("%zu"), cartridgeCount));
            }
        }

        // Restore docked state;
        m_cassette->SetCassetteDocked(_getCassetteDocked());
    }
    else
    {
        wxMessageBox(wxT("Cassette DB count is out of boundaries: ") + wxString::Format(wxT("%zu"), cartCnt), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_reloadOperators(wxArrayOperator &operators)
{
    bool    ok = true;
    size_t  opsCnt = static_cast<size_t>(m_dbOperators.ExecuteScalar("SELECT COUNT(*) FROM operators;"));

    //wxLogStatus(wxT("Operator DB Count: ") + wxString::Format(wxT("%zu"), opsCnt));

    operators.Clear();
    //operators.Empty();

    if (opsCnt > 0)
    {
        size_t    operatorCount = 0;
        wxString  selcmd = wxString(wxT("SELECT o.name, o.uuid FROM operators o ORDER BY o.name, o.uuid desc;"));

        try
        {
            wxSQLite3Statement stmt = m_dbOperators.PrepareStatement(selcmd);
            wxSQLite3ResultSet q = stmt.ExecuteQuery();

            while (q.NextRow())
            {
                Operator *op = new Operator(q.GetString(0), q.GetString(1));
                //wxString  str;

                operators.Add(op);

                //str = wxT("Operator ") + op->Name + wxT(", UUID: ") + op->UUID + wxT(" restored.");
                //wxLogStatus(str);

                operatorCount++;
            }
        }
        catch (wxSQLite3Exception e)
        {
            wxMessageBox(wxT("Operators DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);

            ok = false;
        }

        //wxLogStatus(wxT("OperatorCount: ") + wxString::Format(wxT("%zu"), operatorCount));
    }

    operators.Sort(&hUtils::CompareOperators);

    return ok;
}

bool HorusDatabasePool::_reloadEvents(HorusDatabaseEventRestore *receiver)
{
    bool    ok = true;
    size_t  evtCnt = static_cast<size_t>(m_dbCassette.ExecuteScalar("SELECT COUNT(*) FROM events;"));
    //wxArrayHorusDatabaseEventEntries *entries = new wxArrayHorusDatabaseEventEntries();
    //HorusEventDatabaseEventData *data = new HorusEventDatabaseEventData();

    //wxLogStatus(wxT("Event DB Count: ") + wxString::Format(wxT("%zu"), evtCnt));

    if (evtCnt > 0)
    {
        //wxString  selcmd = wxString(wxT("SELECT o.name, o.uuid FROM operators o ORDER BY o.name, o.uuid desc;"));
        wxString  selcmd = wxString(wxT("SELECT e.idx, e.timestamp, e.operator, e.text FROM events e ORDER BY e.idx;"));

        try
        {
            wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);
            wxSQLite3ResultSet q = stmt.ExecuteQuery();

            while (q.NextRow())
            {
//                time_t   ts     = static_cast<time_t>(q.GetInt(1));
//                wxString op     = q.GetString(2);
//                wxString msg    = q.GetString(3);

                //logger->horusLoggerCallbackFunction(ts, op, msg);
                //data->AddEntry(static_cast<time_t>(q.GetInt(1)), q.GetString(2), q.GetString(3));

                receiver->HorusEventRestore(static_cast<time_t>(q.GetInt(1)), q.GetString(2), q.GetString(3));

                //_sendReloadEvent(ts, op, msg);

                //wxString str = wxT("Restore message ") + wxString::Format(wxT("%llu"), ts) + wxT(" [") + op + wxT("] ") + msg;
                //wxLogStatus(str);
            }
        }
        catch (wxSQLite3Exception e)
        {
            wxMessageBox(wxT("Events DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);

            ok = false;
        }

        //_sendReloadEvent(data);

    }

    return ok;
}

#if 0
wxSQLite3Database* _initDB(void)
{
    wxString testDBName = wxGetCwd() + wxT("/test2.db");

    if (wxFileExists(testDBName))
    {
        wxRemoveFile(testDBName);
    }

    wxSQLite3Database* db = new wxSQLite3Database();
    db->Open(testDBName);
    db->ExecuteUpdate(wxT("CREATE TABLE test (col1 INTEGER)"));
    return db;
}

void _clearDB(wxSQLite3Database* db)
{
    assert(db != NULL);
    db->Close();
    delete db;
}

#endif // 0

bool HorusDatabasePool::_initializeDatabases()
{
    //wxSQLite3Database db;
    //wxLogStatus(wxT("wxSQLite3 Version:    ") + wxSQLite3Database::GetWrapperVersion());
    //wxLogStatus(wxT("SQLite3 Version:      ") + db.GetVersion());
    //wxLogStatus(wxT("SQLite3 Source Id:    ") + db.GetSourceId());

    return _initializeCassetteDatabase() && _initializeOperatorsDatabase();
}

bool HorusDatabasePool::_initializeCassetteDatabase()
{
    bool        ok = true;
    int         state = 0;
    int         j = 0;
    const char* sqlCommands[] = {
    "pragma foreign_keys=1;",
    "CREATE TABLE IF NOT EXISTS informations (\
       dockTS         INT  UNIQUE NOT NULL,\
       funeral        INT  UNIQUE,\
       operatorUUID   VARCHAR(32) UNIQUE NOT NULL,\
       docked         INT,\
       keepOnStage    INT,\
     PRIMARY KEY (dockTS));",
    "CREATE TABLE IF NOT EXISTS cartridges (\
       cid            INT         NOT NULL,\
       text           VARCHAR(80) NOT NULL,\
       keep           INT         NOT NULL,\
       empty          INT         NOT NULL,\
       loaded         INT         NOT NULL,\
     PRIMARY KEY (cid));",
    "CREATE TABLE IF NOT EXISTS events (\
       idx            INT         UNIQUE NOT NULL,\
       timestamp      INT         NOT NULL,\
       operator       VARCHAR(32) NOT NULL,\
       text           VARCHAR(80) NOT NULL,\
     PRIMARY KEY (idx));",
    NULL };

    try
    {
        m_dbCassette.Open(m_dbPath + wxFILE_SEP_PATH + wxT("cassette.db3"));
        //m_dbCassette.Begin(WXSQLITE_TRANSACTION_EXCLUSIVE);

        while (sqlCommands[j] != NULL)
            m_dbCassette.ExecuteUpdate(sqlCommands[j++]);

        state = 1;

        // Database is empty, fix that
        if (m_dbCassette.ExecuteScalar("SELECT COUNT(*) FROM cartridges;") == 0)
        {
            ok = _fillCartridgesData();
        }

        if (ok)
        {
            // Get creation time;
            wxString  selcmd = wxString(wxT("SELECT i.dockTS, i.funeral FROM informations i;"));

            try
            {
                wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);
                wxSQLite3ResultSet q = stmt.ExecuteQuery();

                if (q.NextRow())
                {
                    time_t      ts = static_cast<time_t>(q.GetInt(0));
                    wxDateTime  dt(ts);

                    //wxLogStatus(wxT("Database dockTS : ") + dt.Format(wxT("%a %b %d %Y %H:%M:%S")));
                }
            }
            catch (wxSQLite3Exception e)
            {
                wxMessageBox(wxT("Cassette DB informations query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);

                ok = false;
            }
        }

    }
    catch (wxSQLite3Exception& e)
    {
        wxString msg;

        if (state == 0)
            msg = wxString(wxT("Error on creating the Cassette database.\n"));

        if (state == 1)
            msg = wxString(wxT("Error on initializing the Cassette database.\n"));

        msg << e.GetMessage();

        wxMessageBox(msg, wxT("Database Error"), wxOK|wxICON_ERROR);

        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_initializeOperatorsDatabase()
{
    bool        ok = true;
    int         state = 0;
    int         j = 0;
    const char* sqlCommands[] = {
    "pragma foreign_keys=1;",
    "CREATE TABLE IF NOT EXISTS operators (\
       name           VARCHAR(32)  UNIQUE NOT NULL,\
       uuid           VARCHAR(32)  UNIQUE NOT NULL,\
     PRIMARY KEY (uuid));",
    NULL };

    try
    {
        m_dbOperators.Open(m_dbPath + wxFILE_SEP_PATH + wxT("operators.db3"));
        //m_dbCassette.Begin(WXSQLITE_TRANSACTION_EXCLUSIVE);

        while (sqlCommands[j] != NULL)
            m_dbOperators.ExecuteUpdate(sqlCommands[j++]);

        state = 1;

        // Database is empty, fix that
        if (m_dbOperators.ExecuteScalar("SELECT COUNT(*) FROM operators;") == 0)
        {
            //ok = _fillCartridgesData();
        }

    }
    catch (wxSQLite3Exception& e)
    {
        wxString msg;

        if (state == 0)
            msg = wxString(wxT("Error on creating the Operators database.\n"));

        if (state == 1)
            msg = wxString(wxT("Error on initializing the Operators database.\n"));

        msg << e.GetMessage();

        wxMessageBox(msg, wxT("Database Error"), wxOK|wxICON_ERROR);

        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_updateCartridgeData(HorusCartridge *slot)
{
    bool ok = true;

    if (! slot)
        return false;

    wxString  sqlUpdate = wxString(wxT("UPDATE cartridges SET text=?, keep=?, empty=?, loaded=? WHERE cid=?;"));

    if (slot)
    {
        try
        {
            wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(sqlUpdate);

            updateStatement.Bind(1, slot->GetText());
            updateStatement.BindBool(2, slot->GetKeepItFlag());
            updateStatement.BindBool(3, slot->GetEmptyFlag());
            updateStatement.BindBool(4, slot->GetLoaded());

            updateStatement.Bind(5, static_cast<int>(slot->GetNumber()));

            int ret = updateStatement.ExecuteUpdate();

            //wxLogStatus(updateStatement.GetSQL());
            //wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));

            if (ret == 0)
            {
                wxMessageBox(wxT("Cassette DB update failed: unable to update slot #")
                             + wxString::Format(wxT("%zu"), slot->GetNumber()), wxT("Database Error"), wxOK|wxICON_ERROR);
                ok = false;
            }

        }
        catch (wxSQLite3Exception e)
        {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }

    return ok;
}

bool HorusDatabasePool::_insertOperator(const wxString &name, const wxString &uuid)
{
    bool        ok = true;
    wxString    sqlInsert = wxString(wxT("INSERT OR IGNORE INTO operators (name, uuid) VALUES (?,?);"));

    try
    {
        wxSQLite3Statement insertStatement = m_dbOperators.PrepareStatement(sqlInsert);

        insertStatement.Bind(1, name);
        insertStatement.Bind(2, uuid);

        int ret = insertStatement.ExecuteUpdate();

        //wxLogStatus(insertStatement.GetSQL());
        //wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));

        if (ret == 0)
        {
            wxMessageBox(wxT("Operators DB insertion failed: unable to insert ")
                         + name + wxT(", UUID: ") + uuid, wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_updateOperator(const wxString &name, const wxString &uuid)
{
    bool        ok = true;
    wxString    sqlUpdate = wxString(wxT("UPDATE operators SET name=? WHERE uuid=?;"));

    try
    {
        wxSQLite3Statement updateStatement = m_dbOperators.PrepareStatement(sqlUpdate);

        updateStatement.Bind(1, name);
        updateStatement.Bind(2, uuid);

        int ret = updateStatement.ExecuteUpdate();

        //wxLogStatus(updateStatement.GetSQL());
        //wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));

        if (ret == 0)
        {
            wxMessageBox(wxT("Operators DB update failed: unable to insert ")
                         + name + wxT(", UUID: ") + uuid, wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    return ok;
}

bool HorusDatabasePool::_deleteOperator(const wxString &uuid)
{
    bool        ok = true;
    wxString    sqlDelete = wxString(wxT("DELETE FROM operators WHERE uuid=?;"));

    try
    {
        wxSQLite3Statement deleteStatement = m_dbOperators.PrepareStatement(sqlDelete);

        deleteStatement.Bind(1, uuid);

        int ret = deleteStatement.ExecuteUpdate();

        //wxLogStatus(deleteStatement.GetSQL());
        //wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));

        if (ret == 0)
        {
            wxMessageBox(wxT("Operators DB deletion failed: unable to delete UUID: ") + uuid,
                         wxT("Database Error"), wxOK|wxICON_ERROR);
            ok = false;
        }

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
        ok = false;
    }

    return ok;
}

#if 0
bool HorusDatabasePool::_saveDB()
{
    bool ok = true;

    for (size_t i = 0; i < MAX_CARTRIDGE_SLOTS; i++)
    {
        wxString        sqlUpdate = wxString(wxT("UPDATE cartridges SET text=?, keep=?, empty=?, loaded=? WHERE cid=?;"));
        HorusCartridge *slot = m_cassette->GetCartridge(i);

        if (slot)
        {
            try
            {
                wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(sqlUpdate);

                updateStatement.Bind(1, slot->GetText());
                updateStatement.BindBool(2, slot->GetKeepItFlag());
                updateStatement.BindBool(3, slot->GetEmptyFlag());
                updateStatement.BindBool(4, slot->GetLoaded());

                updateStatement.Bind(5, static_cast<int>(i + 1));

                int ret = updateStatement.ExecuteUpdate();

                //wxLogStatus(updateStatement.GetSQL());
                //wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));


            }
            catch (wxSQLite3Exception e)
            {
                wxMessageBox(wxT("Error: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);
                ok = false;
            }
        }
    }

    //m_dbCassette.Commit();



    return ok;
}
#endif // 0

void HorusDatabasePool::_sendEvent(HorusDatabaseEvent eventID)
{
    HorusEventDatabaseData *data = new HorusEventDatabaseData();
    wxCommandEvent          event(wxEVT_HORUS_DATABASEPOOL, GetId());

    event.SetInt(eventID);

    event.SetClientData((void *)data);

    wxPostEvent((wxEvtHandler *)m_parent, event);
}

void HorusDatabasePool::_sendBackupEvent(const wxString &dbName)
{
    HorusEventDatabaseData *data = new HorusEventDatabaseData();
    wxCommandEvent          event(wxEVT_HORUS_DATABASEPOOL, GetId());

    data->BackupFile = dbName;

    event.SetInt(HORUS_EVENT_DATABASEPOOL_BACKUP);

    event.SetClientData((void *)data);

    wxPostEvent((wxEvtHandler *)m_parent, event);
}

bool HorusDatabasePool::_fillCartridgesData()
{
    bool ok = true;

    //
    try
    {
        wxString            sqlInsert = wxString(wxT("INSERT OR IGNORE INTO informations (dockTS, operatorUUID, docked, keepOnStage) VALUES (?,?,?,?);"));
        wxSQLite3Statement  insertStatement = m_dbCassette.PrepareStatement(sqlInsert);

        insertStatement.Bind(1, 0); // Zero dock timestamp
        insertStatement.Bind(2, wxT("-1"));
        insertStatement.BindBool(3, false);
        insertStatement.BindBool(4, false);

        int ret = insertStatement.ExecuteUpdate();

        ////wxLogStatus(wxT("SQL: ") + insertStatement.GetSQL());
        //wxLogStatus(wxT("dockTS and Docked Inserted: ") + wxString::Format(wxT("%d"), ret));

    }
    catch (wxSQLite3Exception e)
    {
        wxMessageBox(wxT("Cassette DB informations failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);

        ok = false;
    }


    if (! ok)
        return ok;

    // Add Cartridges
    for (size_t i = 0; i < MAX_CARTRIDGE_SLOTS; i++)
    {
        HorusCartridge *slot = m_cassette->GetCartridge(i);
        wxString        sqlInsert = wxString(wxT("INSERT INTO cartridges (cid, text, keep, empty, loaded)"))
                                            + wxString(wxT(" VALUES (?,?,?,?,?);"));

        if (slot)
        {
            try
            {
                wxSQLite3Statement insertStatement = m_dbCassette.PrepareStatement(sqlInsert);

                insertStatement.Bind(1, static_cast<int>(slot->GetNumber()));
                insertStatement.Bind(2, slot->GetText());
                insertStatement.BindBool(3, slot->GetKeepItFlag());
                insertStatement.BindBool(4, slot->GetEmptyFlag());
                insertStatement.BindBool(5, slot->GetLoaded());

                int ret = insertStatement.ExecuteUpdate();

                ////wxLogStatus(wxT("SQL: ") + insertStatement.GetSQL());
                //wxLogStatus(wxT("Cartridge Inserted: ") + wxString::Format(wxT("%d"), ret));

            }
            catch (wxSQLite3Exception e)
            {
                wxMessageBox(wxT("Cassette DB insertion failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);

                ok = false;
            }
        }
    }

    return ok;
}

} // namespace
