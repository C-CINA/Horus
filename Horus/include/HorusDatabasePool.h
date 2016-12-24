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

        bool                            IsOK();
        bool                            Initialize(HorusCassette *cassette);
        bool                            ReloadData(wxArrayOperator &operators, HorusEventLoggerCallbackInterface *logger);
        bool                            UpdateCartridge(HorusCartridge *cartridge);
        bool                            AddOperator(const wxString &name, const wxString &uuid);
        bool                            UpdateOperator(const wxString &name, const wxString &uuid);
        bool                            DeleteOperator(const wxString &uuid);
        bool                            SetCassetteOperator(const wxString &uuid);
        wxString const                  GetCassetteOperator();
        bool                            LogCassetteEvent(time_t ts, const wxString &op, const wxString &message);
        bool                            SetCassetteDocked(bool);
        bool                            GetCassetteDocked();
        bool                            SetKeepOnStage(bool);
        bool                            GetKeepOnStage();


    private:
        bool                            _setKeepOnStage(bool keep);
        bool                            _getKeepOnStage();
        bool                            _setCassetteDocked(bool);
        bool                            _getCassetteDocked();
        bool                            _logCassetteEvent(time_t ts, const wxString &op, const wxString &message);
        bool                            _updateCassetteOperator(const wxString &uuid);
        wxString const                  _getCassetteOperator();
        bool                            _reloadCassette();
        bool                            _reloadOperators(wxArrayOperator &operators);
        bool                            _reloadEvents(HorusEventLoggerCallbackInterface *logger);

        void                            _testDB();

        bool                            _initializeDatabases();
        bool                            _initializeCassetteDatabase();
        bool                            _initializeOperatorsDatabase();
        bool                            _updateCartridgeData(HorusCartridge *slot);
        bool                            _insertOperator(const wxString &name, const wxString &uuid);
        bool                            _updateOperator(const wxString &name, const wxString &uuid);
        bool                            _deleteOperator(const wxString &uuid);
        bool                            _fillCartridgesData();

        bool                            _saveDB();


    private:
        bool                            m_initialized;
        wxString                        m_dbPath;
        HorusCassette                  *m_cassette;

        wxSQLite3Database               m_dbCassette;
        wxSQLite3Database               m_dbOperators;

};

}

#endif // HORUSDATABASEPOOL_H
