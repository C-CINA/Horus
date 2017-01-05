/// -----------------------------------------------------------------------------
///
/// \file HorusMain.cpp
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

#ifdef __WXDEBUG__
#define DEBUG
#endif // __WXDEBUG__

#include "HorusMain.h"

//(*InternalHeaders(HorusFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)


namespace Horus
{

static const wxString   PROGRAM_AUTHOR_NAME    = wxT("Daniel Caujolle-Bert");
static const wxString   PROGRAM_AUTHOR_ADDRESS = wxT("daniel.caujolle-bert@unibas.ch");
static const wxString   PROGRAM_COMPANY        = wxT("BioEM Lab");
static const wxString   PROGRAM_COMPANY_URL    = wxT("https://c-cina.unibas.ch/bioem");


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

//(*IdInit(HorusFrame)
const long HorusFrame::ID_BUTTON1 = wxNewId();
const long HorusFrame::ID_BUTTON3 = wxNewId();
const long HorusFrame::ID_BUTTON6 = wxNewId();
const long HorusFrame::ID_STATICTEXT3 = wxNewId();
const long HorusFrame::ID_SCROLLEDWINDOW1 = wxNewId();
const long HorusFrame::ID_STATICTEXT1 = wxNewId();
const long HorusFrame::ID_STATICTEXT2 = wxNewId();
const long HorusFrame::ID_CHECKBOX1 = wxNewId();
const long HorusFrame::ID_BUTTON2 = wxNewId();
const long HorusFrame::ID_SCROLLEDWINDOW2 = wxNewId();
const long HorusFrame::ID_CHOICE1 = wxNewId();
const long HorusFrame::ID_BUTTON4 = wxNewId();
const long HorusFrame::ID_BUTTON5 = wxNewId();
const long HorusFrame::ID_RICHTEXTCTRL1 = wxNewId();
const long HorusFrame::ID_PANEL1 = wxNewId();
const long HorusFrame::ID_BUTTON7 = wxNewId();
const long HorusFrame::ID_BUTTON8 = wxNewId();
const long HorusFrame::ID_TREECTRL1 = wxNewId();
const long HorusFrame::ID_PANEL3 = wxNewId();
const long HorusFrame::ID_STATICTEXT6 = wxNewId();
const long HorusFrame::ID_STATICTEXT4 = wxNewId();
const long HorusFrame::ID_STATICTEXT5 = wxNewId();
const long HorusFrame::ID_GRID1 = wxNewId();
const long HorusFrame::ID_RICHTEXTCTRL2 = wxNewId();
const long HorusFrame::ID_PANEL4 = wxNewId();
const long HorusFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long HorusFrame::ID_PANEL2 = wxNewId();
const long HorusFrame::ID_AUINOTEBOOK1 = wxNewId();
const long HorusFrame::idMenuQuit = wxNewId();
const long HorusFrame::idMenuAbout = wxNewId();
const long HorusFrame::ID_STATUSBAR1 = wxNewId();
//*)

const int HorusFrame::MAX_SASH_POSITION = 500;

BEGIN_EVENT_TABLE(HorusFrame,wxFrame)
    //(*EventTable(HorusFrame)
    //*)
    EVT_COMMAND(wxID_ANY, Horus::wxEVT_HORUS_CASSETTE, HorusFrame::OnCassetteEvent)
    EVT_COMMAND(wxID_ANY, Horus::wxEVT_HORUS_DATABASEPOOL, HorusFrame::OnDatabasePoolEvent)
END_EVENT_TABLE()

HorusFrame::HorusFrame(wxWindow* parent,wxWindowID id) : m_eventLoggerLockout(false)
{
#ifdef DEBUG
    wxLogWindow *logger = new wxLogWindow(this, _("Logging Window"));
    wxLog::SetActiveTarget(logger);
    wxLogStatus(wxT("Horus Started"));
#else
    wxLogNull noLog;
#endif

    // Hide the main window (a splashscreen will popup)
    Hide();

    //(*Initialize(HorusFrame)
    wxBoxSizer* BoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer19;
    wxBoxSizer* BoxSizer15;
    wxBoxSizer* BoxSizer20;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer21;
    wxMenuItem* MenuItem2;
    wxBoxSizer* BoxSizer13;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer23;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer16;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer18;
    wxBoxSizer* BoxSizer14;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxBoxSizer* BoxSizer27;
    wxBoxSizer* BoxSizer17;
    wxBoxSizer* BoxSizer24;
    wxBoxSizer* BoxSizer26;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer9;
    wxMenuBar* MenuBar1;
    wxBoxSizer* BoxSizer22;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;
    wxStaticBoxSizer* StaticBoxSizer5;
    wxBoxSizer* BoxSizer25;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    AuiNotebook1 = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH);
    AuiNotebook1->SetMinSize(wxSize(1200,500));
    m_wloggerPanel = new wxPanel(AuiNotebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    m_wcassetteSizer = new wxStaticBoxSizer(wxVERTICAL, m_wloggerPanel, _("  Cassette  "));
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    m_wdockCassette = new wxButton(m_wloggerPanel, ID_BUTTON1, _("Dock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    m_wdockCassette->SetToolTip(_("Dock the cassette."));
    BoxSizer13->Add(m_wdockCassette, 1, wxLEFT|wxRIGHT, 5);
    m_wredockCassette = new wxButton(m_wloggerPanel, ID_BUTTON3, _("Redock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    m_wredockCassette->SetToolTip(_("Dock the cassette again."));
    BoxSizer13->Add(m_wredockCassette, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wundockCassette = new wxButton(m_wloggerPanel, ID_BUTTON6, _("Undock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    m_wundockCassette->SetToolTip(_("Undock the cassette."));
    BoxSizer13->Add(m_wundockCassette, 1, wxLEFT|wxRIGHT, 5);
    BoxSizer8->Add(BoxSizer13, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, m_wloggerPanel, _("  Docked On  "));
    StaticBoxSizer1->Add(-1,-1,0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wdockedLabel = new wxStaticText(m_wloggerPanel, ID_STATICTEXT3, _("< ----/--/-- --:--:-- >"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT3"));
    m_wdockedLabel->SetToolTip(_("Docking time stamp."));
    StaticBoxSizer1->Add(m_wdockedLabel, 1, wxLEFT|wxRIGHT|wxEXPAND, 5);
    StaticBoxSizer1->Add(-1,-1,0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(StaticBoxSizer1, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wcassetteSizer->Add(BoxSizer8, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer14 = new wxBoxSizer(wxVERTICAL);
    BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer16 = new wxBoxSizer(wxVERTICAL);
    m_wscrolledCartridges = new wxScrolledWindow(m_wloggerPanel, ID_SCROLLEDWINDOW1, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW1"));
    m_wslotSizer = new wxBoxSizer(wxVERTICAL);
    m_wscrolledCartridges->SetSizer(m_wslotSizer);
    m_wslotSizer->Fit(m_wscrolledCartridges);
    m_wslotSizer->SetSizeHints(m_wscrolledCartridges);
    BoxSizer16->Add(m_wscrolledCartridges, 1, wxBOTTOM|wxEXPAND, 5);
    BoxSizer15->Add(BoxSizer16, 1, wxEXPAND, 5);
    BoxSizer14->Add(BoxSizer15, 1, wxEXPAND, 5);
    m_wcassetteSizer->Add(BoxSizer14, 1, wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer6->Add(m_wcassetteSizer, 1, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND, 5);
    BoxSizer4->Add(BoxSizer6, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    m_wstageSizer = new wxStaticBoxSizer(wxVERTICAL, m_wloggerPanel, _("  On Stage  "));
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(m_wloggerPanel, ID_STATICTEXT1, _("Loaded Cartridge: "), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
    BoxSizer7->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wcartridgeNum = new wxStaticText(m_wloggerPanel, ID_STATICTEXT2, _("<NONE>"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    m_wcartridgeNum->SetToolTip(_("Cartridge loaded on the stage."));
    BoxSizer7->Add(m_wcartridgeNum, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wstageSizer->Add(BoxSizer7, 0, wxALL|wxEXPAND, 5);
    BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    m_wscrolledStage = new wxScrolledWindow(m_wloggerPanel, ID_SCROLLEDWINDOW2, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW2"));
    BoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer19 = new wxBoxSizer(wxVERTICAL);
    m_wkeepOnStage = new wxCheckBox(m_wscrolledStage, ID_CHECKBOX1, _("Keep On Stage"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    m_wkeepOnStage->SetValue(false);
    m_wkeepOnStage->Disable();
    m_wkeepOnStage->SetToolTip(_("Keep the cartridge on the stage on undocking."));
    BoxSizer19->Add(m_wkeepOnStage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wunloadStage = new wxButton(m_wscrolledStage, ID_BUTTON2, _("Unload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    m_wunloadStage->Disable();
    m_wunloadStage->SetToolTip(_("Unload the cartridge."));
    BoxSizer19->Add(m_wunloadStage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer18->Add(BoxSizer19, 1, wxALL|wxEXPAND, 5);
    m_wscrolledStage->SetSizer(BoxSizer18);
    BoxSizer18->Fit(m_wscrolledStage);
    BoxSizer18->SetSizeHints(m_wscrolledStage);
    BoxSizer17->Add(m_wscrolledStage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wstageSizer->Add(BoxSizer17, 1, wxALL|wxEXPAND, 5);
    BoxSizer5->Add(m_wstageSizer, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, m_wloggerPanel, _("  Operator  "));
    BoxSizer10 = new wxBoxSizer(wxVERTICAL);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    m_woperatorChoice = new wxChoice(m_wloggerPanel, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    m_woperatorChoice->SetToolTip(_("Select an operator."));
    BoxSizer11->Add(m_woperatorChoice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12 = new wxBoxSizer(wxVERTICAL);
    m_waddOperator = new wxButton(m_wloggerPanel, ID_BUTTON4, _("+"), wxDefaultPosition, wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    m_waddOperator->SetToolTip(_("Add an operator"));
    BoxSizer12->Add(m_waddOperator, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wdeleteOperator = new wxButton(m_wloggerPanel, ID_BUTTON5, _("-"), wxDefaultPosition, wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    m_wdeleteOperator->Disable();
    m_wdeleteOperator->SetToolTip(_("Delete selected operator."));
    BoxSizer12->Add(m_wdeleteOperator, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer11->Add(BoxSizer12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer10->Add(BoxSizer11, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer2->Add(BoxSizer10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(StaticBoxSizer2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer4->Add(BoxSizer5, 0, wxTOP|wxRIGHT|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer4, 1, wxEXPAND, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    m_wtextLogger = new wxRichTextCtrl(m_wloggerPanel, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxRE_READONLY|wxSUNKEN_BORDER, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
    wxRichTextAttr rchtxtAttr_1;
    rchtxtAttr_1.SetFlags(wxTEXT_ATTR_TEXT_COLOUR|wxTEXT_ATTR_BACKGROUND_COLOUR|wxTEXT_ATTR_FONT_FACE|wxTEXT_ATTR_FONT_SIZE|wxTEXT_ATTR_FONT_WEIGHT|wxTEXT_ATTR_FONT_ITALIC|wxTEXT_ATTR_FONT_UNDERLINE|wxTEXT_ATTR_FONT|wxTEXT_ATTR_ALIGNMENT|wxTEXT_ATTR_LEFT_INDENT);
    rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    m_wtextLogger->SetBasicStyle(rchtxtAttr_1);
    m_wtextLogger->SetToolTip(_("Event logger."));
    BoxSizer9->Add(m_wtextLogger, 1, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer9, 1, wxEXPAND, 5);
    m_wloggerPanel->SetSizer(BoxSizer3);
    BoxSizer3->Fit(m_wloggerPanel);
    BoxSizer3->SetSizeHints(m_wloggerPanel);
    m_wbrowserPanel = new wxPanel(AuiNotebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer20 = new wxBoxSizer(wxVERTICAL);
    BoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
    SplitterWindow1 = new wxSplitterWindow(m_wbrowserPanel, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(300,300));
    SplitterWindow1->SetMinimumPaneSize(300);
    SplitterWindow1->SetSashGravity(0);
    Panel1 = new wxPanel(SplitterWindow1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizer22 = new wxBoxSizer(wxVERTICAL);
    BoxSizer27 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer27->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wtreeExpandAll = new wxButton(Panel1, ID_BUTTON7, _("+"), wxDefaultPosition, wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    m_wtreeExpandAll->SetToolTip(_("Expand All"));
    BoxSizer27->Add(m_wtreeExpandAll, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wtreeCollapseAll = new wxButton(Panel1, ID_BUTTON8, _("-"), wxDefaultPosition, wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    m_wtreeCollapseAll->SetToolTip(_("Collapse All"));
    BoxSizer27->Add(m_wtreeCollapseAll, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer22->Add(BoxSizer27, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    m_wtreeCassettes = new wxTreeCtrl(Panel1, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    m_wtreeCassettes->SetToolTip(_("Cassettes log tree."));
    BoxSizer22->Add(m_wtreeCassettes, 1, wxALL|wxEXPAND, 5);
    Panel1->SetSizer(BoxSizer22);
    BoxSizer22->Fit(Panel1);
    BoxSizer22->SetSizeHints(Panel1);
    Panel2 = new wxPanel(SplitterWindow1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    BoxSizer23 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, Panel2, _("  Cassette  "));
    BoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("  Operator  "));
    m_wbrowserOperator = new wxStaticText(Panel2, ID_STATICTEXT6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    m_wbrowserOperator->SetToolTip(_("Cassette operator."));
    StaticBoxSizer6->Add(m_wbrowserOperator, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer24->Add(StaticBoxSizer6, 1, wxALL, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("  Docked On  "));
    m_wbrowserDocked = new wxStaticText(Panel2, ID_STATICTEXT4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    m_wbrowserDocked->SetToolTip(_("Docking time stamp."));
    StaticBoxSizer4->Add(m_wbrowserDocked, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer24->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("  Funeral On  "));
    m_wbrowserFuneral = new wxStaticText(Panel2, ID_STATICTEXT5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    m_wbrowserFuneral->SetToolTip(_("Ejection time stamp."));
    StaticBoxSizer5->Add(m_wbrowserFuneral, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer24->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(BoxSizer24, 0, wxEXPAND, 5);
    BoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
    m_wbrowserGrid = new wxGrid(Panel2, ID_GRID1, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, _T("ID_GRID1"));
    m_wbrowserGrid->CreateGrid(0,1);
    m_wbrowserGrid->EnableEditing(false);
    m_wbrowserGrid->EnableGridLines(true);
    m_wbrowserGrid->SetColLabelValue(0, _("Cartridges"));
    m_wbrowserGrid->SetDefaultCellFont( m_wbrowserGrid->GetFont() );
    m_wbrowserGrid->SetDefaultCellTextColour( m_wbrowserGrid->GetForegroundColour() );
    BoxSizer25->Add(m_wbrowserGrid, 1, wxALIGN_LEFT, 5);
    StaticBoxSizer3->Add(BoxSizer25, 0, wxALL|wxEXPAND, 5);
    BoxSizer26 = new wxBoxSizer(wxHORIZONTAL);
    m_wbrowserText = new wxRichTextCtrl(Panel2, ID_RICHTEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL2"));
    wxRichTextAttr rchtxtAttr_2;
    rchtxtAttr_2.SetFlags(wxTEXT_ATTR_TEXT_COLOUR|wxTEXT_ATTR_BACKGROUND_COLOUR|wxTEXT_ATTR_FONT_FACE|wxTEXT_ATTR_FONT_SIZE|wxTEXT_ATTR_FONT_WEIGHT|wxTEXT_ATTR_FONT_ITALIC|wxTEXT_ATTR_FONT_UNDERLINE|wxTEXT_ATTR_FONT|wxTEXT_ATTR_ALIGNMENT|wxTEXT_ATTR_LEFT_INDENT);
    rchtxtAttr_2.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    m_wbrowserText->SetBasicStyle(rchtxtAttr_2);
    m_wbrowserText->SetToolTip(_("Event logger."));
    BoxSizer26->Add(m_wbrowserText, 1, wxEXPAND, 5);
    StaticBoxSizer3->Add(BoxSizer26, 1, wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer23->Add(StaticBoxSizer3, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    Panel2->SetSizer(BoxSizer23);
    BoxSizer23->Fit(Panel2);
    BoxSizer23->SetSizeHints(Panel2);
    SplitterWindow1->SplitVertically(Panel1, Panel2);
    SplitterWindow1->SetSashPosition(300);
    BoxSizer21->Add(SplitterWindow1, 1, wxALL|wxEXPAND, 5);
    BoxSizer20->Add(BoxSizer21, 1, wxALL|wxEXPAND, 5);
    m_wbrowserPanel->SetSizer(BoxSizer20);
    BoxSizer20->Fit(m_wbrowserPanel);
    BoxSizer20->SetSizeHints(m_wbrowserPanel);
    AuiNotebook1->AddPage(m_wloggerPanel, _("Cassette Logger"));
    AuiNotebook1->AddPage(m_wbrowserPanel, _("Cassettes Browser"));
    BoxSizer2->Add(AuiNotebook1, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_dockCassetteClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_wredockCassetteClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_undockCassetteClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_keepOnStageClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_unloadStageClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_addOperatorClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_deleteOperatorClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_wtreeExpandAllClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_wtreeCollapseAllClick);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&HorusFrame::OnCassettesSelectionChanged);
    m_wbrowserGrid->Connect(wxEVT_SIZE,(wxObjectEventFunction)&HorusFrame::OnBrowserGridResize,0,this);
    Connect(ID_SPLITTERWINDOW1,wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING,(wxObjectEventFunction)&HorusFrame::OnSplitterWindow1SashPosChanging);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HorusFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HorusFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&HorusFrame::OnClose);
    //*)

    // Add needed rows.
    m_wbrowserGrid->InsertRows(0, MAX_CARTRIDGE_SLOTS);

    // Show the splashscreen, usefull when the log is "huge"
    wxSplashScreen* splash = new wxSplashScreen(*hUtils::CreateBitmapFromPNGResource(wxT("SPLASH")), wxSPLASH_CENTRE_ON_SCREEN/*|wxSPLASH_TIMEOUT*/,
                                                0/*6000*/, NULL, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxSTAY_ON_TOP);
    wxYield();

    // Create the cassette object, which handles cartridges and stage
    m_cassette = new HorusCassette(m_wscrolledCartridges, m_wslotSizer);
    m_wscrolledCartridges->Fit();
    wxSize ws = m_wscrolledCartridges->GetSize();
    m_wscrolledCartridges->SetMinSize(wxSize(-1, ws.GetHeight()));
    m_wscrolledCartridges->SetMaxSize(wxSize(-1, ws.GetHeight()));

    // Define App icon and Title
    SetIcon(wxICON(MAINICON));
    SetTitle(wxGetApp().GetAppName() + wxT(" ")
             + wxString::FromAscii(AutoVersion::FULLVERSION_STRING)
             + wxString::FromAscii(AutoVersion::STATUS_SHORT));

    // UI update
    Fit();
    Layout();

    // Size is hardcoded
    wxSize s(1300, 1000);
    SetSize(s);
    SetMinSize(s);

    // Don't let the cartridges sending events now.
    m_cassette->SetSilent(true);

    // Don't log events into database yet.
    m_eventLoggerLockout = true;

    // Create database pool object
    m_databases = new HorusDatabasePool(this);

    // Initialize the database pool
    if (m_databases->Initialize(m_cassette))
    {
        // Reload previous cassette and operators list
        if (! m_databases->ReloadData(m_operators, this))
            Close();

        // Update the UI if a cartridge is on the stage.
        if (! m_cassette->IsStageEmpty())
        {
            HorusCartridge *slot = m_cassette->GetLoadedCartridge();

            m_wunloadStage->Enable(true);
            m_wcartridgeNum->SetLabel(wxString::Format(wxT("%zu"), slot->GetNumber()));
        }
    }

    // Update Keep On Stage UI checkbox
    m_wkeepOnStage->SetValue(m_databases->GetKeepOnStage());

    // Dock the cassette, if any
    _dockCassette(m_databases->GetCassetteDocked());

    // If a cassette is docked, update the docking timestamp in the UI
    if (m_databases->GetCassetteDocked())
    {
        time_t ts;

        if (m_databases->GetCassetteDockTimeStamp(ts))
            m_wdockedLabel->SetLabel(hUtils::GetTimeStampString(ts, false));
    }

    // Update the Keep On Stage checkbox
    if (! m_cassette->IsStageEmpty() && ! m_wkeepOnStage->IsEnabled())
        m_wkeepOnStage->Enable(true);

    // Accept events now
    m_eventLoggerLockout = false;
    m_cassette->SetSilent(false);

    // Update the operator list widget
    _updateOperatorChoice();

    // Get cassette's operator UUID
    wxString opUUID = m_databases->GetCassetteOperator();

    // Update Operator, if defined
    if (opUUID != wxEmptyString && opUUID != wxT("-1"))
    {
        // Looking for matching Operator name
        for (size_t i = 0; i < m_operators.GetCount(); i++)
        {
            if (m_operators.Item(i).UUID.Cmp(opUUID) == 0)
            {
                m_woperatorChoice->SetSelection(i);
                break;
            }
        }
    }

    // Init cassettes browser tab.
    _initBrowser();

    // Delete splashscreen
    delete splash;

    // Show the main window
    Show();
}

HorusFrame::~HorusFrame()
{
    //(*Destroy(HorusFrame)
    //*)
}

void HorusFrame::_updateOperatorChoice()
{
    m_woperatorChoice->Clear();

    for (size_t i = 0; i < m_operators.GetCount(); i++)
        m_woperatorChoice->Append(m_operators.Item(i).Name);

    if (m_operators.GetCount())
    {
        m_woperatorChoice->SetSelection(0);
        m_wdeleteOperator->Enable(true);
        m_woperatorChoice->Fit();
        m_woperatorChoice->GetParent()->Fit();
        m_woperatorChoice->GetParent()->Layout();
        Layout();
    }
    else
    {
        m_wdeleteOperator->Enable(false);
    }
}

inline void HorusFrame::_logEvent(wxRichTextCtrl *ctrl, time_t ts, const wxString &op, const wxString &message, bool frozen, bool saveToDatabase)
{
    wxDateTime dt(ts);
    wxString timestamp = dt.Format(wxT("%a %b %d %Y %H:%M:%S "));

    if (frozen)
        ctrl->Freeze();

    ctrl->SetInsertionPointEnd();

    ctrl->BeginFontSize(10);

    // Timestamp in bold
    ctrl->BeginBold();
    ctrl->WriteText(timestamp + wxT("[ "));

    // Operator
    ctrl->BeginTextColour(*wxBLUE);//wxColor(0, 0, 255));
    ctrl->WriteText(op != wxEmptyString ? op : wxT("<UNKNOWN>"));
    ctrl->EndTextColour();

    ctrl->WriteText(wxT(" ] :: "));
    ctrl->EndBold();

    // Then text
    ctrl->WriteText(message + wxT("\n"));

    // Move to the end of the text

    if (frozen)
    {
        ctrl->ScrollIntoView(ctrl->GetLastPosition(), /* WXK_PAGEDOWN */ WXK_END);
        ctrl->Thaw();
    }

    if (saveToDatabase && m_eventLoggerLockout == false)
    {
        if (! m_databases->LogCassetteEvent(ts, op != wxEmptyString ? op : wxT("-1"), message))
            wxMessageBox(wxT("Unable to log the cassette event into database."), wxT("Error"), wxOK|wxICON_ERROR);
    }
}


void HorusFrame::OnClose(wxCloseEvent& event)
{
    //_saveDB();

    delete m_databases;

    event.Skip();
}

void HorusFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void HorusFrame::OnAbout(wxCommandEvent& event)
{
    HorusAboutInformations infos;

    infos.Program.Name = wxGetApp().GetAppName();
    infos.Program.Version = wxString::FromAscii(AutoVersion::FULLVERSION_STRING) + wxT("-") + wxString::FromAscii(AutoVersion::STATUS);
    infos.Program.Pitch = wxT("A Cassette Logger");
    infos.Copyright.Year = wxT("2016-") + wxString::FromAscii(AutoVersion::YEAR);
    infos.Copyright.AuthorName = PROGRAM_AUTHOR_NAME;
    infos.Copyright.AuthorAddress = PROGRAM_AUTHOR_ADDRESS;
    infos.Copyright.Company = PROGRAM_COMPANY;
    infos.Copyright.URL = PROGRAM_COMPANY_URL;
    infos.Copyright.LicenseExcerpt = wxT("Released under the terms of the GPL v2");
    infos.Copyright.LicenseComplete = \
    wxT("\
                        GNU GENERAL PUBLIC LICENSE\n\
                           Version 2, June 1991\n\
    \n\
     Copyright (C) 1989, 1991 Free Software Foundation, Inc.,\n\
     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA\n\
     Everyone is permitted to copy and distribute verbatim copies\n\
     of this license document, but changing it is not allowed.\n\
    \n\
                                Preamble\n\
    \n\
      The licenses for most software are designed to take away your\n\
    freedom to share and change it.  By contrast, the GNU General Public\n\
    License is intended to guarantee your freedom to share and change free\n\
    software--to make sure the software is free for all its users.  This\n\
    General Public License applies to most of the Free Software\n\
    Foundation's software and to any other program whose authors commit to\n\
    using it.  (Some other Free Software Foundation software is covered by\n\
    the GNU Lesser General Public License instead.)  You can apply it to\n\
    your programs, too.\n\
    \n\
      When we speak of free software, we are referring to freedom, not\n\
    price.  Our General Public Licenses are designed to make sure that you\n\
    have the freedom to distribute copies of free software (and charge for\n\
    this service if you wish), that you receive source code or can get it\n\
    if you want it, that you can change the software or use pieces of it\n\
    in new free programs; and that you know you can do these things.\n\
    \n\
      To protect your rights, we need to make restrictions that forbid\n\
    anyone to deny you these rights or to ask you to surrender the rights.\n\
    These restrictions translate to certain responsibilities for you if you\n\
    distribute copies of the software, or if you modify it.\n\
    \n\
      For example, if you distribute copies of such a program, whether\n\
    gratis or for a fee, you must give the recipients all the rights that\n\
    you have.  You must make sure that they, too, receive or can get the\n\
    source code.  And you must show them these terms so they know their\n\
    rights.\n\
    \n\
      We protect your rights with two steps: (1) copyright the software, and\n\
    (2) offer you this license which gives you legal permission to copy,\n\
    distribute and/or modify the software.\n\
    \n\
      Also, for each author's protection and ours, we want to make certain\n\
    that everyone understands that there is no warranty for this free\n\
    software.  If the software is modified by someone else and passed on, we\n\
    want its recipients to know that what they have is not the original, so\n\
    that any problems introduced by others will not reflect on the original\n\
    authors' reputations.\n\
    \n\
      Finally, any free program is threatened constantly by software\n\
    patents.  We wish to avoid the danger that redistributors of a free\n\
    program will individually obtain patent licenses, in effect making the\n\
    program proprietary.  To prevent this, we have made it clear that any\n\
    patent must be licensed for everyone's free use or not licensed at all.\n\
    \n\
      The precise terms and conditions for copying, distribution and\n\
    modification follow.\n\
    \n\
                        GNU GENERAL PUBLIC LICENSE\n\
       TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION\n\
    \n\
      0. This License applies to any program or other work which contains\n\
    a notice placed by the copyright holder saying it may be distributed\n\
    under the terms of this General Public License.  The \"Program\", below,\n\
    refers to any such program or work, and a \"work based on the Program\"\n\
    means either the Program or any derivative work under copyright law:\n\
    that is to say, a work containing the Program or a portion of it,\n\
    either verbatim or with modifications and/or translated into another\n\
    language.  (Hereinafter, translation is included without limitation in\n\
    the term \"modification\".)  Each licensee is addressed as \"you\".\n\
    \n\
    Activities other than copying, distribution and modification are not\n\
    covered by this License; they are outside its scope.  The act of\n\
    running the Program is not restricted, and the output from the Program\n\
    is covered only if its contents constitute a work based on the\n\
    Program (independent of having been made by running the Program).\n\
    Whether that is true depends on what the Program does.\n\
    \n\
      1. You may copy and distribute verbatim copies of the Program's\n\
    source code as you receive it, in any medium, provided that you\n\
    conspicuously and appropriately publish on each copy an appropriate\n\
    copyright notice and disclaimer of warranty; keep intact all the\n\
    notices that refer to this License and to the absence of any warranty;\n\
    and give any other recipients of the Program a copy of this License\n\
    along with the Program.\n\
    \n\
    You may charge a fee for the physical act of transferring a copy, and\n\
    you may at your option offer warranty protection in exchange for a fee.\n\
    \n\
      2. You may modify your copy or copies of the Program or any portion\n\
    of it, thus forming a work based on the Program, and copy and\n\
    distribute such modifications or work under the terms of Section 1\n\
    above, provided that you also meet all of these conditions:\n\
    \n\
        a) You must cause the modified files to carry prominent notices\n\
        stating that you changed the files and the date of any change.\n\
    \n\
        b) You must cause any work that you distribute or publish, that in\n\
        whole or in part contains or is derived from the Program or any\n\
        part thereof, to be licensed as a whole at no charge to all third\n\
        parties under the terms of this License.\n\
    \n\
        c) If the modified program normally reads commands interactively\n\
        when run, you must cause it, when started running for such\n\
        interactive use in the most ordinary way, to print or display an\n\
        announcement including an appropriate copyright notice and a\n\
        notice that there is no warranty (or else, saying that you provide\n\
        a warranty) and that users may redistribute the program under\n\
        these conditions, and telling the user how to view a copy of this\n\
        License.  (Exception: if the Program itself is interactive but\n\
        does not normally print such an announcement, your work based on\n\
        the Program is not required to print an announcement.)\n\
    \n\
    These requirements apply to the modified work as a whole.  If\n\
    identifiable sections of that work are not derived from the Program,\n\
    and can be reasonably considered independent and separate works in\n\
    themselves, then this License, and its terms, do not apply to those\n\
    sections when you distribute them as separate works.  But when you\n\
    distribute the same sections as part of a whole which is a work based\n\
    on the Program, the distribution of the whole must be on the terms of\n\
    this License, whose permissions for other licensees extend to the\n\
    entire whole, and thus to each and every part regardless of who wrote it.\n\
    \n\
    Thus, it is not the intent of this section to claim rights or contest\n\
    your rights to work written entirely by you; rather, the intent is to\n\
    exercise the right to control the distribution of derivative or\n\
    collective works based on the Program.\n\
    \n\
    In addition, mere aggregation of another work not based on the Program\n\
    with the Program (or with a work based on the Program) on a volume of\n\
    a storage or distribution medium does not bring the other work under\n\
    the scope of this License.\n\
    \n\
      3. You may copy and distribute the Program (or a work based on it,\n\
    under Section 2) in object code or executable form under the terms of\n\
    Sections 1 and 2 above provided that you also do one of the following:\n\
    \n\
        a) Accompany it with the complete corresponding machine-readable\n\
        source code, which must be distributed under the terms of Sections\n\
        1 and 2 above on a medium customarily used for software interchange; or,\n\
    \n\
        b) Accompany it with a written offer, valid for at least three\n\
        years, to give any third party, for a charge no more than your\n\
        cost of physically performing source distribution, a complete\n\
        machine-readable copy of the corresponding source code, to be\n\
        distributed under the terms of Sections 1 and 2 above on a medium\n\
        customarily used for software interchange; or,\n\
    \n\
        c) Accompany it with the information you received as to the offer\n\
        to distribute corresponding source code.  (This alternative is\n\
        allowed only for noncommercial distribution and only if you\n\
        received the program in object code or executable form with such\n\
        an offer, in accord with Subsection b above.)\n\
    \n\
    The source code for a work means the preferred form of the work for\n\
    making modifications to it.  For an executable work, complete source\n\
    code means all the source code for all modules it contains, plus any\n\
    associated interface definition files, plus the scripts used to\n\
    control compilation and installation of the executable.  However, as a\n\
    special exception, the source code distributed need not include\n\
    anything that is normally distributed (in either source or binary\n\
    form) with the major components (compiler, kernel, and so on) of the\n\
    operating system on which the executable runs, unless that component\n\
    itself accompanies the executable.\n\
    \n\
    If distribution of executable or object code is made by offering\n\
    access to copy from a designated place, then offering equivalent\n\
    access to copy the source code from the same place counts as\n\
    distribution of the source code, even though third parties are not\n\
    compelled to copy the source along with the object code.\n\
    \n\
      4. You may not copy, modify, sublicense, or distribute the Program\n\
    except as expressly provided under this License.  Any attempt\n\
    otherwise to copy, modify, sublicense or distribute the Program is\n\
    void, and will automatically terminate your rights under this License.\n\
    However, parties who have received copies, or rights, from you under\n\
    this License will not have their licenses terminated so long as such\n\
    parties remain in full compliance.\n\
    \n\
      5. You are not required to accept this License, since you have not\n\
    signed it.  However, nothing else grants you permission to modify or\n\
    distribute the Program or its derivative works.  These actions are\n\
    prohibited by law if you do not accept this License.  Therefore, by\n\
    modifying or distributing the Program (or any work based on the\n\
    Program), you indicate your acceptance of this License to do so, and\n\
    all its terms and conditions for copying, distributing or modifying\n\
    the Program or works based on it.\n\
    \n\
      6. Each time you redistribute the Program (or any work based on the\n\
    Program), the recipient automatically receives a license from the\n\
    original licensor to copy, distribute or modify the Program subject to\n\
    these terms and conditions.  You may not impose any further\n\
    restrictions on the recipients' exercise of the rights granted herein.\n\
    You are not responsible for enforcing compliance by third parties to\n\
    this License.\n\
    \n\
      7. If, as a consequence of a court judgment or allegation of patent\n\
    infringement or for any other reason (not limited to patent issues),\n\
    conditions are imposed on you (whether by court order, agreement or\n\
    otherwise) that contradict the conditions of this License, they do not\n\
    excuse you from the conditions of this License.  If you cannot\n\
    distribute so as to satisfy simultaneously your obligations under this\n\
    License and any other pertinent obligations, then as a consequence you\n\
    may not distribute the Program at all.  For example, if a patent\n\
    license would not permit royalty-free redistribution of the Program by\n\
    all those who receive copies directly or indirectly through you, then\n\
    the only way you could satisfy both it and this License would be to\n\
    refrain entirely from distribution of the Program.\n\
    \n\
    If any portion of this section is held invalid or unenforceable under\n\
    any particular circumstance, the balance of the section is intended to\n\
    apply and the section as a whole is intended to apply in other\n\
    circumstances.\n\
    \n\
    It is not the purpose of this section to induce you to infringe any\n\
    patents or other property right claims or to contest validity of any\n\
    such claims; this section has the sole purpose of protecting the\n\
    integrity of the free software distribution system, which is\n\
    implemented by public license practices.  Many people have made\n\
    generous contributions to the wide range of software distributed\n\
    through that system in reliance on consistent application of that\n\
    system; it is up to the author/donor to decide if he or she is willing\n\
    to distribute software through any other system and a licensee cannot\n\
    impose that choice.\n\
    \n\
    This section is intended to make thoroughly clear what is believed to\n\
    be a consequence of the rest of this License.\n\
    \n\
      8. If the distribution and/or use of the Program is restricted in\n\
    certain countries either by patents or by copyrighted interfaces, the\n\
    original copyright holder who places the Program under this License\n\
    may add an explicit geographical distribution limitation excluding\n\
    those countries, so that distribution is permitted only in or among\n\
    countries not thus excluded.  In such case, this License incorporates\n\
    the limitation as if written in the body of this License.\n\
    \n\
      9. The Free Software Foundation may publish revised and/or new versions\n\
    of the General Public License from time to time.  Such new versions will\n\
    be similar in spirit to the present version, but may differ in detail to\n\
    address new problems or concerns.\n\
    \n\
    Each version is given a distinguishing version number.  If the Program\n\
    specifies a version number of this License which applies to it and \"any\n\
    later version\", you have the option of following the terms and conditions\n\
    either of that version or of any later version published by the Free\n\
    Software Foundation.  If the Program does not specify a version number of\n\
    this License, you may choose any version ever published by the Free Software\n\
    Foundation.\n\
    \n\
      10. If you wish to incorporate parts of the Program into other free\n\
    programs whose distribution conditions are different, write to the author\n\
    to ask for permission.  For software which is copyrighted by the Free\n\
    Software Foundation, write to the Free Software Foundation; we sometimes\n\
    make exceptions for this.  Our decision will be guided by the two goals\n\
    of preserving the free status of all derivatives of our free software and\n\
    of promoting the sharing and reuse of software generally.\n\
    \n\
                                NO WARRANTY\n\
    \n\
      11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY\n\
    FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN\n\
    OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES\n\
    PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED\n\
    OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF\n\
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS\n\
    TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE\n\
    PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,\n\
    REPAIR OR CORRECTION.\n\
    \n\
      12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\n\
    WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR\n\
    REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,\n\
    INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING\n\
    OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED\n\
    TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY\n\
    YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER\n\
    PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE\n\
    POSSIBILITY OF SUCH DAMAGES.\n\
    \n\
                         END OF TERMS AND CONDITIONS\
");

    wxString buildstr = wxbuildinfo(long_f) + wxT("\n");
#ifdef __GNUG__
    buildstr << wxT("GNU C++ Compiler: ") << __GNUC__ << wxT(".") << __GNUC_MINOR__ << wxT(".") << __GNUC_PATCHLEVEL__ << wxT("\n");
#endif

#ifdef __WIN64__
    buildstr << wxT("Build Platform: x64") << wxT(".\n");
#else
#ifdef __WIN32__
    buildstr << wxT("Build Platform: x86") << wxT(".\n");
#else
#error Are you kidding me ? ;)
#endif // __WIN32__
#endif // __WIN64__

    buildstr << wxT("Build Date: ") << wxString::FromAscii(__DATE__) << wxT(" at ") << wxString::FromAscii(__TIME__) << wxT("\n");
    buildstr << wxT("By: ") << wxString::FromAscii(USERNAME).Lower() << wxT("@") << wxString::FromAscii(HOSTNAME).Lower();// << wxT(" On ") << HOSTSYSTEM;

    if (wxWindow::IsDoubleBuffered())
        buildstr << wxT(".\n") << wxT("Features: ") << wxT("DOUBLE_BUFFER");

    infos.BuildInfos = buildstr;

    // Logos
    infos.Bitmaps.Program = *hUtils::CreateBitmapFromPNGResource(wxT("HORUSLOGO"));
    infos.Bitmaps.Company1 = *hUtils::CreateBitmapFromPNGResource(wxT("BIOEMLABLOGO"));
    infos.Bitmaps.Company2 = *hUtils::CreateBitmapFromPNGResource(wxT("CINALOGO"));
    infos.Bitmaps.Company3 = *hUtils::CreateBitmapFromPNGResource(wxT("BIOZLOGO"));

    HorusAboutDialog dialog(this);

    dialog.SetInformations(infos);
    dialog.ShowModal();
}

void HorusFrame::_dockCassette(bool dock, bool redock)
{
    switch (dock)
    {
        case true:
            if (redock)
                m_cassette->RedockCassette();
            else
                m_cassette->DockCassette();

            m_wdockCassette->Enable(false);
            m_wredockCassette->Enable(false);
            m_wundockCassette->Enable(true);
            m_wscrolledCartridges->Enable(true);
            m_wscrolledStage->Enable(true);
            break;

        case false:
            if (! m_wkeepOnStage->GetValue())
                m_cassette->UnloadStage();

            m_cassette->UndockCassette();

            m_wdockCassette->Enable(true);
            m_wredockCassette->Enable(true);
            m_wundockCassette->Enable(false);
            m_wscrolledCartridges->Enable(false);
            m_wscrolledStage->Enable(false);
            break;
    }
}

void HorusFrame::Onm_dockCassetteClick(wxCommandEvent& event)
{
    if (wxMessageBox(wxT("Do you really want to dock the cassette ?"), wxT("Question"), wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION) == wxYES)
        _dockCassette(true);

    event.Skip();
}

void HorusFrame::Onm_wredockCassetteClick(wxCommandEvent& event)
{
    if (wxMessageBox(wxT("Do you really want to redock the cassette ?"), wxT("Question"), wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION) == wxYES)
        _dockCassette(true, true);
}

void HorusFrame::Onm_undockCassetteClick(wxCommandEvent& event)
{
    if (wxMessageBox(wxT("Do you really want to undock the cassette ?"), wxT("Question"), wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION) == wxYES)
        _dockCassette(false);

    event.Skip();
}

void HorusFrame::OnCassetteEvent(wxCommandEvent &event)
{
    HorusEventCassetteData *data = (HorusEventCassetteData *)event.GetClientData();

    if (data)
    {
        switch (event.GetInt())
        {
            case HORUS_EVENT_CARTRIDGE_LOAD:
                //wxLogStatus(wxT("  ** Cartridge LOADED: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_wcartridgeNum->SetLabel(wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));

                _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cartridge #")
                          + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()) + wxT(" loaded."), true);

                m_wunloadStage->Enable(true);
                m_wkeepOnStage->Enable(true);
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CARTRIDGE_UNLOAD:
                //wxLogStatus(wxT("  ** Cartridge UNLOADED: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_wcartridgeNum->SetLabel(wxT("<NONE>"));

                _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cartridge #")
                          + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()) + wxT(" unloaded."), true);

                if (m_wkeepOnStage->GetValue())
                {
                    m_wkeepOnStage->SetValue(false);
                    m_databases->SetKeepOnStage(false);
                }

                m_wunloadStage->Enable(false);
                m_wkeepOnStage->Enable(false);
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CARTRIDGE_UPDATE:
                // Update Database
                //wxLogStatus(wxT("  ** Cartridge UPDATE: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CASSETTE_DOCKED:
                {
                    //wxLogStatus(wxT("  ** Cassette DOCKED."));

                    if (! m_cassette->IsStageEmpty() && ! m_wkeepOnStage->IsEnabled())
                        m_wkeepOnStage->Enable(true);

                    _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()),
                              wxT("Cassette Docked."), true);

                    m_wtextLogger->Clear();

                    m_databases->SetCassetteDocked(true, m_operators.GetCount()
                                                           ? m_operators.Item(static_cast<size_t>(m_woperatorChoice->GetSelection())).UUID
                                                            : wxT("-1"));

                    time_t ts;

                    if (m_databases->GetCassetteDockTimeStamp(ts))
                        m_wdockedLabel->SetLabel(hUtils::GetTimeStampString(ts, false));

                    // Update all cartridges informations into database
                    for (size_t i = 0; i < MAX_CARTRIDGE_SLOTS; i++)
                        m_databases->UpdateCartridge(m_cassette->GetCartridge(i));

                    _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()),
                              wxT("Cassette Docked."), true, false);
                }
                break;

            case HORUS_EVENT_CASSETTE_REDOCKED:
                {
                    //wxLogStatus(wxT("  ** Cassette REDOCKED."));

                    if (! m_cassette->IsStageEmpty() && ! m_wkeepOnStage->IsEnabled())
                        m_wkeepOnStage->Enable(true);

                    _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()),
                              wxT("Cassette Redocked."), true);

                    m_databases->SetCassetteRedocked();

                    time_t ts;
                    if (m_databases->GetCassetteDockTimeStamp(ts))
                        m_wdockedLabel->SetLabel(hUtils::GetTimeStampString(ts, false));
                }
                break;

            case HORUS_EVENT_CASSETTE_UNDOCKED:
                //wxLogStatus(wxT("  ** Cassette UNDOCKED."));

                _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()),
                          wxT("Cassette Undocked."), true);
                m_databases->SetCassetteDocked(false, wxEmptyString);
                m_wdockedLabel->SetLabel(wxT("< ----/--/-- --:--:-- >"));
                break;
        }

        delete data;
    }

    event.Skip();
}

void HorusFrame::OnDatabasePoolEvent(wxCommandEvent &event)
{
    HorusEventDatabaseData *data = (HorusEventDatabaseData *)event.GetClientData();

    switch (event.GetInt())
    {
        case HORUS_EVENT_DATABASEPOOL_BACKUP:
            if (data)
                _extractCassetteFromDatabase(data->BackupFile);
            break;
    }

    if (data)
        delete data;

    event.Skip();
}

void HorusFrame::HorusEventRestore(time_t ts, const wxString &op, const wxString &msg)
{
    _logEvent(m_wtextLogger, ts, op, msg, false, false);
}

void HorusFrame::Onm_unloadStageClick(wxCommandEvent& event)
{
    if (wxMessageBox(wxT("Do you really want to unload cartridge #")
                     + wxString::Format(wxT("%zu"), m_cassette->GetLoadedCartridge()->GetNumber()) + wxT(" ?."),
                     wxT("Question"), wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION) == wxYES)
        m_cassette->UnloadStage();

    event.Skip();
}

void HorusFrame::Onm_addOperatorClick(wxCommandEvent& event)
{
    wxTextEntryDialog dial(this, wxT("Please enter a name for the new operator"), wxT("New Operator"));
    bool valid = false;

    dial.SetMaxLength(32); ///< Operator max name length

    while (! valid)
    {
        // Adding canceled
        if (dial.ShowModal() != wxID_OK)
            break;

        wxString name = dial.GetValue();
        name.Trim();
        name.Trim(false);

        if ((name == wxEmptyString) || (name.Len() == 0))
        {
            wxMessageBox(wxT("You have entered an empty or an incorrect operator name."), wxT("Error"), wxOK|wxICON_ERROR);
            continue;
        }

        valid = true;

        // Check if user name already exists
        for (size_t i = 0; i < m_operators.GetCount(); i++)
        {
            if (m_operators.Item(i).Name.CmpNoCase(name) == 0)
            {
                wxMessageBox(wxT("The operator '") + name + wxT("' already exists.\nPlease choose a different one."),
                             wxT("Error"), wxOK|wxICON_ERROR);
                valid = false;
                break;
            }
        }

        // Not a valid operator name, or creation has been canceled
        if (! valid)
            return;

        // New operator
        wxString uuid = hUtils::CreateGUID();

        // First check if everything is fine with the operators database
        if (! m_databases->AddOperator(name, uuid))
            wxMessageBox(wxT("Unable to add operator ") + name, wxT("Error"), wxOK|wxICON_ERROR);
        else
        {
            wxMessageBox(name + wxT(" is now a new operator."), wxT("Information"), wxOK|wxICON_INFORMATION);

            m_operators.Add(new Operator(name, uuid));
            m_operators.Sort(&hUtils::CompareOperators);

            _updateOperatorChoice();
        }

    }

    event.Skip();
}

void HorusFrame::Onm_deleteOperatorClick(wxCommandEvent& event)
{
    size_t selected = static_cast<size_t>(m_woperatorChoice->GetSelection());//static_cast<size_t>(event.GetInt());

    if (wxMessageBox(wxT("Do you really want to delete operator ")
                     + m_operators.Item(selected).Name + wxT(" ?."),
                     wxT("Delete Operator"), wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION) == wxYES)
    {
        if (!m_databases->DeleteOperator(m_operators.Item(selected).UUID))
            wxMessageBox(wxT("Unable to delete operator ") + m_operators.Item(selected).Name, wxT("Error"), wxOK|wxICON_ERROR);
        else
        {
            m_operators.RemoveAt(selected);
            _updateOperatorChoice();
        }

    }

    event.Skip();
}

void HorusFrame::Onm_keepOnStageClick(wxCommandEvent& event)
{
    m_databases->SetKeepOnStage(m_wkeepOnStage->GetValue());
}

wxTreeItemId HorusFrame::_getItemID(wxTreeItemId parent, const wxString &name)
{
    wxTreeItemIdValue   cookie;
    wxTreeItemId        id = m_wtreeCassettes->GetFirstChild(parent, cookie);
    wxTreeItemId        retID;

    do
    {
        if (id.IsOk())
        {
            if (m_wtreeCassettes->GetItemText(id).Cmp(name) == 0)
                return id;
        }
    } while ((id = m_wtreeCassettes->GetNextChild(parent, cookie)) && id.IsOk());

    return retID;
}

wxString const HorusFrame::_getOperatorFromUUID(const wxString &uuid)
{
    for (size_t i = 0; i < m_operators.GetCount(); i++)
    {
        if (m_operators.Item(i).UUID.Cmp(uuid) == 0)
        {
            return m_woperatorChoice->GetString(i);
        }
    }

    return wxT("<UNKNOWN>");
}

void HorusFrame::_addCassetteToTree(time_t ts, const wxString &uuid, const wxString &dbName)
{
    //   --ROOT
    //       |
    //       +-- 2017
    //             |
    //             +-- 09
    //                  |
    //                  +-- 30
    //                       |
    //                       +-- HH:MM:SS Operator
    //                       |
    //                       +-- HH:MM:SS Operator
    //                       |
    //                       +--
    //                       |
    //                       ...

    wxDateTime timestamp(ts);
    // Get Root
    wxTreeItemId rootID = m_wtreeCassettes->GetRootItem();
    // Get Year or create entry
    wxString yearStr = wxString::Format(wxT("%d"), timestamp.GetYear());
    wxTreeItemId yearID = _getItemID(rootID, yearStr);

    if (! yearID.IsOk())
    {
        yearID = m_wtreeCassettes->AppendItem(rootID, yearStr);
    }

    // Get Month or create entry
    wxString monthStr = wxString::Format(wxT("%02d"), timestamp.GetMonth() + 1);
    wxTreeItemId monthID = _getItemID(yearID, monthStr);

    if (! monthID.IsOk())
    {
        monthID = m_wtreeCassettes->AppendItem(yearID, monthStr);
    }

    // Get Day or create entry
    wxString dayStr = wxString::Format(wxT("%02d"), timestamp.GetDay());
    wxTreeItemId dayID = _getItemID(monthID, dayStr);

    if (! dayID.IsOk())
    {
        dayID = m_wtreeCassettes->AppendItem(monthID, dayStr);
    }

    // Add new entry based on hh:mm:ss uuid
    // Get op name from UUID (<UNKNOWN> if not found)
    wxString op = _getOperatorFromUUID(uuid);
    wxString entryStr = wxString::Format(wxT("%02d:%02d:%02d %s"),
                                         timestamp.GetHour(), timestamp.GetMinute(), timestamp.GetSecond(), op);
    wxTreeItemId entryID = m_wtreeCassettes->AppendItem(dayID, entryStr);

    if (entryID.IsOk())
    {
        hTreeItemData *data = new hTreeItemData(op, dbName);

        m_wtreeCassettes->SetItemData(entryID, data);
    }
}

bool HorusFrame::_extractCassetteFromDatabase(const wxString &dbName)
{
    /*
     extract database infos:
        - docked timestamp

        if clicked:
            - funeral timestamp
            - who docked
            - cartridges contents
            - list of events
    */

    // First extract timestamp;
    bool ok = true;
    int step = 0;
    time_t ts = 0;
    wxString op = wxEmptyString;
    wxSQLite3Database db;

    try
    {
        db.Open(dbName);

        step = 1;

        wxString            selcmd = wxString(wxT("SELECT i.dockTS, i.operatorUUID FROM informations i;"));
        wxSQLite3Statement  stmt = db.PrepareStatement(selcmd);
        wxSQLite3ResultSet  q = stmt.ExecuteQuery();

        if (q.NextRow())
        {
            ts = static_cast<time_t>(q.GetInt(0));
            op = q.GetString(1);
        }
    }
    catch (wxSQLite3Exception e)
    {
        wxString msg;

        if (step == 0)
            msg = wxString(wxT("Error on opening the Cassette database ") + dbName + wxT("\n"));

        if (step == 1)
            msg = wxString(wxT("Error on retrieving docked timestamp the Cassette database ") + dbName + wxT("\n"));

        msg << e.GetMessage();

        wxMessageBox(msg, wxT("Database Error"), wxOK|wxICON_ERROR);

        ok = false;
    }


    if (ok && ts != 0)
    {
        wxDateTime  dt(ts);

        _addCassetteToTree(ts, op, dbName);
    }

    db.Close();

    return ok;
}

// Cassettes Browser
void HorusFrame::_initBrowser()
{
    m_wtreeCassettes->DeleteAllItems();
    m_wtreeCassettes->AddRoot(wxT("Cassettes"));

    // Tweak wxGrid
    m_wbrowserGrid->DisableDragCell();
    m_wbrowserGrid->DisableDragColSize();
    m_wbrowserGrid->DisableDragColMove();
    m_wbrowserGrid->DisableDragGridSize();
    m_wbrowserGrid->DisableDragRowSize();

    // Load databases content
    wxString    directory = m_databases->GetBackupPath();
    wxDir       dir(directory);

    if (dir.Exists(directory) && dir.HasFiles())
    {
        wxArrayString backupFiles;

        if (wxDir::GetAllFiles(directory, &backupFiles, wxT("cassette_*.db3"), wxDIR_FILES))
        {
            for (size_t i = 0; i < backupFiles.GetCount(); i++)
            {
                _extractCassetteFromDatabase(backupFiles.Item(i));
            }

        }
    }

    m_wtreeCassettes->Expand(m_wtreeCassettes->GetRootItem());
}

void HorusFrame::_displayCassetteInfos(const wxString &opName, const wxString &dbName)
{
    /*
        if clicked:
        - docking timestamp
        - funeral timestamp
        - who docked
        - cartridges contents
        - list of events
    */

    if (dbName == wxEmptyString)
    {
        m_wbrowserOperator->SetLabel(wxEmptyString);
        m_wbrowserDocked->SetLabel(wxEmptyString);
        m_wbrowserFuneral->SetLabel(wxEmptyString);
        m_wbrowserGrid->ClearGrid();
        m_wbrowserText->Clear();
    }
    else
    {
        int                 step = 0;
        wxSQLite3Database   db;

        wxString op = opName;
        op.Replace(wxT("&"), wxT("&&"), true);
        m_wbrowserOperator->SetLabel(op);


        try
        {
            db.Open(dbName);

            step = 1;

            wxString            selcmd = wxString(wxT("SELECT i.dockTS, i.funeral FROM informations i;"));
            wxSQLite3Statement  stmt = db.PrepareStatement(selcmd);
            wxSQLite3ResultSet  q = stmt.ExecuteQuery();

            if (q.NextRow())
            {
                m_wbrowserDocked->SetLabel(hUtils::GetTimeStampString(static_cast<time_t>(q.GetInt(0)), false));
                m_wbrowserFuneral->SetLabel(hUtils::GetTimeStampString(static_cast<time_t>(q.GetInt(1)), false));
            }

            step = 2;

            m_wbrowserGrid->BeginBatch();
            for (size_t j = 0; j < MAX_CARTRIDGE_SLOTS; j++)
            {
                //cartridges SET text=?, keep=?, empty=?, loaded=? WHERE cid=?;
                selcmd = wxString(wxT("SELECT c.text FROM cartridges c WHERE cid=?;"));
                stmt = db.PrepareStatement(selcmd);
                stmt.Bind(1, static_cast<int>(j + 1));
                q = stmt.ExecuteQuery();

                if (q.NextRow())
                {
                    m_wbrowserGrid->SetCellValue(j, 0, q.GetString(0));
                }
            }
            m_wbrowserGrid->EndBatch();

            step = 3;

            m_wbrowserText->Clear();
            size_t  evtCnt = static_cast<size_t>(db.ExecuteScalar("SELECT COUNT(*) FROM events;"));

            if (evtCnt > 0)
            {
                selcmd = wxString(wxT("SELECT e.idx, e.timestamp, e.operator, e.text FROM events e ORDER BY e.idx;"));
                stmt = db.PrepareStatement(selcmd);
                q = stmt.ExecuteQuery();

                m_wbrowserText->Freeze();

                while (q.NextRow())
                {
                    time_t   ts     = static_cast<time_t>(q.GetInt(1));
                    wxString op     = q.GetString(2);
                    wxString msg    = q.GetString(3);

                    _logEvent(m_wbrowserText, ts, op, msg, false, false);
                }

                m_wbrowserText->ScrollIntoView(m_wbrowserText->GetLastPosition(), /* WXK_PAGEDOWN */ WXK_END);
                m_wbrowserText->Thaw();
            }

        }
        catch (wxSQLite3Exception e)
        {
            wxString msg;

            if (step == 0)
                msg = wxString(wxT("Error on opening the Cassette database ") + dbName + wxT("\n"));

            if (step == 1)
                msg = wxString(wxT("Error on retrieving timestamp\n"));

            if (step == 2)
                msg = wxString(wxT("Error on retrieving cartriges informations\n"));

            msg << e.GetMessage();

            wxMessageBox(msg, wxT("Database Error"), wxOK|wxICON_ERROR);
        }

        db.Close();
    }
}

void HorusFrame::OnCassettesSelectionChanged(wxTreeEvent& event)
{
    wxTreeItemId id = event.GetItem();
    wxTreeCtrl *tree = wxDynamicCast(event.GetEventObject(), wxTreeCtrl);
    hTreeItemData *data = (hTreeItemData *)tree->GetItemData(id);
    wxString dbName = wxEmptyString;
    wxString opName = wxEmptyString;

    if (data)
    {
        opName = data->GetOperatorName();
        dbName = data->GetDatabaseFilename();
    }

    wxBusyCursor busy;
    _displayCassetteInfos(opName, dbName);

    event.Skip();
}

void HorusFrame::OnBrowserGridResize(wxSizeEvent& event)
{
    wxSize sz = m_wbrowserGrid->GetClientSize();
    m_wbrowserGrid->SetColSize(0, sz.GetWidth() - m_wbrowserGrid->GetRowLabelSize());

    event.Skip();
}

void HorusFrame::Onm_wtreeExpandAllClick(wxCommandEvent& event)
{
    m_wtreeCassettes->ExpandAll();

    event.Skip();
}

void HorusFrame::Onm_wtreeCollapseAllClick(wxCommandEvent& event)
{
    m_wtreeCassettes->CollapseAll();

    event.Skip();
}

void HorusFrame::OnSplitterWindow1SashPosChanging(wxSplitterEvent& event)
{
    // Limit Sash position
    if (event.GetSashPosition() > MAX_SASH_POSITION)
        event.SetSashPosition(MAX_SASH_POSITION);

    event.Skip();
}

} // namespace Horus


