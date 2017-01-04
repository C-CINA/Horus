/***************************************************************
 * Name:      HorusMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Daniel Caujolle-Bert (daniel.caujolle-bert@unibas.ch)
 * Created:   2016-12-16
 * Copyright: Daniel Caujolle-Bert (https://c-cina.unibas.ch/bioem/)
 * License:
 **************************************************************/

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

BEGIN_EVENT_TABLE(HorusFrame,wxFrame)
    //(*EventTable(HorusFrame)
    //*)
    EVT_COMMAND(wxID_ANY, Horus::wxEVT_HORUS_CASSETTE, HorusFrame::OnCassetteEvent)
    EVT_COMMAND(wxID_ANY, Horus::wxEVT_HORUS_DATABASEPOOL, HorusFrame::OnDatabasePoolEvent)
END_EVENT_TABLE()

HorusFrame::HorusFrame(wxWindow* parent,wxWindowID id) : m_eventLockout(false)
{
#ifdef DEBUG
    wxLogWindow *logger = new wxLogWindow(this, _("Logging Window"));
    wxLog::SetActiveTarget(logger);
    wxLogStatus(wxT("Horus Started"));
#else
    wxLogNull noLog;
#endif

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
    BoxSizer13->Add(m_wdockCassette, 1, wxLEFT|wxRIGHT, 5);
    m_wredockCassette = new wxButton(m_wloggerPanel, ID_BUTTON3, _("Redock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer13->Add(m_wredockCassette, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wundockCassette = new wxButton(m_wloggerPanel, ID_BUTTON6, _("Undock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer13->Add(m_wundockCassette, 1, wxLEFT|wxRIGHT, 5);
    BoxSizer8->Add(BoxSizer13, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, m_wloggerPanel, _("  Docked On  "));
    StaticBoxSizer1->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wdockedLabel = new wxStaticText(m_wloggerPanel, ID_STATICTEXT3, _("< ----/--/-- --:--:-- >"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT3"));
    StaticBoxSizer1->Add(m_wdockedLabel, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer1->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(StaticBoxSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
    BoxSizer7->Add(m_wcartridgeNum, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wstageSizer->Add(BoxSizer7, 0, wxALL|wxEXPAND, 5);
    BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    m_wscrolledStage = new wxScrolledWindow(m_wloggerPanel, ID_SCROLLEDWINDOW2, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW2"));
    BoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer19 = new wxBoxSizer(wxVERTICAL);
    m_wkeepOnStage = new wxCheckBox(m_wscrolledStage, ID_CHECKBOX1, _("Keep On Stage"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    m_wkeepOnStage->SetValue(false);
    m_wkeepOnStage->Disable();
    BoxSizer19->Add(m_wkeepOnStage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wunloadStage = new wxButton(m_wscrolledStage, ID_BUTTON2, _("Unload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    m_wunloadStage->Disable();
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
    BoxSizer11->Add(m_woperatorChoice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12 = new wxBoxSizer(wxVERTICAL);
    m_waddOperator = new wxButton(m_wloggerPanel, ID_BUTTON4, _("+"), wxDefaultPosition, wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    m_waddOperator->SetToolTip(_("Add an Operator"));
    BoxSizer12->Add(m_waddOperator, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wdeleteOperator = new wxButton(m_wloggerPanel, ID_BUTTON5, _("-"), wxDefaultPosition, wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    m_wdeleteOperator->Disable();
    m_wdeleteOperator->SetToolTip(_("Delete Selected Operator"));
    BoxSizer12->Add(m_wdeleteOperator, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer11->Add(BoxSizer12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer10->Add(BoxSizer11, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer2->Add(BoxSizer10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(StaticBoxSizer2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer4->Add(BoxSizer5, 0, wxTOP|wxRIGHT|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer4, 1, wxEXPAND, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    m_wtextLogger = new wxRichTextCtrl(m_wloggerPanel, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
    wxRichTextAttr rchtxtAttr_1;
    rchtxtAttr_1.SetFlags(wxTEXT_ATTR_TEXT_COLOUR|wxTEXT_ATTR_BACKGROUND_COLOUR|wxTEXT_ATTR_FONT_FACE|wxTEXT_ATTR_FONT_SIZE|wxTEXT_ATTR_FONT_WEIGHT|wxTEXT_ATTR_FONT_ITALIC|wxTEXT_ATTR_FONT_UNDERLINE|wxTEXT_ATTR_FONT|wxTEXT_ATTR_ALIGNMENT|wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT|wxTEXT_ATTR_TABS|wxTEXT_ATTR_PARA_SPACING_AFTER|wxTEXT_ATTR_PARA_SPACING_BEFORE|wxTEXT_ATTR_LINE_SPACING|wxTEXT_ATTR_CHARACTER_STYLE_NAME|wxTEXT_ATTR_PARAGRAPH_STYLE_NAME|wxTEXT_ATTR_LIST_STYLE_NAME|wxTEXT_ATTR_BULLET_STYLE|wxTEXT_ATTR_BULLET_NUMBER|wxTEXT_ATTR_BULLET_TEXT|wxTEXT_ATTR_BULLET_NAME|wxTEXT_ATTR_URL|wxTEXT_ATTR_PAGE_BREAK|wxTEXT_ATTR_EFFECTS|wxTEXT_ATTR_OUTLINE_LEVEL);
    rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    m_wtextLogger->SetBasicStyle(rchtxtAttr_1);
    BoxSizer9->Add(m_wtextLogger, 1, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer9, 1, wxEXPAND, 5);
    m_wloggerPanel->SetSizer(BoxSizer3);
    BoxSizer3->Fit(m_wloggerPanel);
    BoxSizer3->SetSizeHints(m_wloggerPanel);
    m_wbrowserPanel = new wxPanel(AuiNotebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer20 = new wxBoxSizer(wxVERTICAL);
    BoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
    SplitterWindow1 = new wxSplitterWindow(m_wbrowserPanel, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(250,250));
    SplitterWindow1->SetMinimumPaneSize(250);
    SplitterWindow1->SetSashGravity(0);
    Panel1 = new wxPanel(SplitterWindow1, ID_PANEL3, wxPoint(133,10), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizer22 = new wxBoxSizer(wxVERTICAL);
    m_wtreeCassettes = new wxTreeCtrl(Panel1, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    BoxSizer22->Add(m_wtreeCassettes, 1, wxALL|wxEXPAND, 10);
    Panel1->SetSizer(BoxSizer22);
    BoxSizer22->Fit(Panel1);
    BoxSizer22->SetSizeHints(Panel1);
    Panel2 = new wxPanel(SplitterWindow1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    BoxSizer23 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, Panel2, _("  Cassette  "));
    BoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("  Operator  "));
    m_wbrowserOperator = new wxStaticText(Panel2, ID_STATICTEXT6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticBoxSizer6->Add(m_wbrowserOperator, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer24->Add(StaticBoxSizer6, 1, wxALL, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("  Docked On  "));
    m_wbrowserDocked = new wxStaticText(Panel2, ID_STATICTEXT4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticBoxSizer4->Add(m_wbrowserDocked, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer24->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("  Funeral On  "));
    m_wbrowserFuneral = new wxStaticText(Panel2, ID_STATICTEXT5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticBoxSizer5->Add(m_wbrowserFuneral, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer24->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(BoxSizer24, 0, wxALL|wxEXPAND, 5);
    BoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
    m_wbrowserGrid = new wxGrid(Panel2, ID_GRID1, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, _T("ID_GRID1"));
    m_wbrowserGrid->CreateGrid(6,1);
    m_wbrowserGrid->EnableEditing(false);
    m_wbrowserGrid->EnableGridLines(true);
    m_wbrowserGrid->SetColLabelValue(0, _("Cartridges"));
    m_wbrowserGrid->SetDefaultCellFont( m_wbrowserGrid->GetFont() );
    m_wbrowserGrid->SetDefaultCellTextColour( m_wbrowserGrid->GetForegroundColour() );
    BoxSizer25->Add(m_wbrowserGrid, 1, wxALL, 5);
    StaticBoxSizer3->Add(BoxSizer25, 0, wxALL|wxEXPAND, 5);
    BoxSizer26 = new wxBoxSizer(wxHORIZONTAL);
    m_wbrowserText = new wxRichTextCtrl(Panel2, ID_RICHTEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL2"));
    wxRichTextAttr rchtxtAttr_2;
    rchtxtAttr_2.SetFlags(wxTEXT_ATTR_TEXT_COLOUR|wxTEXT_ATTR_BACKGROUND_COLOUR|wxTEXT_ATTR_FONT_FACE|wxTEXT_ATTR_FONT_SIZE|wxTEXT_ATTR_FONT_WEIGHT|wxTEXT_ATTR_FONT_ITALIC|wxTEXT_ATTR_FONT_UNDERLINE|wxTEXT_ATTR_FONT|wxTEXT_ATTR_ALIGNMENT|wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT|wxTEXT_ATTR_TABS|wxTEXT_ATTR_PARA_SPACING_AFTER|wxTEXT_ATTR_PARA_SPACING_BEFORE|wxTEXT_ATTR_LINE_SPACING|wxTEXT_ATTR_CHARACTER_STYLE_NAME|wxTEXT_ATTR_PARAGRAPH_STYLE_NAME|wxTEXT_ATTR_LIST_STYLE_NAME|wxTEXT_ATTR_BULLET_STYLE|wxTEXT_ATTR_BULLET_NUMBER|wxTEXT_ATTR_BULLET_TEXT|wxTEXT_ATTR_BULLET_NAME|wxTEXT_ATTR_URL|wxTEXT_ATTR_PAGE_BREAK|wxTEXT_ATTR_EFFECTS|wxTEXT_ATTR_OUTLINE_LEVEL);
    rchtxtAttr_2.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    m_wbrowserText->SetBasicStyle(rchtxtAttr_2);
    BoxSizer26->Add(m_wbrowserText, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer3->Add(BoxSizer26, 1, wxALL|wxEXPAND, 5);
    BoxSizer23->Add(StaticBoxSizer3, 1, wxBOTTOM|wxEXPAND, 10);
    Panel2->SetSizer(BoxSizer23);
    BoxSizer23->Fit(Panel2);
    BoxSizer23->SetSizeHints(Panel2);
    SplitterWindow1->SplitVertically(Panel1, Panel2);
    SplitterWindow1->SetSashPosition(250);
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
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&HorusFrame::Onm_operatorChoiceSelect);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_addOperatorClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_deleteOperatorClick);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&HorusFrame::OnCassettesSelectionChanged);
    m_wbrowserGrid->Connect(wxEVT_SIZE,(wxObjectEventFunction)&HorusFrame::OnBrowserGridResize,0,this);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HorusFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HorusFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&HorusFrame::OnClose);
    //*)

    //StaticBoxSizer2->GetContainingWindow()->Connect(wxEVT_CONTEXT_MENU, (wxObjectEventFunction)&HorusFrame::OnContext, 0, this);

#if 0
    for (size_t i = 0; i < 6; i++)
    {
        HorusSlot *slot = new HorusSlot(Panel1, i + 1);
        m_slotSizer->Add(slot, 0, wxEXPAND, 5);

    }
#else

    m_cassette = new HorusCassette(m_wscrolledCartridges, m_wslotSizer);
    m_wscrolledCartridges->Fit();
    wxSize ws = m_wscrolledCartridges->GetSize();
    m_wscrolledCartridges->SetMinSize(wxSize(-1, ws.GetHeight()));
    m_wscrolledCartridges->SetMaxSize(wxSize(-1, ws.GetHeight()));

//    m_cartridgesPanel->Layout();

#endif


    SetIcon(wxICON(MAINICON));
    SetTitle(wxGetApp().GetAppName() + wxT(" ")
             + wxString::FromAscii(AutoVersion::FULLVERSION_STRING)
             + wxString::FromAscii(AutoVersion::STATUS_SHORT));

//    Custom1->SetBitmapPressed(*hUtils::CreateBitmapFromPNGResource(wxT("TOGGLE_IN")));
//    Custom1->SetBitmapPressed(*hUtils::CreateBitmapFromPNGResource(wxT("TOGGLE_OUT_DISABLED")));

    //Custom1->SetMaxSize(wxSize(50, 25));

    Fit();
    Layout();

    wxSize s(1300, 900);
    SetSize(s);
    SetMinSize(s);

#warning FIX THIS
//    m_scrolledCartridges->Enable(! m_scrolledCartridges->Enable());
//    m_scrolledCartridges->Enable(! m_scrolledCartridges->Enable());
//    m_scrolledCartridges->Enable(! m_scrolledCartridges->Enable());
//    m_scrolledCartridges->Enable(! m_scrolledCartridges->Enable());

    //m_eventLock = true;

    m_cassette->SetSilent(true);
    m_eventLockout = true;

    m_databases = new HorusDatabasePool(this);

    if (m_databases->Initialize(m_cassette))
    {
        if (! m_databases->ReloadData(m_operators))
            Close();

        if (! m_cassette->IsStageEmpty())
        {
            HorusCartridge *slot = m_cassette->GetLoadedCartridge();

            m_wunloadStage->Enable(true);
            m_wcartridgeNum->SetLabel(wxString::Format(wxT("%zu"), slot->GetNumber()));
        }
    }

    m_wkeepOnStage->SetValue(m_databases->GetKeepOnStage());

    _dockCassette(m_databases->GetCassetteDocked());

    if (m_databases->GetCassetteDocked())
    {
        time_t ts;
        if (m_databases->GetCassetteDockTimeStamp(ts))
        {
            m_wdockedLabel->SetLabel(hUtils::GetTimeStampString(ts, false));
        }
    }

    if (! m_cassette->IsStageEmpty() && ! m_wkeepOnStage->IsEnabled())
        m_wkeepOnStage->Enable(true);

    m_eventLockout = false;
    m_cassette->SetSilent(false);

    //m_eventLock = false;


//    wxLogStatus(wxT("GetUserDataDir: ") + wxStandardPaths::Get().GetUserDataDir());
//
//    m_databases->AddOperator(wxT("Daniel"), wxT("17069590be3c40148674aadd0b88d591"));
//    m_databases->UpdateOperator(wxT("Daniel"), wxT("17069590be3c40148674aadd0b88d591") /*hUtils::CreateGUID()*/ );
//    m_databases->DeleteOperator(wxT("c52e5fc5acb544688e19e1ed8e8caf1f"));

    _updateOperatorChoice();
    wxString opUUID = m_databases->GetCassetteOperator();

    if (opUUID != wxEmptyString && opUUID != wxT("-1"))
    {
        wxLogStatus(wxT("opUUID is not null"));

        for (size_t i = 0; i < m_operators.GetCount(); i++)
        {
            if (m_operators.Item(i).UUID.Cmp(opUUID) == 0)
            {
                m_woperatorChoice->SetSelection(i);
                break;
            }
        }
    }
    else
    {
        if (m_operators.GetCount())
            m_databases->SetCassetteOperator(m_operators.Item(static_cast<size_t>(m_woperatorChoice->GetSelection())).UUID);
    }


    _initBrowser();
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

void HorusFrame::_logEvent(wxRichTextCtrl *ctrl, time_t ts, const wxString &op, const wxString &message, bool saveToDatabase)
{
    wxDateTime dt(ts);
    wxString timestamp = dt.Format(wxT("%a %b %d %Y %H:%M:%S "));

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
    ctrl->ScrollIntoView(m_wtextLogger->GetLastPosition(), /* WXK_PAGEDOWN */ WXK_END);
    ctrl->Thaw();

    if (! m_eventLockout)
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
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
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
    _dockCassette(true);
}

void HorusFrame::Onm_undockCassetteClick(wxCommandEvent& event)
{
    _dockCassette(false);
}

void HorusFrame::OnCassetteEvent(wxCommandEvent &event)
{
    HorusEventCassetteData *data = (HorusEventCassetteData *)event.GetClientData();

    //if (! m_eventLock)
    {
        //wxDateTime dt(data->TimeStamp);

        wxLogStatus(wxT("RX Event"));

        switch (event.GetInt())
        {
            case HORUS_EVENT_CARTRIDGE_LOAD:
                wxLogStatus(wxT("  ** Cartridge LOADED: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_wcartridgeNum->SetLabel(wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));

                _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cartridge #")
                          + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()) + wxT(" loaded."));

                m_wunloadStage->Enable(true);
                m_wkeepOnStage->Enable(true);
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CARTRIDGE_UNLOAD:
                wxLogStatus(wxT("  ** Cartridge UNLOADED: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_wcartridgeNum->SetLabel(wxT("<NONE>"));

                _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cartridge #")
                          + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()) + wxT(" unloaded."));

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
                wxLogStatus(wxT("  ** Cartridge UPDATE: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CASSETTE_DOCKED:
                {
                    wxLogStatus(wxT("  ** Cassette DOCKED."));

                    if (! m_cassette->IsStageEmpty() && ! m_wkeepOnStage->IsEnabled())
                        m_wkeepOnStage->Enable(true);

                    _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cassette Docked."));

                    m_wtextLogger->Clear();

                    m_databases->SetCassetteDocked(true);

                    time_t ts;

                    if (m_databases->GetCassetteDockTimeStamp(ts))
                    {
                        m_wdockedLabel->SetLabel(hUtils::GetTimeStampString(ts, false));
                        //Panel1->Layout();
                    }

    #warning CRAPPY
                    m_eventLockout = true;
                    _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cassette Docked."));
                    m_eventLockout = false;
                }
                break;

            case HORUS_EVENT_CASSETTE_REDOCKED:
                {
                    wxLogStatus(wxT("  ** Cassette REDOCKED."));

                    if (! m_cassette->IsStageEmpty() && ! m_wkeepOnStage->IsEnabled())
                        m_wkeepOnStage->Enable(true);

                    _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cassette Redocked."));

                    //m_wtextLogger->Clear();

                    m_databases->SetCassetteRedocked();

                    time_t ts;
                    if (m_databases->GetCassetteDockTimeStamp(ts))
                    {
                        m_wdockedLabel->SetLabel(hUtils::GetTimeStampString(ts, false));
                        //Panel1->Layout();
                    }

    //#warning CRAPPY
    //                m_eventLockout = true;
    //                _logEvent(data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cassette Redocked."));
    //                m_eventLockout = false;
                }
                break;

            case HORUS_EVENT_CASSETTE_UNDOCKED:
                wxLogStatus(wxT("  ** Cassette UNDOCKED."));

                _logEvent(m_wtextLogger, data->TimeStamp, m_woperatorChoice->GetString(m_woperatorChoice->GetSelection()), wxT("Cassette Undocked."));
                m_databases->SetCassetteDocked(false);
                m_wdockedLabel->SetLabel(wxT("< ----/--/-- --:--:-- >"));
                //m_wdockedOnSizer->La
                //Panel1->Layout();
                break;
        }
    }

    if (data)
        delete data;

}

void HorusFrame::OnDatabasePoolEvent(wxCommandEvent &event)
{
    HorusEventDatabaseData *data = (HorusEventDatabaseData *)event.GetClientData();

    switch (event.GetInt())
    {
        case HORUS_EVENT_DATABASEPOOL_RELOAD_EVENTS:
            m_eventLockout = true;
            wxLogStatus("EVENT!!!!!!");
            _logEvent(m_wtextLogger, data->TimeStamp, data->Operator, data->Message);
            m_eventLockout = false;
            break;

        case HORUS_EVENT_DATABASEPOOL_BACKUP:
            if (data)
            {
                wxLogStatus(wxT("New backup: ") + data->BackupFile);
                _extractCassetteFromDatabase(data->BackupFile);
            }
            break;
    }


    if (data)
        delete data;
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
            wxMessageBox(wxT("You have entered an incorrect session name."), wxT("Error"), wxOK|wxICON_ERROR);
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

            // First user added to the operator list
            // Set it as cassette operator
            if (m_operators.GetCount() == 1)
                m_databases->SetCassetteOperator(m_operators.Item(0).UUID);
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

void HorusFrame::Onm_operatorChoiceSelect(wxCommandEvent& event)
{
    if (! m_databases->SetCassetteOperator(m_operators.Item(static_cast<size_t>(m_woperatorChoice->GetSelection())).UUID))
    {
        wxMessageBox(wxT("Unable to update cassette's operator"), wxT("Error"), wxOK|wxICON_ERROR);
    }

    event.Skip();
}

void HorusFrame::Onm_keepOnStageClick(wxCommandEvent& event)
{
    m_databases->SetKeepOnStage(m_wkeepOnStage->GetValue());
}

void HorusFrame::Onm_wredockCassetteClick(wxCommandEvent& event)
{
    _dockCassette(true, true);
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

        wxLogStatus(wxT("Database ") + dbName + wxT(" dockTS : ") + dt.Format(wxT("%a %b %d %Y %H:%M:%S")));

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
            //wxDateTime pastDt = wxDateTime::Now().Subtract(wxDateSpan(0, 0, 0, m_config->GetBackupDuration()));

            for (size_t i = 0; i < backupFiles.GetCount(); i++)
            {
                wxLogStatus(wxT("Found Backupfile: ") + backupFiles.Item(i));

                _extractCassetteFromDatabase(backupFiles.Item(i));

            }

        }
    }

    m_wtreeCassettes->ExpandAll();
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
        time_t dockedTS, funeralTS;
        bool ok = true;
        int step = 0;
        //time_t ts = 0;
        //wxString op = wxEmptyString;
        wxSQLite3Database db;

        m_wbrowserOperator->SetLabel(opName);


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

                //m_wbrowserText->Freeze();

                while (q.NextRow())
                {
                    time_t   ts     = static_cast<time_t>(q.GetInt(1));
                    wxString op     = q.GetString(2);
                    wxString msg    = q.GetString(3);

                    //logger->cbiCallbackFunction(ts, op, msg);

                    //wxString str = wxT("Restore message ") + wxString::Format(wxT("%llu"), ts) + wxT(" [") + op + wxT("] ") + msg;
                    //wxLogStatus(str);

                    _logEvent(m_wbrowserText, ts, op, msg);
#if 0
                    wxDateTime dt(ts);
                    wxString timestamp = dt.Format(wxT("%a %b %d %Y %H:%M:%S "));


                    m_wbrowserText->SetInsertionPointEnd();

                    m_wbrowserText->BeginFontSize(10);

                    // Timestamp in bold
                    m_wbrowserText->BeginBold();
                    m_wbrowserText->WriteText(timestamp + wxT("[ "));

                    // Operator
                    m_wbrowserText->BeginTextColour(*wxBLUE);//wxColor(0, 0, 255));
                    m_wbrowserText->WriteText(op != wxEmptyString ? op : wxT("<UNKNOWN>"));
                    m_wbrowserText->EndTextColour();

                    m_wbrowserText->WriteText(wxT(" ] :: "));
                    m_wbrowserText->EndBold();

                    // Then text
                    m_wbrowserText->WriteText(msg + wxT("\n"));


                    // Move to the end of the text
                    m_wbrowserText->ScrollIntoView(m_wbrowserText->GetLastPosition(), /* WXK_PAGEDOWN */ WXK_END);
#endif
                }

                //m_wbrowserText->Thaw();
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

            ok = false;
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
        wxLogStatus(wxT("CLICKED: data OK"));
        //_displayCassetteInfos(data->GetDatabaseFilename();
        opName = data->GetOperatorName();
        dbName = data->GetDatabaseFilename();
    }
    else
    {
        wxLogStatus(wxT("CLICKED: NO data"));
    }

    _displayCassetteInfos(opName, dbName);

    event.Skip();
}

void HorusFrame::OnBrowserGridResize(wxSizeEvent& event)
{
    wxSize sz = m_wbrowserGrid->GetClientSize();
    m_wbrowserGrid->SetColSize(0, sz.GetWidth() - m_wbrowserGrid->GetRowLabelSize());

    event.Skip();
}

void HorusFrame::OnSplitterWindow1SashPosChanged(wxSplitterEvent& event)
{
    wxSize sz = m_wbrowserGrid->GetSize();
    m_wbrowserGrid->SetColSize(0, sz.GetWidth() - m_wbrowserGrid->GetRowLabelSize() - 1);

    event.Skip();
}

} // namespace
