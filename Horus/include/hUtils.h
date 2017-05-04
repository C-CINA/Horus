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
        /// \brief Constructor
        ///
        /// \param name const wxString& operator name
        /// \param uuid const wxString& operator uuid
        ///
        ///
        Operator(const wxString &name, const wxString &uuid) : Name(name), UUID(uuid)
        {
        }

        /// \brief Destructor
        ///
        ///
        ///
        ~Operator()
        {
        }

        wxString Name; ///< Operator name
        wxString UUID; ///< Operator UUID
};

/// \class wxArrayOperator
/// \inherit wxObjArray
/// \brief Declaration of Operator dynamic array class, (see wxWidget::wxObjArray class)
///
WX_DECLARE_OBJARRAY(Operator, wxArrayOperator);

/// \brief Class wxHorusArrayOperator, extends wxArrayOperator class with embedded sorting feature
///
class wxHorusArrayOperator : public wxArrayOperator
{
    public:
        /// \brief Sort operators alphabetically
        ///
        /// \return void
        ///
        ///
        void                                SortOperators();

    private:
        /// \brief Sorting function, ignoring case.
        ///
        /// \param l Operator** first operator to compare to
        /// \param h Operator** second operator to compare to
        /// \return wxCMPFUNC_CONV compare result (see wxString::CmpNoCase());
        ///
        ///
        static wxCMPFUNC_CONV               _compareOperators(Operator **l, Operator **h);
};

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

        /// \brief Raise a window, identified by its name (only first windowName::Len() is compared)
        ///
        /// \param windowName const wxString& window name
        /// \return bool true if found and raised, otherwise false
        ///
        ///
        static bool                     RaiseWindowNamed(const wxString &windowName);

};

#endif // HUTILS_H
