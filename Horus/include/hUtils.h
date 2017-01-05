/// -----------------------------------------------------------------------------
///
/// \file hUtils.h
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

#ifndef HUTILS_H
#define HUTILS_H

#include "../HorusMain.h"


/// \brief Class Operator
///
class Operator
{
    public:
        Operator() : Name(wxEmptyString), UUID(wxEmptyString)
        {
        }

        Operator(const wxString &name, const wxString &uuid) : Name(name), UUID(uuid)
        {
        }

        ~Operator()
        {
        }

        wxString Name;
        wxString UUID;
};

/// \brief Declaration of Operator dynamic array
///
WX_DECLARE_OBJARRAY(Operator, wxArrayOperator);

class hUtils
{
    public:
        hUtils();
        virtual ~hUtils();

        static bool                     LoadDataFromResource(char * &, DWORD &, const wxString  &);
        static wxBitmap*                GetBitmapFromMemory(const char *, const DWORD);
        static wxBitmap*                CreateBitmapFromPNGResource(const wxString &);

        static wxString const           CreateGUID(int = 32);

        static wxString const           GetTimeStampString(wxDateTime, bool);
        static wxString const           GetTimeStampString(time_t, bool);

        static wxCMPFUNC_CONV           CompareOperators(Operator **l, Operator **h);
};

#endif // HUTILS_H
