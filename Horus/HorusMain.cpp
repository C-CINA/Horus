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

DEFINE_EVENT_TYPE(wxEVT_HORUS_CASSETTE); ///< Event that receiver may handle


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
const long HorusFrame::ID_BUTTON6 = wxNewId();
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
const long HorusFrame::ID_AUINOTEBOOK1 = wxNewId();
const long HorusFrame::idMenuQuit = wxNewId();
const long HorusFrame::idMenuAbout = wxNewId();
const long HorusFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HorusFrame,wxFrame)
    //(*EventTable(HorusFrame)
    //*)
    EVT_COMMAND(wxID_ANY, Horus::wxEVT_HORUS_CASSETTE, HorusFrame::OnCassetteEvent)
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
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxMenuItem* MenuItem2;
    wxBoxSizer* BoxSizer13;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer16;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer18;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer17;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer9;
    wxMenuBar* MenuBar1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    AuiNotebook1 = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH);
    AuiNotebook1->SetMinSize(wxSize(800,500));
    Panel1 = new wxPanel(AuiNotebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    m_cassetteSizer = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("  Cassette  "));
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    m_dockCassette = new wxButton(Panel1, ID_BUTTON1, _("Dock Cassette"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer13->Add(m_dockCassette, 0, wxALL, 5);
    m_undockCassette = new wxButton(Panel1, ID_BUTTON6, _("Undock Cassette"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer13->Add(m_undockCassette, 0, wxALL, 5);
    BoxSizer8->Add(BoxSizer13, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_cassetteSizer->Add(BoxSizer8, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer14 = new wxBoxSizer(wxVERTICAL);
    BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer16 = new wxBoxSizer(wxVERTICAL);
    m_scrolledCartridges = new wxScrolledWindow(Panel1, ID_SCROLLEDWINDOW1, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW1"));
    m_slotSizer = new wxBoxSizer(wxVERTICAL);
    m_scrolledCartridges->SetSizer(m_slotSizer);
    m_slotSizer->Fit(m_scrolledCartridges);
    m_slotSizer->SetSizeHints(m_scrolledCartridges);
    BoxSizer16->Add(m_scrolledCartridges, 1, wxEXPAND, 5);
    BoxSizer15->Add(BoxSizer16, 1, wxEXPAND, 5);
    BoxSizer14->Add(BoxSizer15, 1, wxEXPAND, 5);
    m_cassetteSizer->Add(BoxSizer14, 1, wxLEFT|wxRIGHT|wxEXPAND, 5);
    BoxSizer6->Add(m_cassetteSizer, 1, wxALL|wxEXPAND, 5);
    BoxSizer4->Add(BoxSizer6, 1, wxALL|wxEXPAND, 5);
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    m_stageSizer = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("  On Stage  "));
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Loaded Cartridge: "), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
    BoxSizer7->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_cartridgeNum = new wxStaticText(Panel1, ID_STATICTEXT2, _("<NONE>"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer7->Add(m_cartridgeNum, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_stageSizer->Add(BoxSizer7, 0, wxALL|wxEXPAND, 5);
    BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    m_scrolledStage = new wxScrolledWindow(Panel1, ID_SCROLLEDWINDOW2, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW2"));
    BoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer19 = new wxBoxSizer(wxVERTICAL);
    m_keepOnStage = new wxCheckBox(m_scrolledStage, ID_CHECKBOX1, _("Keep On Stage"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    m_keepOnStage->SetValue(false);
    m_keepOnStage->Disable();
    BoxSizer19->Add(m_keepOnStage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_unloadStage = new wxButton(m_scrolledStage, ID_BUTTON2, _("Unload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    m_unloadStage->Disable();
    BoxSizer19->Add(m_unloadStage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer18->Add(BoxSizer19, 1, wxALL|wxEXPAND, 5);
    m_scrolledStage->SetSizer(BoxSizer18);
    BoxSizer18->Fit(m_scrolledStage);
    BoxSizer18->SetSizeHints(m_scrolledStage);
    BoxSizer17->Add(m_scrolledStage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_stageSizer->Add(BoxSizer17, 1, wxALL|wxEXPAND, 5);
    BoxSizer5->Add(m_stageSizer, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("  Operator  "));
    BoxSizer10 = new wxBoxSizer(wxVERTICAL);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    m_operatorChoice = new wxChoice(Panel1, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    BoxSizer11->Add(m_operatorChoice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12 = new wxBoxSizer(wxVERTICAL);
    m_addOperator = new wxButton(Panel1, ID_BUTTON4, _("+"), wxDefaultPosition, wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    m_addOperator->SetToolTip(_("Add an Operator"));
    BoxSizer12->Add(m_addOperator, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_deleteOperator = new wxButton(Panel1, ID_BUTTON5, _("-"), wxDefaultPosition, wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    m_deleteOperator->Disable();
    m_deleteOperator->SetToolTip(_("Delete Selected Operator"));
    BoxSizer12->Add(m_deleteOperator, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer11->Add(BoxSizer12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer10->Add(BoxSizer11, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer2->Add(BoxSizer10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 5);
    BoxSizer4->Add(BoxSizer5, 0, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer4, 1, wxALL|wxEXPAND, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    m_textLogger = new wxRichTextCtrl(Panel1, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
    wxRichTextAttr rchtxtAttr_1;
    rchtxtAttr_1.SetFlags(wxTEXT_ATTR_TEXT_COLOUR|wxTEXT_ATTR_BACKGROUND_COLOUR|wxTEXT_ATTR_FONT_FACE|wxTEXT_ATTR_FONT_SIZE|wxTEXT_ATTR_FONT_WEIGHT|wxTEXT_ATTR_FONT_ITALIC|wxTEXT_ATTR_FONT_UNDERLINE|wxTEXT_ATTR_FONT|wxTEXT_ATTR_ALIGNMENT|wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT|wxTEXT_ATTR_TABS|wxTEXT_ATTR_PARA_SPACING_AFTER|wxTEXT_ATTR_PARA_SPACING_BEFORE|wxTEXT_ATTR_LINE_SPACING|wxTEXT_ATTR_CHARACTER_STYLE_NAME|wxTEXT_ATTR_PARAGRAPH_STYLE_NAME|wxTEXT_ATTR_LIST_STYLE_NAME|wxTEXT_ATTR_BULLET_STYLE|wxTEXT_ATTR_BULLET_NUMBER|wxTEXT_ATTR_BULLET_TEXT|wxTEXT_ATTR_BULLET_NAME|wxTEXT_ATTR_URL|wxTEXT_ATTR_PAGE_BREAK|wxTEXT_ATTR_EFFECTS|wxTEXT_ATTR_OUTLINE_LEVEL);
    rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    m_textLogger->SetBasicStyle(rchtxtAttr_1);
    BoxSizer9->Add(m_textLogger, 1, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer9, 1, wxALL|wxEXPAND, 5);
    Panel1->SetSizer(BoxSizer3);
    BoxSizer3->Fit(Panel1);
    BoxSizer3->SetSizeHints(Panel1);
    AuiNotebook1->AddPage(Panel1, _("Cassette Logger"));
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
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_undockCassetteClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_keepOnStageClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_unloadStageClick);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&HorusFrame::Onm_operatorChoiceSelect);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_addOperatorClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::Onm_deleteOperatorClick);
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

    m_cassette = new HorusCassette(m_scrolledCartridges, m_slotSizer);
    m_scrolledCartridges->Fit();
    wxSize ws = m_scrolledCartridges->GetSize();
    m_scrolledCartridges->SetMinSize(wxSize(-1, ws.GetHeight()));
    m_scrolledCartridges->SetMaxSize(wxSize(-1, ws.GetHeight()));

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

    m_databases = new HorusDatabasePool();

    if (m_databases->Initialize(m_cassette))
    {
        if (! m_databases->ReloadData(m_operators, this))
            Close();

        if (! m_cassette->IsStageEmpty())
        {
            HorusCartridge *slot = m_cassette->GetLoadedCartridge();

            m_unloadStage->Enable(true);
            m_cartridgeNum->SetLabel(wxString::Format(wxT("%zu"), slot->GetNumber()));
        }
    }

    m_keepOnStage->SetValue(m_databases->GetKeepOnStage());

    _dockCassette(m_databases->GetCassetteDocked());

    if (! m_cassette->IsStageEmpty() && ! m_keepOnStage->IsEnabled())
        m_keepOnStage->Enable(true);

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

    if (opUUID != wxEmptyString)
    {
        wxLogStatus(wxT("opUUID is not null"));

        for (size_t i = 0; i < m_operators.GetCount(); i++)
        {
            if (m_operators.Item(i).UUID.Cmp(opUUID) == 0)
            {
                m_operatorChoice->SetSelection(i);
                break;
            }
        }
    }
    else
    {
        if (m_operators.GetCount())
            m_databases->SetCassetteOperator(m_operators.Item(static_cast<size_t>(m_operatorChoice->GetSelection())).UUID);
    }
}

HorusFrame::~HorusFrame()
{
    //(*Destroy(HorusFrame)
    //*)
}

void HorusFrame::_updateOperatorChoice()
{
    m_operatorChoice->Clear();

    for (size_t i = 0; i < m_operators.GetCount(); i++)
        m_operatorChoice->Append(m_operators.Item(i).Name);

    if (m_operators.GetCount())
    {
        m_operatorChoice->SetSelection(0);
        m_deleteOperator->Enable(true);
        m_operatorChoice->Fit();
        m_operatorChoice->GetParent()->Fit();
        m_operatorChoice->GetParent()->Layout();
        Layout();
    }
    else
    {
        m_deleteOperator->Enable(false);
    }
}

void HorusFrame::_logEvent(time_t ts, const wxString &op, const wxString &message)
{
    wxDateTime dt(ts);
    wxString timestamp = dt.Format(wxT("%a %b %d %Y %H:%M:%S "));

    m_textLogger->Freeze();

    m_textLogger->SetInsertionPointEnd();

    m_textLogger->BeginFontSize(10);

    // Timestamp in bold
    m_textLogger->BeginBold();
    m_textLogger->WriteText(timestamp + wxT("[ "));

    // Operator
    m_textLogger->BeginTextColour(*wxBLUE);//wxColor(0, 0, 255));
    m_textLogger->WriteText(op);
    m_textLogger->EndTextColour();

    m_textLogger->WriteText(wxT(" ] :: "));
    m_textLogger->EndBold();

    // Then text
    m_textLogger->WriteText(message + wxT("\n"));


    // Move to the end of the text
    m_textLogger->ScrollIntoView(m_textLogger->GetLastPosition(), /* WXK_PAGEDOWN */ WXK_END);
    m_textLogger->Thaw();

    if (! m_eventLockout)
    {
        if (! m_databases->LogCassetteEvent(ts, op, message))
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

void HorusFrame::_dockCassette(bool dock, bool silent)
{
    switch (dock)
    {
        case true:
            m_cassette->DockCassette();
            m_dockCassette->Enable(false);
            m_undockCassette->Enable(true);
            m_scrolledCartridges->Enable(true);
            m_scrolledStage->Enable(true);

//            if (! silent)
//                _logEvent(wxDateTime::Now().GetTicks(), m_operatorChoice->GetString(m_operatorChoice->GetSelection()), wxT("Cassette docked."));
            break;

        case false:
            if (! m_keepOnStage->GetValue())
                m_cassette->UnloadStage();

            m_cassette->UndockCassette();

            m_dockCassette->Enable(true);
            m_undockCassette->Enable(false);
            m_scrolledCartridges->Enable(false);
            m_scrolledStage->Enable(false);

//            if (! silent)
//                _logEvent(wxDateTime::Now().GetTicks(), m_operatorChoice->GetString(m_operatorChoice->GetSelection()), wxT("Cassette undocked."));
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
                m_cartridgeNum->SetLabel(wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));

                _logEvent(data->TimeStamp, m_operatorChoice->GetString(m_operatorChoice->GetSelection()), wxT("Cartridge #")
                          + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()) + wxT(" loaded."));

                m_unloadStage->Enable(true);
                m_keepOnStage->Enable(true);
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CARTRIDGE_UNLOAD:
                wxLogStatus(wxT("  ** Cartridge UNLOADED: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_cartridgeNum->SetLabel(wxT("<NONE>"));

                _logEvent(data->TimeStamp, m_operatorChoice->GetString(m_operatorChoice->GetSelection()), wxT("Cartridge #")
                          + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()) + wxT(" unloaded."));

                if (m_keepOnStage->GetValue())
                {
                    m_keepOnStage->SetValue(false);
                    m_databases->SetKeepOnStage(false);
                }

                m_unloadStage->Enable(false);
                m_keepOnStage->Enable(false);
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CARTRIDGE_UPDATE:
                // Update Database
                wxLogStatus(wxT("  ** Cartridge UPDATE: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CASSETTE_DOCKED:
                wxLogStatus(wxT("  ** Cassette DOCKED."));

                if (! m_cassette->IsStageEmpty() && ! m_keepOnStage->IsEnabled())
                    m_keepOnStage->Enable(true);

                _logEvent(data->TimeStamp, m_operatorChoice->GetString(m_operatorChoice->GetSelection()), wxT("Cassette Docked."));
                m_databases->SetCassetteDocked(true);
                break;

            case HORUS_EVENT_CASSETTE_UNDOCKED:
                wxLogStatus(wxT("  ** Cassette UNDOCKED."));

                _logEvent(data->TimeStamp, m_operatorChoice->GetString(m_operatorChoice->GetSelection()), wxT("Cassette Undocked."));
                m_databases->SetCassetteDocked(false);
                break;
        }
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
    size_t selected = static_cast<size_t>(m_operatorChoice->GetSelection());//static_cast<size_t>(event.GetInt());

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
    if (! m_databases->SetCassetteOperator(m_operators.Item(static_cast<size_t>(m_operatorChoice->GetSelection())).UUID))
    {
        wxMessageBox(wxT("Unable to update cassette's operator"), wxT("Error"), wxOK|wxICON_ERROR);
    }

    event.Skip();
}

void HorusFrame::Onm_keepOnStageClick(wxCommandEvent& event)
{
    m_databases->SetKeepOnStage(m_keepOnStage->GetValue());
}

} // namespace

