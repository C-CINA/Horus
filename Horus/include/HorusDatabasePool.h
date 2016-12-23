#ifndef HORUSDATABASEPOOL_H
#define HORUSDATABASEPOOL_H

#include "../HorusMain.h"
//#include "HorusCassette.h"

namespace Horus
{


class HorusDatabasePool
{
    public:
        HorusDatabasePool();
        virtual ~HorusDatabasePool();

        bool IsOK()
        {
            return m_initialized;
        }

        bool Initialize(HorusCassette *cassette)
        {
            if (m_initialized)
                return false;

            m_cassette = cassette;

            wxSQLite3Database::InitializeSQLite();

            _testDB();

            m_initialized = _initializeDatabases();

            return m_initialized;
        }

        bool ReloadData(wxArrayOperator &operators)
        {
            if (!m_initialized)
                return false;

            return _reloadCassette() && _reloadOperators(operators);
        }


        bool UpdateCartridge(HorusCartridge *cartridge)
        {
            if (! m_initialized)
                return false;

            return _updateCartridgeData(cartridge);
        }

        bool AddOperator(const wxString &name, const wxString &uuid)
        {
            if (! m_initialized)
                return false;

            return _insertOperator(name, uuid);
        }

        bool UpdateOperator(const wxString &name, const wxString &uuid)
        {
            if (! m_initialized)
                return false;

            return _updateOperator(name, uuid);
        }

        bool DeleteOperator(const wxString &uuid)
        {
            if (! m_initialized)
                return false;

            return _deleteOperator(uuid);
        }

        bool SetCassetteOperator(const wxString &uuid)
        {
            if (! m_initialized)
                return false;

            return _updateCassetteOperator(uuid);
        }

        wxString const GetCassetteOperator()
        {
            if (! m_initialized)
                return wxEmptyString;

            return _getCassetteOperator();
        }

    protected:
        bool _updateCassetteOperator(const wxString &uuid)
        {
            bool        ok = true;
            wxString    sqlUpdate = wxString(wxT("UPDATE informations SET operatorUUID=?;"));

            try
            {
                wxSQLite3Statement updateStatement = m_dbCassette.PrepareStatement(sqlUpdate);

                updateStatement.Bind(1, uuid);

                int ret = updateStatement.ExecuteUpdate();

                wxLogStatus(updateStatement.GetSQL());
                wxLogStatus(wxT("CassetteOperator Inserted: ") + wxString::Format(wxT("%d"), ret));

                if (ret == 0)
                {
                    wxMessageBox(wxT("Operators DB update failed: unable to insert ")
                                 + uuid, wxT("Database Error"), wxOK|wxICON_ERROR);
                    ok = false;
                }

            }
            catch (wxSQLite3Exception e)
            {
                #warning wxmessagebox
                wxLogStatus(wxT("Error: ") + e.GetMessage());
                ok = false;
            }

            return ok;
        }

        wxString const _getCassetteOperator()
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

        bool _reloadCassette()
        {
            // Restore data from DB
            bool    ok = true;
            size_t  cartCnt = static_cast<size_t>(m_dbCassette.ExecuteScalar("SELECT COUNT(*) FROM cartridges;"));

            wxLogStatus(wxT("Cassette DB Count: ") + wxString::Format(wxT("%zu"), cartCnt));

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

                                str = wxT("Cartridge #");
                                str << cid << wxT(", Text: ") << text;
                                str << wxT(", Keep: ") << wxString::Format(wxT("%s"), keepFlag ? wxT("YES") : wxT("NO"));
                                str << wxT(", Empty: ") << wxString::Format(wxT("%s"), emptyFlag ? wxT("YES") : wxT("NO"));
                                str << wxT(", Loaded: ") << wxString::Format(wxT("%s"), loadedFlag ? wxT("YES") : wxT("NO"));

                                wxLogStatus(str);

                                cartridgeCount++;
                            }
                        }
                        catch (wxSQLite3Exception e)
                        {
                            wxMessageBox(wxT("Cassette DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);

                            ok = false;
                        }

                        wxLogStatus(wxT("CartridgeCount: ") + wxString::Format(wxT("%zu"), cartridgeCount));
                    }
                }
            }
            else
            {
                wxMessageBox(wxT("Cassette DB count is out of boundaries: ") + wxString::Format(wxT("%zu"), cartCnt), wxT("Database Error"), wxOK|wxICON_ERROR);
                ok = false;
            }

            return ok;
        }

        bool _reloadOperators(wxArrayOperator &operators)
        {
            wxLogStatus(wxT("ENTER _reloadOperators()"));
            // Restore data from DB
            bool    ok = true;
            size_t  opsCnt = static_cast<size_t>(m_dbOperators.ExecuteScalar("SELECT COUNT(*) FROM operators;"));

            wxLogStatus(wxT("Operator DB Count: ") + wxString::Format(wxT("%zu"), opsCnt));

            operators.Clear();
            //operators.Empty();

            if (opsCnt > 0)
            {
                size_t    operatorCount = 0;
                wxString  selcmd = wxString(wxT("SELECT o.name, o.uuid FROM operators o order by o.name, o.uuid desc;"));

                try
                {
                    wxSQLite3Statement stmt = m_dbOperators.PrepareStatement(selcmd);
                    wxSQLite3ResultSet q = stmt.ExecuteQuery();

                    while (q.NextRow())
                    {
                        Operator *op = new Operator(q.GetString(0), q.GetString(1));
                        wxString  str;

                        operators.Add(op);

                        str = wxT("Operator ") + op->Name + wxT(", UUID: ") + op->UUID + wxT(" restored.");
                        wxLogStatus(str);

                        operatorCount++;
                    }
                }
                catch (wxSQLite3Exception e)
                {
                    wxMessageBox(wxT("Operators DB query failed: ") + e.GetMessage(), wxT("Database Error"), wxOK|wxICON_ERROR);

                    ok = false;
                }

                wxLogStatus(wxT("OperatorCount: ") + wxString::Format(wxT("%zu"), operatorCount));
            }

            operators.Sort(&hUtils::CompareOperators);

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

        void _testDB()
        {
            wxSQLite3Database db;

            wxLogStatus(wxT("wxSQLite3 Version:    ") + wxSQLite3Database::GetWrapperVersion());
            wxLogStatus(wxT("SQLite3 Version:      ") + db.GetVersion());
            wxLogStatus(wxT("SQLite3 Source Id:    ") + db.GetSourceId());
        }

        bool _initializeDatabases()
        {
            return _initializeCassetteDatabase() && _initializeOperatorsDatabase();
        }

        bool _initializeCassetteDatabase()
        {
            bool        ok = true;
            int         state = 0;
            int         j = 0;
            const char* sqlCommands[] = {
            "pragma foreign_keys=1;",
            "CREATE TABLE IF NOT EXISTS informations (\
               birth          INT  UNIQUE,\
               funeral        INT  UNIQUE,\
               operatorUUID   VARCHAR(32) UNIQUE,\
             PRIMARY KEY (birth));",
            "CREATE TABLE IF NOT EXISTS cartridges (\
               cid            INT         NOT NULL,\
               text           VARCHAR(80) NOT NULL,\
               keep           INT         NOT NULL,\
               empty          INT         NOT NULL,\
               loaded         INT         NOT NULL,\
             PRIMARY KEY (cid));",
            "CREATE TABLE IF NOT EXISTS events (\
               timestamp      INT         NOT NULL,\
               operator       VARCHAR(80) NOT NULL,\
               cid            INT         NOT NULL,\
               text           VARCHAR(80) NOT NULL,\
             PRIMARY KEY (timestamp));",
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
                    wxString  selcmd = wxString(wxT("SELECT i.birth, i.funeral FROM informations i;"));

                    try
                    {
                        wxSQLite3Statement stmt = m_dbCassette.PrepareStatement(selcmd);
                        wxSQLite3ResultSet q = stmt.ExecuteQuery();

                        if (q.NextRow())
                        {
                            time_t      ts = static_cast<time_t>(q.GetInt(0));
                            wxDateTime  dt(ts);

                            wxLogStatus(wxT("Database Birth : ") + dt.Format(wxT("%a %b %d %Y %H:%M:%S")));
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

        bool _initializeOperatorsDatabase()
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

        bool _updateCartridgeData(HorusCartridge *slot)
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

                    wxLogStatus(updateStatement.GetSQL());
                    wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));

                    if (ret == 0)
                    {
                        wxMessageBox(wxT("Cassette DB update failed: unable to update slot #")
                                     + wxString::Format(wxT("%zu"), slot->GetNumber()), wxT("Database Error"), wxOK|wxICON_ERROR);
                        ok = false;
                    }

                }
                catch (wxSQLite3Exception e)
                {
                    #warning wxmessagebox
                    wxLogStatus(wxT("Error: ") + e.GetMessage());
                    ok = false;
                }

            }

            return ok;
        }

        bool _insertOperator(const wxString &name, const wxString &uuid)
        {
            bool        ok = true;
            wxString    sqlInsert = wxString(wxT("INSERT OR IGNORE INTO operators (name, uuid) VALUES (?,?);"));

            try
            {
                wxSQLite3Statement insertStatement = m_dbOperators.PrepareStatement(sqlInsert);

                insertStatement.Bind(1, name);
                insertStatement.Bind(2, uuid);

                int ret = insertStatement.ExecuteUpdate();

                wxLogStatus(insertStatement.GetSQL());
                wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));

                if (ret == 0)
                {
                    wxMessageBox(wxT("Operators DB insertion failed: unable to insert ")
                                 + name + wxT(", UUID: ") + uuid, wxT("Database Error"), wxOK|wxICON_ERROR);
                    ok = false;
                }

            }
            catch (wxSQLite3Exception e)
            {
                #warning wxmessagebox
                wxLogStatus(wxT("Error: ") + e.GetMessage());
                ok = false;
            }

            return ok;
        }

        bool _updateOperator(const wxString &name, const wxString &uuid)
        {
            bool        ok = true;
            wxString    sqlUpdate = wxString(wxT("UPDATE operators SET name=? WHERE uuid=?;"));

            try
            {
                wxSQLite3Statement updateStatement = m_dbOperators.PrepareStatement(sqlUpdate);

                updateStatement.Bind(1, name);
                updateStatement.Bind(2, uuid);

                int ret = updateStatement.ExecuteUpdate();

                wxLogStatus(updateStatement.GetSQL());
                wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));

                if (ret == 0)
                {
                    wxMessageBox(wxT("Operators DB update failed: unable to insert ")
                                 + name + wxT(", UUID: ") + uuid, wxT("Database Error"), wxOK|wxICON_ERROR);
                    ok = false;
                }

            }
            catch (wxSQLite3Exception e)
            {
                #warning wxmessagebox
                wxLogStatus(wxT("Error: ") + e.GetMessage());
                ok = false;
            }

            return ok;
        }

        bool _deleteOperator(const wxString &uuid)
        {
            bool        ok = true;
            wxString    sqlDelete = wxString(wxT("DELETE FROM operators WHERE uuid=?;"));

            try
            {
                wxSQLite3Statement deleteStatement = m_dbOperators.PrepareStatement(sqlDelete);

                deleteStatement.Bind(1, uuid);

                int ret = deleteStatement.ExecuteUpdate();

                wxLogStatus(deleteStatement.GetSQL());
                wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));

                if (ret == 0)
                {
                    wxMessageBox(wxT("Operators DB deletion failed: unable to delete UUID: ") + uuid,
                                 wxT("Database Error"), wxOK|wxICON_ERROR);
                    ok = false;
                }

            }
            catch (wxSQLite3Exception e)
            {
                #warning wxmessagebox
                wxLogStatus(wxT("Error: ") + e.GetMessage());
                ok = false;
            }

            return ok;
        }

        bool _saveDB()
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

                        wxLogStatus(updateStatement.GetSQL());
                        wxLogStatus(wxT("Changed: ") + wxString::Format(wxT("%d"), ret));


                    }
                    catch (wxSQLite3Exception e)
                    {
                        #warning wxmessagebox
                        wxLogStatus(wxT("Error: ") + e.GetMessage());
                        ok = false;
                    }
                }
            }

            //m_dbCassette.Commit();



            return ok;
        }

    private:
        bool _fillCartridgesData()
        {
            bool ok = true;

            //
            try
            {
                wxString            sqlInsert = wxString(wxT("INSERT OR IGNORE INTO informations (birth) VALUES (?);"));
                wxSQLite3Statement  insertStatement = m_dbCassette.PrepareStatement(sqlInsert);

                insertStatement.Bind(1, static_cast<int>(wxDateTime::Now().GetTicks()));

                int ret = insertStatement.ExecuteUpdate();

                //wxLogStatus(wxT("SQL: ") + insertStatement.GetSQL());
                wxLogStatus(wxT("Birth Inserted: ") + wxString::Format(wxT("%d"), ret));

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

                        //wxLogStatus(wxT("SQL: ") + insertStatement.GetSQL());
                        wxLogStatus(wxT("Cartridge Inserted: ") + wxString::Format(wxT("%d"), ret));

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

    private:
        bool                            m_initialized;
        wxString                        m_dbPath;
        HorusCassette                  *m_cassette;

        wxSQLite3Database               m_dbCassette;
        wxSQLite3Database               m_dbOperators;

};

}

#endif // HORUSDATABASEPOOL_H
