/// -----------------------------------------------------------------------------
///
/// \file hUtils.cpp
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

hUtils::hUtils()
{
    //ctor
}

hUtils::~hUtils()
{
    //dtor
}

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

wxBitmap* hUtils::GetBitmapFromMemory(const char *t_data, const DWORD t_size)
{
    wxMemoryInputStream a_is(t_data, t_size);

    return new wxBitmap(wxImage(a_is, wxBITMAP_TYPE_PNG, -1), -1);
}

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

wxString const hUtils::GetTimeStampString(wxDateTime now, bool fsfriendly)
{
    return ((wxString::Format(wxT("%d%c%02d%c%02d%c%02d%c%02d%c%02d"),
                              now.GetYear(), (fsfriendly ? '-' : '/'), now.GetMonth() + 1, (fsfriendly ? '-' : '/'), now.GetDay(), (fsfriendly ? '_' : ' '),
                              now.GetHour(), (fsfriendly ? '.' : ':'), now.GetMinute(), (fsfriendly ? '.' : ':'), now.GetSecond())));

}

wxString const hUtils::GetTimeStampString(time_t now, bool fsfriendly)
{
    wxDateTime dt(now);

    return GetTimeStampString(dt, fsfriendly);
}

// Magic of Operator dynamic array is just below
//
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxArrayOperator);

void wxHorusArrayOperator::SortOperators()
{
    wxArrayOperator::Sort(_compareOperators);
}

wxCMPFUNC_CONV wxHorusArrayOperator::_compareOperators(Operator **l, Operator **h)
{
    return (*l)->Name.CmpNoCase((*h)->Name);
}

