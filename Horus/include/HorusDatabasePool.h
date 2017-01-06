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

/// \brief Database event(s)
///
enum HorusDatabaseEvent
{
    HORUS_EVENT_DATABASEPOOL_BACKUP ///< A backup has been performed, filename will be available in event's data
};

class HorusDatabasePool
{
    public:
        /// \brief Constructor
        ///
        /// \param parent wxWindow* parent window
        ///
        ///
        HorusDatabasePool(wxWindow *parent);

        /// \brief Destructor
        ///
        /// \return virtual
        ///
        ///
        virtual ~HorusDatabasePool();

        /// \brief Get pool state
        ///
        /// \return bool true if initialized.
        ///
        ///
        bool                            IsOK();

        /// \brief Initialize the pool, extract cartridges informations form cassette argument (and store cassette pointer)
        ///
        /// \param  HorusCassette* cassette to attach to.
        /// \return bool true on success
        ///
        ///
        bool                            Initialize(HorusCassette *);

        /// \brief Returns the database backup pathname.
        ///
        /// \return wxString const database backup pathname
        ///
        ///
        wxString const                  GetBackupPath();

        /// \brief Returns pool ID
        ///
        /// \return wxWindowID ID
        ///
        ///
        wxWindowID                      GetId();

        /// \brief Reload pool information, fill the operator array and use HorusDatabaseEventRestore::HorusEventRestore()
        ///         while reloading cassette events.
        ///
        /// \param  wxArrayOperator& destination operators array
        /// \param  HorusDatabaseEventRestore* destination class for cassette events
        /// \return bool true on success
        ///
        ///
        bool                            ReloadData(wxArrayOperator &, HorusDatabaseEventRestore *);

        /// \brief Update database values of given cartridge.
        ///
        /// \param  HorusCartridge* source cartridge
        /// \return bool true on success
        ///
        ///
        bool                            UpdateCartridge(HorusCartridge *);

        /// \brief Add an operator in the pool
        ///
        /// \param  const wxString& operator name
        /// \param  const wxString& operator UUID
        /// \return bool true on success
        ///
        ///
        bool                            AddOperator(const wxString &, const wxString &);

        /// \brief Update operator name, identification defined by UUID
        ///
        /// \param  const wxString& operator name
        /// \param  const wxString& operator UUID
        /// \return bool
        ///
        ///
        bool                            UpdateOperator(const wxString &, const wxString &);

        /// \brief Delete an operator from the database
        ///
        /// \param  const wxString& operator UUID
        /// \return bool true on success
        ///
        ///
        bool                            DeleteOperator(const wxString &);

        /// \brief Returns cassette operator UUID
        ///
        /// \return wxString const non wxEmptyString on success.
        ///
        ///
        wxString const                  GetCassetteOperator();

        /// \brief Log an event in cassette database
        ///
        /// \param time_t event timestamp
        /// \param  const wxString& event operator
        /// \param  const wxString& event text
        /// \return bool true on success
        ///
        ///
        bool                            LogCassetteEvent(time_t, const wxString &, const wxString &);

        /// \brief Define the docking cassette state, made by given operator. This member also handle backup of
        ///         previously docked cassette, and send a BACKUP event, if any.
        ///
        /// \param bool docking state
        /// \param  const wxString& operator UUID
        /// \return bool true on success
        ///
        ///
        bool                            SetCassetteDocked(bool, const wxString &);

        /// \brief Redock a previously docked cassette.
        ///
        /// \return bool true on success
        ///
        ///
        bool                            SetCassetteRedocked();

        /// \brief Returns cassette docking state
        ///
        /// \return bool true if docked, otherwise false.
        ///
        ///
        bool                            GetCassetteDocked();

        /// \brief Get cassette docking timestamp
        ///
        /// \param  time_t& destination timestamp.
        /// \return bool true on success
        ///
        ///
        bool                            GetCassetteDockTimeStamp(time_t &);

        /// \brief Define "Keep On Stage" state flag
        ///
        /// \param bool flag state
        /// \return bool true on success
        ///
        ///
        bool                            SetKeepOnStage(bool);

        /// \brief Get "Keep On Stage" state flag
        ///
        /// \return bool true if "Keep On Stage" is defined
        ///
        ///
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

        void                            _sendEvent(HorusDatabaseEvent);
        void                            _sendBackupEvent(const wxString &dbName);

    private:
        wxWindow                       *m_parent; ///< Parent window
        wxWindowID                      m_id; ///< Pool ID
        bool                            m_initialized; ///< Initialization flag
        wxString                        m_dbPath; ///< Database pathname
        wxString                        m_dbBackupPath; ///< Database backup pathname
        HorusCassette                  *m_cassette; ///< Cassette pointer

        wxSQLite3Database               m_dbCassette; ///< Cassette database
        wxSQLite3Database               m_dbOperators; ///< Operators database
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
