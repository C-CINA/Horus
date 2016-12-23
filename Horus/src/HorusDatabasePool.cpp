#include "../HorusMain.h"

namespace Horus
{

HorusDatabasePool::HorusDatabasePool() : m_initialized(false), m_cassette(NULL)
{
    //ctor

    m_dbPath = wxStandardPaths::Get().GetUserDataDir() + wxFILE_SEP_PATH + wxT("Databases");

    if (! wxFileName::DirExists(m_dbPath))
        wxFileName::Mkdir(m_dbPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
}

HorusDatabasePool::~HorusDatabasePool()
{
    //dtor
    //_saveDB();

    if (m_dbCassette.IsOpen())
        m_dbCassette.Close();

    if (m_dbOperators.IsOpen())
        m_dbOperators.Close();

    wxSQLite3Database::ShutdownSQLite();
}

}
