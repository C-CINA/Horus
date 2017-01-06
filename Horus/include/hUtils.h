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

        /// \brief Load data from ressource file
        ///
        /// \param &t_data char* pointer to ressource
        /// \param t_dataSize DWORD& size of ressource
        /// \param t_name const wxString& ressource name
        /// \return bool operation completion status
        ///
        ///
        static bool                     LoadDataFromResource(char * &t_data, DWORD &t_dataSize, const wxString &t_name);

        /// \brief Get bitmap from ressource file, streamed
        ///
        /// \param t_data const char* pointer to ressource
        /// \param t_size const DWORD ressource size
        /// \return wxBitmap* bitmap
        ///
        ///
        static wxBitmap*                GetBitmapFromMemory(const char *t_data, const DWORD t_size);

        /// \brief Create a wxBitmap from ressource file
        ///
        /// \param t_name const wxString& ressource name
        /// \return wxBitmap* bitmap
        ///
        ///
        static wxBitmap*                CreateBitmapFromPNGResource(const wxString &t_name);

        /// \brief Returns a valid UUID
        ///
        /// \param nSize int max length of created UUID
        /// \return wxString const newly created UUID
        ///
        ///
        static wxString const           CreateGUID(int nSize = 32);

        /// \brief Returns a formated timestamp, filesystem friendly if fsfriendly is true.
        ///
        /// \param now wxDateTime timestamp source date/time
        /// \param fsfriendly bool filesystem friendly flag
        /// \return wxString const formatted timestamp
        ///
        ///
        static wxString const           GetTimeStampString(wxDateTime now, bool fsfriendly);

        /// \brief Returns a formated timestamp, filesystem friendly if fsfriendly is true.
        ///
        /// \param ts time_t timestamp source date/time
        /// \param fsfriendly bool filesystem friendly flag
        /// \return wxString const formatted timestamp
        ///
        ///
        static wxString const           GetTimeStampString(time_t ts, bool fsfriendly);

        /// \brief Comparator callback function, used by wxArrayOperator::Sort()
        ///
        /// \param l Operator** first operator
        /// \param h Operator** second operator
        /// \return wxCMPFUNC_CONV compare result
        ///
        ///
        static wxCMPFUNC_CONV           CompareOperators(Operator **l, Operator **h);
};

#endif // HUTILS_H
