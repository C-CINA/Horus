/// -----------------------------------------------------------------------------
///
/// \file HorusDatabasePool.h
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

#ifndef HORUSDATABASEPOOL_H
#define HORUSDATABASEPOOL_H

#include "../HorusMain.h"
//#include "HorusCassette.h"

namespace Horus
{

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_HORUS_DATABASEPOOL, wxNewEventType()) ///<
END_DECLARE_EVENT_TYPES()


class HorusDatabaseEventRestore
{
    public:
        virtual void HorusEventRestore(time_t, const wxString &, const wxString &) = 0;
};

class HorusEventDatabaseEventData;

enum HorusDatabaseEvent
{
    HORUS_EVENT_DATABASEPOOL_BACKUP
};

class HorusDatabasePool
{
    public:
        HorusDatabasePool(wxWindow *parent);
        virtual ~HorusDatabasePool();

        bool                            IsOK();
        bool                            Initialize(HorusCassette *);
        wxString const                  GetBackupPath();
        wxWindowID                      GetId();
        bool                            ReloadData(wxArrayOperator &, HorusDatabaseEventRestore *);
        bool                            UpdateCartridge(HorusCartridge *);
        bool                            AddOperator(const wxString &, const wxString &);
        bool                            UpdateOperator(const wxString &, const wxString &);
        bool                            DeleteOperator(const wxString &);
//        bool                            SetCassetteOperator(const wxString &);
        wxString const                  GetCassetteOperator();
        bool                            LogCassetteEvent(time_t, const wxString &, const wxString &);
        bool                            SetCassetteDocked(bool, const wxString &);
        bool                            SetCassetteRedocked();
        bool                            GetCassetteDocked();
        bool                            GetCassetteDockTimeStamp(time_t &);
        bool                            SetKeepOnStage(bool);
        bool                            GetKeepOnStage();


    private:
        bool                            _setKeepOnStage(bool);
        bool                            _getKeepOnStage();
        bool                            _rotateCassette(const wxString &);
        bool                            _setCassetteDocked(bool, const wxString &, bool = false);
        bool                            _setCassetteRedocked();
        bool                            _getCassetteDocked();
        bool                            _getCassetteDockTimeStamp(time_t &);
        bool                            _logCassetteEvent(time_t ts, const wxString &, const wxString &);
        bool                            _updateCassetteOperator(const wxString &);
        wxString const                  _getCassetteOperator();
        bool                            _reloadCassette();
        bool                            _reloadOperators(wxArrayOperator &);
        bool                            _reloadEvents(HorusDatabaseEventRestore *);

        bool                            _initializeDatabases();
        bool                            _initializeCassetteDatabase();
        bool                            _initializeOperatorsDatabase();
        bool                            _updateCartridgeData(HorusCartridge *);
        bool                            _insertOperator(const wxString &, const wxString &);
        bool                            _updateOperator(const wxString &, const wxString &);
        bool                            _deleteOperator(const wxString &);
        bool                            _fillCartridgesData();

        //bool                            _saveDB();

        void                            _sendEvent(HorusDatabaseEvent);
        void                            _sendBackupEvent(const wxString &dbName);

    private:
        wxWindow                       *m_parent;
        wxWindowID                      m_id;
        bool                            m_initialized;
        wxString                        m_dbPath;
        wxString                        m_dbBackupPath;
        HorusCassette                  *m_cassette;

        wxSQLite3Database               m_dbCassette;
        wxSQLite3Database               m_dbOperators;

};


struct HorusEventDatabaseData
{
    HorusEventDatabaseData() : TimeStamp(wxDateTime::Now().GetTicks()), BackupFile(wxEmptyString)
    {
    }

    HorusEventDatabaseData(time_t ts) : TimeStamp(ts), BackupFile(wxEmptyString)
    {
    }

    ~HorusEventDatabaseData()
    {

    }

    time_t                              TimeStamp;
    wxString                            BackupFile;
};


}

#endif // HORUSDATABASEPOOL_H
