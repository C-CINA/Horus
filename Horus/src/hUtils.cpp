#include "../HorusMain.h"

hUtils::hUtils()
{
    //ctor
}

hUtils::~hUtils()
{
    //dtor
}

/// \brief Load data from ressource file
///
/// \param &t_data char* pointer to ressource
/// \param t_dataSize DWORD& size of ressource
/// \param t_name const wxString& ressource name
/// \return bool operation completion status
///
///
bool hUtils::LoadDataFromResource(char * &t_data, DWORD &t_dataSize, const wxString &t_name)
{
    bool     r_result    = false;
    HGLOBAL  a_resHandle = 0;
    HRSRC    a_resource;

    a_resource = FindResource(0, t_name.wchar_str(), RT_RCDATA);

    if(0 != a_resource)
    {
        a_resHandle = LoadResource(NULL, a_resource);

        if (0 != a_resHandle)
        {
            t_data = (char *)LockResource(a_resHandle);
            t_dataSize = SizeofResource(NULL, a_resource);
            r_result = true;
        }
    }

    return r_result;
}

/// \brief Get bitmap from ressource file, streamed
///
/// \param t_data const char* pointer to ressource
/// \param t_size const DWORD ressource size
/// \return wxBitmap* bitmap
///
///
wxBitmap* hUtils::GetBitmapFromMemory(const char *t_data, const DWORD t_size)
{
    wxMemoryInputStream a_is(t_data, t_size);

    return new wxBitmap(wxImage(a_is, wxBITMAP_TYPE_PNG, -1), -1);
}

/// \brief Create a wxBitmap from ressource file
///
/// \param t_name const wxString& ressource name
/// \return wxBitmap* bitmap
///
///
wxBitmap* hUtils::CreateBitmapFromPNGResource(const wxString &t_name)
{
    wxBitmap   *r_bitmapPtr = 0;
    char       *a_data      = 0;
    DWORD       a_dataSize  = 0;
    wxString    resName = t_name;

    // Windows theming is off, load non themed resource
    if (! IsThemeActive())
        resName += wxT("_NOTHEME");

    if(hUtils::LoadDataFromResource(a_data, a_dataSize, resName))
        r_bitmapPtr = hUtils::GetBitmapFromMemory(a_data, a_dataSize);
    else
    {
        // Fallback
        if(hUtils::LoadDataFromResource(a_data, a_dataSize, t_name))
            r_bitmapPtr = hUtils::GetBitmapFromMemory(a_data, a_dataSize);
    }

    return r_bitmapPtr;
}

/// \brief Create a UUID
///
/// \param nSize int lenth
/// \return wxString UUID
///
///
wxString const hUtils::CreateGUID(int nSize)
{
    if (nSize < 0 || nSize > 32)
        nSize = 32;

#ifdef __WXMSW__
    GUID guid;
    short unsigned *str;

    CoCreateGuid(&guid);
    UuidToString((UUID*)&guid, &str);
    wxString unique( (LPTSTR)str );
    RpcStringFree( &str );
    unique.Replace("-", "");

    return ( unique.Left( nSize ) );
#else // untested
    uuid_t guid;
    uuid_string str;

    string_out[36] = 0;
    uuid_generate(guid);
    uuid_unparse(guid, str);
    wxString unique( (LPTSTR)str );
    unique.Replace("-", "");
    return ( unique.Left( nSize ) );
#endif

    return wxT("Error-from-CreateGUID");
}

/// \brief Get a timestamp formatted string, possibily filesystem friendly.
///
/// \param now wxDateTime Date/Time to put in the timestamp
/// \param fsfriendly bool Make it filesystem friendly.
/// \return wxString const Returns a formatted string.
///
///
wxString const hUtils::GetTimeStampString(wxDateTime now, bool fsfriendly)
{
    return ((wxString::Format(wxT("%d%c%02d%c%02d%c%02d%c%02d%c%02d"),
                              now.GetYear(), (fsfriendly ? '-' : '/'), now.GetMonth() + 1, (fsfriendly ? '-' : '/'), now.GetDay(), (fsfriendly ? '_' : ' '),
                              now.GetHour(), (fsfriendly ? '.' : ':'), now.GetMinute(), (fsfriendly ? '.' : ':'), now.GetSecond())));

}

/// \brief Get a timestamp formatted string, possibily filesystem friendly.
///
/// \param now time_t ticks to put in the timestamp
/// \param fsfriendly bool Make it filesystem friendly.
/// \return wxString const Returns a formatted string.
///
///
wxString const hUtils::GetTimeStampString(time_t now, bool fsfriendly)
{
    wxDateTime dt(now);

    return GetTimeStampString(dt, fsfriendly);
}


/// \brief Sort function used for Operator array
///
/// \param l Operator** first operator
/// \param h Operator** second operator
/// \return int string compare result
///
///
wxCMPFUNC_CONV hUtils::CompareOperators(Operator **l, Operator **h)
{
    return (*l)->Name.CmpNoCase((*h)->Name);
}


/// \brief Magic of Operator dynamic array is just below
///
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxArrayOperator);

