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
const long HorusFrame::ID_STATICTEXT1 = wxNewId();
const long HorusFrame::ID_STATICTEXT2 = wxNewId();
const long HorusFrame::ID_BUTTON2 = wxNewId();
const long HorusFrame::ID_BUTTON3 = wxNewId();
const long HorusFrame::ID_CHOICE1 = wxNewId();
const long HorusFrame::ID_BUTTON4 = wxNewId();
const long HorusFrame::ID_BUTTON5 = wxNewId();
const long HorusFrame::ID_TEXTCTRL1 = wxNewId();
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

HorusFrame::HorusFrame(wxWindow* parent,wxWindowID id)// : m_operators
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
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer12;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer9;
    wxMenuBar* MenuBar1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    AuiNotebook1 = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH);
    AuiNotebook1->SetMinSize(wxSize(800,300));
    Panel1 = new wxPanel(AuiNotebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer8 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4->Add(BoxSizer8, 0, wxALL|wxEXPAND, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("  Cassette  "));
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("New Cassette"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticBoxSizer1->Add(Button1, 0, wxALL|wxALIGN_LEFT, 5);
    m_slotSizer = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer1->Add(m_slotSizer, 1, wxALL|wxEXPAND, 5);
    BoxSizer6->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
    BoxSizer4->Add(BoxSizer6, 1, wxALL|wxEXPAND, 5);
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("  On Stage  "));
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Loaded Cartridge: "), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
    BoxSizer7->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_cartridgeNum = new wxStaticText(Panel1, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer7->Add(m_cartridgeNum, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(BoxSizer7, 1, wxALL|wxEXPAND, 5);
    m_unloadStage = new wxButton(Panel1, ID_BUTTON2, _("Unload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    m_unloadStage->Disable();
    StaticBoxSizer3->Add(m_unloadStage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(Panel1, ID_BUTTON3, _("Save DB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    StaticBoxSizer3->Add(Button3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND, 5);
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
    BoxSizer3->Add(BoxSizer4, 0, wxALL|wxEXPAND, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    m_textLogger = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
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

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::OnButton2Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HorusFrame::OnButton3Click);
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

    m_cassette = new HorusCassette(Panel1, m_slotSizer);

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

    //m_eventLock = true;

    m_cassette->SetSilent(true);

    m_databases = new HorusDatabasePool();

    m_operators.Add(new Operator(wxT("zorglub"), wxT("1234657980")));
    m_operators.Add(new Operator(wxT("Tralala"), wxT("1234657980")));
    m_operators.Add(new Operator(wxT("AAA"), wxT("1234657980")));
    m_operators.Add(new Operator(wxT("Glob"), wxT("1234657980")));
    m_operators.Add(new Operator(wxT("Cuite"), wxT("1234657980")));
    m_operators.Add(new Operator(wxT("Poele"), wxT("1234657980")));

    m_operators.Sort(&hUtils::CompareOperators);


    if (m_databases->Initialize(m_cassette))
    {
        if (! m_databases->ReloadData(m_operators))
            Close();

        if (! m_cassette->IsStageEmpty())
        {
            HorusCartridge *slot = m_cassette->GetLoadedCartridge();

            m_unloadStage->Enable(true);
            m_cartridgeNum->SetLabel(wxString::Format(wxT("%zu"), slot->GetNumber()));
        }
    }
    else
    {

    }

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

void HorusFrame::OnButton1Click(wxCommandEvent& event)
{
#if 0
    wxSizerItemList           &items = m_slotSizer->GetChildren();
    wxSizerItemList::iterator  it = items.begin();

    while(it != items.end())
    {
        if ((*it)->IsWindow() && wxIsKindOf((*it)->GetWindow(), HorusSlot))
        {
            HorusSlot *slot = wxDynamicCast((*it)->GetWindow(), HorusSlot);

            slot->Nullify();
        }

        it++;
    }
#else
    m_cassette->LoadNewCassette();
#endif
}

void HorusFrame::OnCassetteEvent(wxCommandEvent &event)
{
    HorusEventCassetteData *data = (HorusEventCassetteData *)event.GetClientData();

    //if (! m_eventLock)
    {
        wxDateTime dt(data->TimeStamp);

        wxLogStatus(wxT("RX Event"));

        switch (event.GetInt())
        {
            case HORUS_EVENT_CASSETTE_LOAD:
                wxLogStatus(wxT("  ** Cassette LOADED: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_cartridgeNum->SetLabel(wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));

                *m_textLogger << dt.Format(wxT("%a %b %d %Y %H:%M:%S")) << wxT(": Cartridge #") << wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()) << wxT(" Loaded.") << wxT("\n");

                m_unloadStage->Enable(true);
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CASSETTE_UNLOAD:
                wxLogStatus(wxT("  ** Cassette UNLOADED: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_cartridgeNum->SetLabel(wxT("<NONE>"));

                *m_textLogger << dt.Format(wxT("%a %b %d %Y %H:%M:%S")) << wxT(": Cartridge #") << wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()) << wxT(" Unloaded.") << wxT("\n");

                m_unloadStage->Enable(false);
                m_databases->UpdateCartridge(data->Cartridge);
                break;

            case HORUS_EVENT_CARTRIDGE_UPDATE:
                // Update Database
                wxLogStatus(wxT("  ** Cartridge UPDATE: ") + wxString::Format(wxT("%zu"), data->Cartridge->GetNumber()));
                m_databases->UpdateCartridge(data->Cartridge);
                break;
        }
    }

    if (data)
        delete data;

}

void HorusFrame::OnButton2Click(wxCommandEvent& event)
{
    m_cassette->UnloadStage();
}

void HorusFrame::OnButton3Click(wxCommandEvent& event)
{
    //m_databases->_saveDB();
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
        wxMessageBox(wxT("Uname to update cassette's operator"), wxT("Error"), wxOK|wxICON_ERROR);
    }

    event.Skip();
}


} // namespace

