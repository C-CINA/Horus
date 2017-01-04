/// -----------------------------------------------------------------------------
///
/// \file HorusAboutMain.h
///
/// \copyright Copyright (c) 2016-2017 Daniel Caujolle-Bert <daniel.caujolle-bert@unibas.ch>
/// \brief Horus Logger
/// \author Daniel Caujolle-Bert <daniel.caujolle-bert@unibas.ch>
///
/// \license
/// All rights reserved. This program and the accompanying materials
/// are made available under the terms of the GNU Public License v2.0
/// which accompanies this distribution, and is available at
/// http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
///
/// This file is part of Horus.
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

#ifndef HORUSABOUTMAIN_H
#define HORUSABOUTMAIN_H

//(*Headers(HorusAboutDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>
#include <wx/statline.h>
#include <wx/hyperlink.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/timer.h>
//*)

struct HorusAboutInformations
{
    struct
    {
        wxString Name;
        wxString Version;
        wxString Pitch;
    } Program;

    struct
    {
        wxString Year;
        wxString AuthorName;
        wxString AuthorAddress;
        wxString Company;
        wxString URL;
        wxString LicenseExcerpt;
        wxString LicenseComplete;
    } Copyright;

    struct
    {
        wxBitmap Program;
        wxBitmap Company1;
        wxBitmap Company2;
        wxBitmap Company3;
    } Bitmaps;

    wxString BuildInfos;

};

class HorusAboutDialog: public wxDialog
{
    public:

        HorusAboutDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~HorusAboutDialog();

        void                            SetInformations(const HorusAboutInformations &);

    private:

        //(*Handlers(HorusAboutDialog)
        void OnQuit(wxCommandEvent& event);
        void OnToggleButton1Toggle(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        //*)

        //(*Identifiers(HorusAboutDialog)
        static const long ID_STATICBITMAP4;
        static const long ID_STATICBITMAP3;
        static const long ID_STATICBITMAP1;
        static const long ID_STATICLINE7;
        static const long ID_STATICBITMAP2;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT16;
        static const long ID_STATICTEXT2;
        static const long ID_STATICLINE3;
        static const long ID_STATICTEXT11;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT15;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT12;
        static const long ID_STATICTEXT8;
        static const long ID_HYPERLINKCTRL1;
        static const long ID_STATICLINE4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICLINE6;
        static const long ID_STATICTEXT3;
        static const long ID_STATICLINE1;
        static const long ID_STATICTEXT6;
        static const long ID_STATICLINE5;
        static const long ID_STATICTEXT4;
        static const long ID_TOGGLEBUTTON1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICLINE2;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(HorusAboutDialog)
        wxHyperlinkCtrl* m_whyperlinkURL;
        wxToggleButton* m_toggleLicense;
        wxStaticBitmap* m_wstaticbitmapLogo;
        wxStaticText* m_wtextCopyrightLicenseShort;
        wxStaticText* StaticText2;
        wxStaticLine* StaticLine6;
        wxStaticBitmap* m_wstaticbitmapCompany3;
        wxStaticBitmap* m_wstaticbitmapCompany1;
        wxStaticText* m_wtextCopyrightAuthorAddress;
        wxButton* Button1;
        wxStaticText* StaticText6;
        wxStaticText* StaticText1;
        wxStaticText* m_wtextCopyrightAuthorName;
        wxStaticText* StaticText3;
        wxStaticText* m_wtextCopyrightCompany;
        wxStaticLine* StaticLine7;
        wxTextCtrl* m_textCopyrightLicenseLong;
        wxStaticBitmap* m_wstaticbitmapCompany2;
        wxStaticLine* StaticLine4;
        wxStaticLine* StaticLine2;
        wxStaticText* m_wtextBuildInfos;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxStaticLine* StaticLine3;
        wxStaticLine* StaticLine1;
        wxStaticText* m_wtextProgramPitch;
        wxStaticText* m_wtextCopyrightYear;
        wxBoxSizer* BoxSizer1;
        wxStaticText* m_wtextProgramName;
        wxStaticText* m_wtextProgramVersion;
        wxTimer m_timer;
        wxStaticText* StaticText4;
        wxStaticLine* StaticLine5;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // HORUSABOUTMAIN_H
