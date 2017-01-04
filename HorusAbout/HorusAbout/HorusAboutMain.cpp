/// -----------------------------------------------------------------------------
///
/// \file HorusAboutMain.cpp
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

#include "HorusAboutMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(HorusAboutDialog)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#ifndef HORUSAPP_BUILD
//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}
#endif // 0

//(*IdInit(HorusAboutDialog)
const long HorusAboutDialog::ID_STATICBITMAP4 = wxNewId();
const long HorusAboutDialog::ID_STATICBITMAP3 = wxNewId();
const long HorusAboutDialog::ID_STATICBITMAP1 = wxNewId();
const long HorusAboutDialog::ID_STATICLINE7 = wxNewId();
const long HorusAboutDialog::ID_STATICBITMAP2 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT1 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT14 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT16 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT2 = wxNewId();
const long HorusAboutDialog::ID_STATICLINE3 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT11 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT9 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT15 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT7 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT13 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT10 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT12 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT8 = wxNewId();
const long HorusAboutDialog::ID_HYPERLINKCTRL1 = wxNewId();
const long HorusAboutDialog::ID_STATICLINE4 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT5 = wxNewId();
const long HorusAboutDialog::ID_STATICLINE6 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT3 = wxNewId();
const long HorusAboutDialog::ID_STATICLINE1 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT6 = wxNewId();
const long HorusAboutDialog::ID_STATICLINE5 = wxNewId();
const long HorusAboutDialog::ID_STATICTEXT4 = wxNewId();
const long HorusAboutDialog::ID_TOGGLEBUTTON1 = wxNewId();
const long HorusAboutDialog::ID_TEXTCTRL1 = wxNewId();
const long HorusAboutDialog::ID_STATICLINE2 = wxNewId();
const long HorusAboutDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HorusAboutDialog,wxDialog)
    //(*EventTable(HorusAboutDialog)
    //*)
END_EVENT_TABLE()

/// \brief Constructor
///
/// \param parent wxWindow* Parent window
/// \param id wxWindowID ID for this dialog
///
///
HorusAboutDialog::HorusAboutDialog(wxWindow* parent, wxWindowID id)
{
    //(*Initialize(HorusAboutDialog)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer29;
    wxBoxSizer* BoxSizer19;
    wxBoxSizer* BoxSizer15;
    wxBoxSizer* BoxSizer20;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer21;
    wxBoxSizer* BoxSizer13;
    wxBoxSizer* BoxSizer23;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer16;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer18;
    wxBoxSizer* BoxSizer28;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer27;
    wxBoxSizer* BoxSizer17;
    wxBoxSizer* BoxSizer24;
    wxBoxSizer* BoxSizer26;
    wxBoxSizer* BoxSizer9;
    wxBoxSizer* BoxSizer22;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer25;

    Create(parent, wxID_ANY, _("wxWidgets app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer15->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wstaticbitmapCompany3 = new wxStaticBitmap(this, ID_STATICBITMAP4, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_STATICBITMAP4"));
    BoxSizer15->Add(m_wstaticbitmapCompany3, 0, wxALL|wxEXPAND, 5);
    BoxSizer15->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wstaticbitmapCompany2 = new wxStaticBitmap(this, ID_STATICBITMAP3, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_STATICBITMAP3"));
    BoxSizer15->Add(m_wstaticbitmapCompany2, 0, wxALL|wxEXPAND, 5);
    BoxSizer15->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wstaticbitmapCompany1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_STATICBITMAP1"));
    BoxSizer15->Add(m_wstaticbitmapCompany1, 0, wxALL|wxEXPAND, 5);
    BoxSizer15->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer15, 1, wxALL|wxEXPAND, 0);
    BoxSizer1->Add(BoxSizer4, 0, wxALL|wxEXPAND, 0);
    StaticLine7 = new wxStaticLine(this, ID_STATICLINE7, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE7"));
    BoxSizer1->Add(StaticLine7, 0, wxEXPAND, 5);
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer10->Add(-1,-1,1, wxALL|wxALIGN_TOP, 5);
    BoxSizer6 = new wxBoxSizer(wxVERTICAL);
    BoxSizer20 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer17 = new wxBoxSizer(wxVERTICAL);
    BoxSizer17->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer28->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer21 = new wxBoxSizer(wxVERTICAL);
    m_wstaticbitmapLogo = new wxStaticBitmap(this, ID_STATICBITMAP2, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_STATICBITMAP2"));
    BoxSizer21->Add(m_wstaticbitmapLogo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer28->Add(BoxSizer21, 0, wxALIGN_LEFT, 10);
    BoxSizer28->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer17->Add(BoxSizer28, 0, wxEXPAND, 5);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    m_wtextProgramName = new wxStaticText(this, ID_STATICTEXT1, _("P"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont m_wtextProgramNameFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !m_wtextProgramNameFont.Ok() ) m_wtextProgramNameFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_wtextProgramNameFont.SetPointSize(20);
    m_wtextProgramNameFont.SetWeight(wxFONTWEIGHT_BOLD);
    m_wtextProgramName->SetFont(m_wtextProgramNameFont);
    BoxSizer11->Add(m_wtextProgramName, 0, wxALL, 5);
    BoxSizer26 = new wxBoxSizer(wxVERTICAL);
    BoxSizer26->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wtextProgramPitch = new wxStaticText(this, ID_STATICTEXT14, _("tag"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT, _T("ID_STATICTEXT14"));
    wxFont m_wtextProgramPitchFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !m_wtextProgramPitchFont.Ok() ) m_wtextProgramPitchFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_wtextProgramPitchFont.SetPointSize(9);
    m_wtextProgramPitchFont.SetStyle(wxFONTSTYLE_ITALIC);
    m_wtextProgramPitch->SetFont(m_wtextProgramPitchFont);
    BoxSizer26->Add(m_wtextProgramPitch, 1, wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer27 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT16, _("v"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT16"));
    BoxSizer27->Add(StaticText6, 0, wxALL|wxEXPAND, 5);
    m_wtextProgramVersion = new wxStaticText(this, ID_STATICTEXT2, _("0.0.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
    BoxSizer27->Add(m_wtextProgramVersion, 1, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5);
    BoxSizer26->Add(BoxSizer27, 1, wxALIGN_RIGHT, 5);
    BoxSizer11->Add(BoxSizer26, 0, wxALL|wxEXPAND, 0);
    BoxSizer17->Add(BoxSizer11, 0, wxLEFT|wxRIGHT|wxEXPAND, 10);
    BoxSizer17->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer20->Add(BoxSizer17, 0, wxALL, 0);
    BoxSizer6->Add(BoxSizer20, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer10->Add(BoxSizer6, 0, wxALL|wxEXPAND, 0);
    BoxSizer10->Add(-1,-1,1, wxALL, 5);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxDefaultPosition, wxSize(2,-1), wxLI_VERTICAL, _T("ID_STATICLINE3"));
    BoxSizer14->Add(StaticLine3, 0, wxALL|wxEXPAND, 5);
    BoxSizer9 = new wxBoxSizer(wxVERTICAL);
    BoxSizer18 = new wxBoxSizer(wxVERTICAL);
    BoxSizer19 = new wxBoxSizer(wxVERTICAL);
    BoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT11, _("(c)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    wxFont StaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !StaticText3Font.Ok() ) StaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    StaticText3Font.SetPointSize(9);
    StaticText3->SetFont(StaticText3Font);
    BoxSizer23->Add(StaticText3, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_wtextCopyrightYear = new wxStaticText(this, ID_STATICTEXT9, _("20xx"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    wxFont m_wtextCopyrightYearFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !m_wtextCopyrightYearFont.Ok() ) m_wtextCopyrightYearFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_wtextCopyrightYearFont.SetPointSize(9);
    m_wtextCopyrightYear->SetFont(m_wtextCopyrightYearFont);
    BoxSizer23->Add(m_wtextCopyrightYear, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT15, _("-"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    wxFont StaticText7Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !StaticText7Font.Ok() ) StaticText7Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    StaticText7Font.SetPointSize(9);
    StaticText7->SetFont(StaticText7Font);
    BoxSizer23->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    m_wtextCopyrightAuthorName = new wxStaticText(this, ID_STATICTEXT7, _("John Doe"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    wxFont m_wtextCopyrightAuthorNameFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !m_wtextCopyrightAuthorNameFont.Ok() ) m_wtextCopyrightAuthorNameFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_wtextCopyrightAuthorNameFont.SetPointSize(9);
    m_wtextCopyrightAuthorName->SetFont(m_wtextCopyrightAuthorNameFont);
    BoxSizer23->Add(m_wtextCopyrightAuthorName, 0, wxTOP|wxBOTTOM, 5);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT13, _("<"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    wxFont StaticText5Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !StaticText5Font.Ok() ) StaticText5Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    StaticText5Font.SetPointSize(9);
    StaticText5->SetFont(StaticText5Font);
    BoxSizer23->Add(StaticText5, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wtextCopyrightAuthorAddress = new wxStaticText(this, ID_STATICTEXT10, _("john.doe@nowhere.com"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    wxFont m_wtextCopyrightAuthorAddressFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !m_wtextCopyrightAuthorAddressFont.Ok() ) m_wtextCopyrightAuthorAddressFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_wtextCopyrightAuthorAddressFont.SetPointSize(9);
    m_wtextCopyrightAuthorAddressFont.SetStyle(wxFONTSTYLE_ITALIC);
    m_wtextCopyrightAuthorAddress->SetFont(m_wtextCopyrightAuthorAddressFont);
    BoxSizer23->Add(m_wtextCopyrightAuthorAddress, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT12, _(">"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    wxFont StaticText4Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !StaticText4Font.Ok() ) StaticText4Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    StaticText4Font.SetPointSize(9);
    StaticText4->SetFont(StaticText4Font);
    BoxSizer23->Add(StaticText4, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer19->Add(BoxSizer23, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
    m_wtextCopyrightCompany = new wxStaticText(this, ID_STATICTEXT8, _("Company"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    wxFont m_wtextCopyrightCompanyFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !m_wtextCopyrightCompanyFont.Ok() ) m_wtextCopyrightCompanyFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_wtextCopyrightCompanyFont.SetPointSize(9);
    m_wtextCopyrightCompanyFont.SetWeight(wxFONTWEIGHT_BOLD);
    m_wtextCopyrightCompany->SetFont(m_wtextCopyrightCompanyFont);
    BoxSizer29->Add(m_wtextCopyrightCompany, 0, wxALL, 5);
    m_whyperlinkURL = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL1, _("url"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL1"));
    BoxSizer29->Add(m_whyperlinkURL, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer19->Add(BoxSizer29, 0, wxALL|wxALIGN_RIGHT, 0);
    BoxSizer18->Add(BoxSizer19, 0, wxALL|wxALIGN_RIGHT, 5);
    StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    BoxSizer18->Add(StaticLine4, 0, wxALL|wxEXPAND, 0);
    BoxSizer22 = new wxBoxSizer(wxVERTICAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT5, _("Build Informations"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT5"));
    wxFont StaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !StaticText1Font.Ok() ) StaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    StaticText1Font.SetPointSize(9);
    StaticText1Font.SetWeight(wxFONTWEIGHT_BOLD);
    StaticText1->SetFont(StaticText1Font);
    BoxSizer22->Add(StaticText1, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    StaticLine6 = new wxStaticLine(this, ID_STATICLINE6, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE6"));
    BoxSizer22->Add(StaticLine6, 0, wxALL|wxEXPAND, 0);
    BoxSizer18->Add(BoxSizer22, 1, wxALL|wxALIGN_RIGHT, 5);
    m_wtextBuildInfos = new wxStaticText(this, ID_STATICTEXT3, _("gcc-xxx"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
    BoxSizer18->Add(m_wtextBuildInfos, 0, wxALL|wxEXPAND, 5);
    BoxSizer18->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer9->Add(BoxSizer18, 0, wxALL|wxALIGN_RIGHT, 0);
    BoxSizer14->Add(BoxSizer9, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer10->Add(BoxSizer14, 0, wxEXPAND, 0);
    BoxSizer8->Add(BoxSizer10, 1, wxALL|wxEXPAND, 0);
    BoxSizer7->Add(BoxSizer8, 0, wxALL|wxEXPAND, 0);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    BoxSizer7->Add(StaticLine1, 0, wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer7, 0, wxEXPAND, 5);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer13->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer16 = new wxBoxSizer(wxVERTICAL);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT6, _("License Informations"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT6"));
    wxFont StaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !StaticText2Font.Ok() ) StaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    StaticText2Font.SetPointSize(9);
    StaticText2Font.SetWeight(wxFONTWEIGHT_BOLD);
    StaticText2->SetFont(StaticText2Font);
    BoxSizer16->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    StaticLine5 = new wxStaticLine(this, ID_STATICLINE5, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE5"));
    BoxSizer16->Add(StaticLine5, 0, wxALL|wxEXPAND, 0);
    BoxSizer25->Add(BoxSizer16, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer13->Add(BoxSizer25, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer13, 0, wxALL|wxEXPAND, 0);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer12->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer24 = new wxBoxSizer(wxVERTICAL);
    m_wtextCopyrightLicenseShort = new wxStaticText(this, ID_STATICTEXT4, _("Released under the terms of...."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer24->Add(m_wtextCopyrightLicenseShort, 1, wxALL, 5);
    BoxSizer12->Add(BoxSizer24, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_toggleLicense = new wxToggleButton(this, ID_TOGGLEBUTTON1, _("Show License"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
    BoxSizer12->Add(m_toggleLicense, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer12, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 0);
    BoxSizer1->Add(BoxSizer2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 0);
    BoxSizer1->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_textCopyrightLicenseLong = new wxTextCtrl(this, ID_TEXTCTRL1, _("blah\n\nblah blah blah blah blah blah blah blah blah blah blah \nblah blah blah blah blah blah blah blah blah \n\nblah blah blah blah blah blah blah blah blah \nblah blah blah blah blah blah blah blah blah blah \n"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_LEFT, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    m_textCopyrightLicenseLong->SetMinSize(wxSize(580,300));
    m_textCopyrightLicenseLong->Hide();
    wxFont m_textCopyrightLicenseLongFont(9,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Calibri"),wxFONTENCODING_DEFAULT);
    m_textCopyrightLicenseLong->SetFont(m_textCopyrightLicenseLongFont);
    BoxSizer5->Add(m_textCopyrightLicenseLong, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer5, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 0);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    BoxSizer1->Add(StaticLine2, 0, wxALL|wxEXPAND, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(this, wxID_OK, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
    BoxSizer3->Add(Button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    m_timer.SetOwner(this, ID_TIMER1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&HorusAboutDialog::OnToggleButton1Toggle);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&HorusAboutDialog::OnTimer1Trigger);
    //*)

    wxSize s = m_textCopyrightLicenseLong->GetMinSize();
    wxSize ws = GetMinSize();

    SetMinSize(wxSize(s.GetWidth() + 30, ws.GetHeight()));
    //Fit();

    HorusAboutInformations info;
    SetInformations(info);
}

/// \brief Destructor
///
HorusAboutDialog::~HorusAboutDialog()
{
    //(*Destroy(HorusAboutDialog)
    //*)
}

/// \brief Set window informations
///
/// \param infos const HorusAboutInformations& Information structure filled by caller
/// \return void
///
///
void HorusAboutDialog::SetInformations(const HorusAboutInformations &infos)
{
    m_wtextProgramName->SetLabel(infos.Program.Name);
    m_wtextProgramVersion->SetLabel(infos.Program.Version);
    m_wtextProgramPitch->SetLabel(infos.Program.Pitch);
    m_wtextCopyrightYear->SetLabel(infos.Copyright.Year);
    m_wtextCopyrightAuthorName->SetLabel(infos.Copyright.AuthorName);
    m_wtextCopyrightAuthorAddress->SetLabel(infos.Copyright.AuthorAddress);
    m_wtextCopyrightCompany->SetLabel(infos.Copyright.Company);
    m_whyperlinkURL->SetLabel(infos.Copyright.URL);
    m_whyperlinkURL->SetURL(infos.Copyright.URL);
    m_wtextCopyrightLicenseShort->SetLabel(infos.Copyright.LicenseExcerpt);
    m_textCopyrightLicenseLong->SetValue(infos.Copyright.LicenseComplete);
    m_wtextBuildInfos->SetLabel(infos.BuildInfos);
    m_wstaticbitmapLogo->SetBitmap(infos.Bitmaps.Program);
    m_wstaticbitmapCompany1->SetBitmap(infos.Bitmaps.Company1);
    m_wstaticbitmapCompany2->SetBitmap(infos.Bitmaps.Company2);
    m_wstaticbitmapCompany3->SetBitmap(infos.Bitmaps.Company3);

    SetTitle(wxT("About ") + infos.Program.Name);

    Fit();
    CenterOnParent();
}

/// \brief Handles close box
///
/// \param event wxCommandEvent& event
/// \return void
///
///
void HorusAboutDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

/// \brief Handles license button click
///
/// \param event wxCommandEvent& event
/// \return void
///
///
void HorusAboutDialog::OnToggleButton1Toggle(wxCommandEvent& event)
{
    m_textCopyrightLicenseLong->Show(m_toggleLicense->GetValue());

    m_toggleLicense->SetLabel(m_toggleLicense->GetValue() ? wxT("Hide License") : wxT("Show License"));

#if 1
    if (m_timer.IsRunning())
    {
        wxTimerEvent ev;

        m_timer.Stop();

        // Reset logo original position
        OnTimer1Trigger(ev);
    }
    else
        m_timer.Start(300, false);
#endif

    Fit();
}

/// \brief Event handler for Timer widget, it rotate the program's logo
///
/// \param event wxTimerEvent& event
/// \return void
///
///
void HorusAboutDialog::OnTimer1Trigger(wxTimerEvent& event)
{
    static wxImage      img = m_wstaticbitmapLogo->GetBitmap().ConvertToImage();
    static wxImage      timg = wxImage(wxSize(img.GetWidth(), img.GetHeight()));
    static wxPoint      p = wxPoint(img.GetWidth() / 2, img.GetHeight() / 2);
    static double       angle = 0.0;
    static const double step = 4.0;
    static bool         direction = true;

    if (m_timer.IsRunning())
    {
        if (direction)
        {
            angle += step;

            if (angle >= 30.0)
                direction = !direction;
        }
        else
        {
            angle -= step;

            if (angle <= -30.0)
                direction = !direction;

        }

        // Create rotated image
        wxImage rimg = img.Rotate((angle * (M_PI / 180.0)), p, true);

        timg.Paste(rimg, -((rimg.GetWidth() - img.GetWidth()) / 2), -((rimg.GetHeight() - img.GetHeight()) / 2));

        m_wstaticbitmapLogo->SetBitmap(timg);
    }
    else
    {
        angle = 0.0;
        direction = true;
        m_wstaticbitmapLogo->SetBitmap(img);
    }

    event.Skip();
}
