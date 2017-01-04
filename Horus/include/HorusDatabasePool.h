#ifndef HORUSDATABASEPOOL_H
#define HORUSDATABASEPOOL_H

#include "../HorusMain.h"
//#include "HorusCassette.h"

namespace Horus
{

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_HORUS_DATABASEPOOL, wxNewEventType()) ///<
END_DECLARE_EVENT_TYPES()

enum HorusDatabaseEvent
{
    HORUS_EVENT_DATABASEPOOL_RELOAD_EVENTS,
    HORUS_EVENT_DATABASEPOOL_BACKUP
};

class HorusDatabasePool
{
    public:
        HorusDatabasePool(wxWindow *parent);
        virtual ~HorusDatabasePool();

        bool                            IsOK();
        bool                            Initialize(HorusCassette *);
        wxString const                  GetBackupPath()
        {
            return m_dbBackupPath;
        }
        wxWindowID                      GetId()
        {
            return m_id;
        }

        bool                            ReloadData(wxArrayOperator &);
        bool                            UpdateCartridge(HorusCartridge *);
        bool                            AddOperator(const wxString &, const wxString &);
        bool                            UpdateOperator(const wxString &, const wxString &);
        bool                            DeleteOperator(const wxString &);
        bool                            SetCassetteOperator(const wxString &);
        wxString const                  GetCassetteOperator();
        bool                            LogCassetteEvent(time_t, const wxString &, const wxString &);
        bool                            SetCassetteDocked(bool);
        bool                            SetCassetteRedocked();
        bool                            GetCassetteDocked();
        bool                            GetCassetteDockTimeStamp(time_t &);
        bool                            SetKeepOnStage(bool);
        bool                            GetKeepOnStage();


    private:
        bool                            _setKeepOnStage(bool);
        bool                            _getKeepOnStage();
        bool                            _rotateCassette();
        bool                            _setCassetteDocked(bool, bool = false);
        bool                            _setCassetteRedocked();
        bool                            _getCassetteDocked();
        bool                            _getCassetteDockTimeStamp(time_t &);
        bool                            _logCassetteEvent(time_t ts, const wxString &, const wxString &);
        bool                            _updateCassetteOperator(const wxString &);
        wxString const                  _getCassetteOperator();
        bool                            _reloadCassette();
        bool                            _reloadOperators(wxArrayOperator &);
        bool                            _reloadEvents();

        void                            _testDB();

        bool                            _initializeDatabases();
        bool                            _initializeCassetteDatabase();
        bool                            _initializeOperatorsDatabase();
        bool                            _updateCartridgeData(HorusCartridge *);
        bool                            _insertOperator(const wxString &, const wxString &);
        bool                            _updateOperator(const wxString &, const wxString &);
        bool                            _deleteOperator(const wxString &);
        bool                            _fillCartridgesData();

        bool                            _saveDB();

        void                            _sendEvent(HorusDatabaseEvent);
        void                            _sendBackupEvent(const wxString &dbName);
        void                            _sendReloadEvent(time_t, const wxString &, const wxString &);

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
    HorusEventDatabaseData() :
        TimeStamp(wxDateTime::Now().GetTicks()),
        BackupFile(wxEmptyString),
        Operator(wxEmptyString),
        Message(wxEmptyString)
    {
        //TimeStamp = wxDateTime::Now().GetTicks();
    }

    HorusEventDatabaseData(time_t ts) :
        TimeStamp(ts),
        BackupFile(wxEmptyString),
        Operator(wxEmptyString),
        Message(wxEmptyString)
    {
    }
    ~HorusEventDatabaseData()
    {

    }

    time_t                              TimeStamp;
    wxString                            BackupFile;
    wxString                            Operator;
    wxString                            Message;
};


}

#endif // HORUSDATABASEPOOL_H
