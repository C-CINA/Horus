#include "../HorusMain.h"

namespace Horus
{

//
// ///////////////////////////////////////////////////////////////////////
//
// HorusCartridge class
//
// ///////////////////////////////////////////////////////////////////////
//

HorusCartridge::HorusCartridge(HorusCassette *cassette, wxWindow *parent, size_t counter, wxWindowID id)
    : wxPanel(parent, id),
    m_cassette(cassette),
    m_parent(parent),
    m_counter(counter),
    m_state(CARTRIDGE_STATE_EMPTY),
    m_stateUnloaded(CARTRIDGE_STATE_UNKNOWN),
    m_silent(false)
{
    wxBoxSizer *boxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *staticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, wxEmptyString);
    wxBoxSizer *boxSizer2 = new wxBoxSizer(wxHORIZONTAL);

    m_panelLabel = new wxPanel(this, wxNewId(), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL);
    m_panelLabel->SetBackgroundColour(wxColour(255,255,128));
    wxBoxSizer *boxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    m_label = new wxStaticText(m_panelLabel, wxNewId(), wxString::Format(wxT("%zu"), counter), wxDefaultPosition, wxSize(80, -1), wxALIGN_CENTRE);

    // Bold label
    wxFont StaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);

    if (! StaticTextFont.Ok())
        StaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);

    StaticTextFont.SetWeight(wxFONTWEIGHT_BOLD);
    m_label->SetFont(StaticTextFont);
    boxSizer6->Add(m_label, 0, wxTOP|wxBOTTOM|wxEXPAND, 6);
    m_panelLabel->SetSizer(boxSizer6);
    boxSizer6->Fit(m_panelLabel);
    boxSizer6->SetSizeHints(m_panelLabel);

    boxSizer2->Add(m_panelLabel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    staticBoxSizer1->Add(boxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_text = new wxTextCtrl(this, wxNewId(), wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
    m_text->SetMaxLength(80);
    staticBoxSizer1->Add(m_text, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxBoxSizer *boxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer *staticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, wxEmptyString);

    m_loadToggle = new wxBitmapToggleButton(this, wxNewId(), *hUtils::CreateBitmapFromPNGResource(wxT("TOGGLE_OUT")), wxDefaultPosition, wxDefaultSize, wxNO_BORDER, wxDefaultValidator);
    staticBoxSizer2->Add(m_loadToggle, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_loadToggle->SetBitmapDisabled(*hUtils::CreateBitmapFromPNGResource(wxT("TOGGLE_OUT_DISABLED")));
    m_loadToggle->SetBitmapPressed(*hUtils::CreateBitmapFromPNGResource(wxT("TOGGLE_IN")));
    m_loadToggle->Enable(false);

    boxSizer3->Add(staticBoxSizer2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticBoxSizer1->Add(boxSizer3, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    wxBoxSizer *boxSizer4 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *boxSizer5 = new wxBoxSizer(wxVERTICAL);
    m_keepIt = new wxCheckBox(this, wxNewId(), _("Keep It"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
    m_keepIt->SetValue(false);
    boxSizer5->Add(m_keepIt, 0, wxALL|wxEXPAND, 5);
    m_empty = new wxCheckBox(this, wxNewId(), _("Empty"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
    m_empty->SetValue(true);
    boxSizer5->Add(m_empty, 0, wxALL|wxEXPAND, 5);
    boxSizer4->Add(boxSizer5, 1, wxALL|wxEXPAND, 5);
    staticBoxSizer1->Add(boxSizer4, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    boxSizer1->Add(staticBoxSizer1, 1, wxEXPAND, 0);
    this->SetSizer(boxSizer1);
    boxSizer1->Fit(this);
    boxSizer1->SetSizeHints(this);

    Connect(wxEVT_CONTEXT_MENU, (wxObjectEventFunction)&HorusCartridge::OnContextMenu);
    Connect(m_text->GetId(), wxEVT_COMMAND_TEXT_UPDATED, (wxObjectEventFunction)&HorusCartridge::OnText);
    Connect(m_empty->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&HorusCartridge::OnEmpty);
    Connect(m_keepIt->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&HorusCartridge::OnKeepIt);
    Connect(m_loadToggle->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, (wxObjectEventFunction)&HorusCartridge::OnToggleLoad);


    _setState(m_state);
}

HorusCartridge::~HorusCartridge()
{

}

void HorusCartridge::Clear()
{
    if (! m_keepIt->GetValue() && ! m_loadToggle->GetValue())
    {
        m_text->SetValue(wxEmptyString);
        m_empty->SetValue(true);
    }
}

bool HorusCartridge::Load(bool load, bool force)
{

    if ((load && (m_state == CARTRIDGE_STATE_LOADED)) || (! load && (m_state != CARTRIDGE_STATE_LOADED)))
        return false;

    //bool        value = load;
    wxString    str = wxT("Do you really want to ");

    str += (load ? wxT("load") : wxT("unload"));
    str << wxT(" cartridge #") << wxString::Format(wxT("%zu"), m_counter) << wxT(" ?.");

    if (force || (! force && wxMessageBox(str, wxT("Question"), wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION) == wxYES))
    {
        // Eject the cartridge loaded on stage, if different from the current one
        if (! m_cassette->IsStageEmpty() && (m_cassette->GetLoadedCartridge() != this))
            m_cassette->UnloadStage();

        _setState(load ? CARTRIDGE_STATE_LOADED : CARTRIDGE_STATE_UNLOADED);
    }
    else
        m_loadToggle->SetValue(! load);


    return true;
}

bool HorusCartridge::Unload()
{
    return Load(false);
}

void HorusCartridge::OnContextMenu(wxContextMenuEvent &event)
{
    wxLogStatus(wxT("Context"));

    wxMenu menu;

    menu.SetTitle(wxString::Format(wxT("Slot #%zu"), m_counter));
    menu.Append(wxNewId(), wxT("Entry 1"), wxEmptyString, wxITEM_NORMAL);
    menu.Append(wxNewId(), wxT("Entry 2"), wxEmptyString, wxITEM_NORMAL);
    menu.AppendSeparator();
    menu.Append(wxNewId(), wxT("Entry 3"), wxEmptyString, wxITEM_NORMAL);
    menu.Append(wxNewId(), wxT("Entry 4"), wxEmptyString, wxITEM_NORMAL);

    PopupMenu(&menu);
}

void HorusCartridge::_changeText(const wxString &str)
{
    if (str != wxEmptyString && str.Len())
    {
        m_empty->SetValue(false);
        _setState(CARTRIDGE_STATE_OCCUPIED);
        _sendEvent(HORUS_EVENT_CARTRIDGE_UPDATE);
    }
    else
        _setState(CARTRIDGE_STATE_EMPTY);
}

void HorusCartridge::OnText(wxCommandEvent &event)
{
    wxString str = m_text->GetValue();

    _changeText(str);

    event.Skip();
}


void HorusCartridge::OnEmpty(wxCommandEvent &event)
{
    _setState(m_empty->GetValue() ? CARTRIDGE_STATE_EMPTY : CARTRIDGE_STATE_OCCUPIED);

    m_loadToggle->Enable(!m_empty->GetValue());

    _sendEvent(HORUS_EVENT_CARTRIDGE_UPDATE);

    event.Skip();
}

void HorusCartridge::OnKeepIt(wxCommandEvent &event)
{
    _sendEvent(HORUS_EVENT_CARTRIDGE_UPDATE);

    event.Skip();
}


void HorusCartridge::OnToggleLoad(wxCommandEvent &event)
{
    Load(m_loadToggle->GetValue());

    event.Skip();
}

void HorusCartridge::_setState(HorusCartridgeState state)
{
    if (state == CARTRIDGE_STATE_LOADED)
        m_stateUnloaded = m_state;

    m_state = state;

    switch (m_state)
    {
        case CARTRIDGE_STATE_EMPTY:
            m_label->SetForegroundColour(wxColour(0, 0, 0));
            m_panelLabel->SetBackgroundColour(wxColour(255, 255, 128));
            m_empty->Enable(true);
            m_loadToggle->Enable(false);
            break;

        case CARTRIDGE_STATE_OCCUPIED:
            m_label->SetForegroundColour(wxColour(255, 255, 255));
            m_panelLabel->SetBackgroundColour(wxColour(40, 40, 255));
            m_empty->Enable(true);
            m_loadToggle->Enable(true);
            break;

        case CARTRIDGE_STATE_LOADED:
            m_label->SetForegroundColour(wxColour(255, 255, 255));
            m_panelLabel->SetBackgroundColour(wxColour(255, 0, 0));

            m_empty->Enable(false);
            m_loadToggle->Enable(true);

            if (! m_loadToggle->GetValue())
                m_loadToggle->SetValue(true);

            _sendEvent(HORUS_EVENT_CARTRIDGE_LOAD);

            m_cassette->CartridgeLoaded(this);
            break;

        case CARTRIDGE_STATE_UNLOADED:
            m_state = m_stateUnloaded;

            if (m_loadToggle->GetValue())
                m_loadToggle->SetValue(false);

            _sendEvent(HORUS_EVENT_CARTRIDGE_UNLOAD);

            _setState(m_state);
           break;

        case CARTRIDGE_STATE_UNKNOWN:
            break;
    }

    m_panelLabel->Refresh();

#ifdef DEBUG
    wxString s = wxT(">>> State: ");

    switch (m_state)
    {
        case CARTRIDGE_STATE_EMPTY:
            s += wxT("EMPTY");
            break;

        case CARTRIDGE_STATE_OCCUPIED:
            s += wxT("OCCUPIED");
            break;

        case CARTRIDGE_STATE_LOADED:
            s += wxT("LOADED");
           break;

        case CARTRIDGE_STATE_UNKNOWN:
            s += wxT("UNKNOWN");
            break;
    }

    wxLogStatus(s);

    s = wxT(">>> Previous State: ");

    switch (m_stateUnloaded)
    {
        case CARTRIDGE_STATE_EMPTY:
            s += wxT("EMPTY");
            break;

        case CARTRIDGE_STATE_OCCUPIED:
            s += wxT("OCCUPIED");
            break;

        case CARTRIDGE_STATE_LOADED:
            s += wxT("LOADED");
           break;

        case CARTRIDGE_STATE_UNKNOWN:
            s += wxT("UNKNOWN");
            break;
    }

    wxLogStatus(s);
#endif
}

void HorusCartridge::_sendEvent(HorusCassetteEvent eventID)
{
    if (m_silent)
        return;

    HorusEventCassetteData *data = new HorusEventCassetteData(this);
    wxCommandEvent          event(wxEVT_HORUS_CASSETTE, GetId());

    event.SetInt(eventID);

    event.SetClientData((void *)data);

    wxPostEvent((wxEvtHandler *)m_parent, event);
}


//
// ///////////////////////////////////////////////////////////////////////
//
// HorusStage class
//
// ///////////////////////////////////////////////////////////////////////
//

HorusStage::HorusStage() : m_cartridge(NULL), m_keepOnStage(false)
{

}

HorusStage::~HorusStage()
{

}

bool HorusStage::Load(HorusCartridge *cartridge)
{
    if (! m_cartridge)
        return false;

    m_cartridge = cartridge;
    return true;
}

bool HorusStage::IsEmpty()
{
    return (m_cartridge == NULL);
}

HorusCartridge *HorusStage::GetLoadedCartridge() const
{
    return m_cartridge;
}


//
// ///////////////////////////////////////////////////////////////////////
//
// HorusCassette class
//
// ///////////////////////////////////////////////////////////////////////
//

HorusCassette::HorusCassette(wxWindow *parent, wxBoxSizer *sizer) : m_parent(parent), m_docked(false)
{
    for (size_t i = 0; i < MAX_CARTRIDGE_SLOTS; i++)
    {
        m_cartridges[i] = new HorusCartridge(this, parent, i + 1);
        sizer->Add(m_cartridges[i], 0, wxEXPAND, 5);
    }

    m_stage = new HorusStage();
}


HorusCassette::~HorusCassette()
{

}

bool HorusCassette::_dock(bool redock)
{
    if (m_docked)
        return false;

    m_docked = true;

    // Send DOCK event
    _sendEvent(redock ? HORUS_EVENT_CASSETTE_REDOCKED : HORUS_EVENT_CASSETTE_DOCKED);

    if (! redock)
    {
        for (size_t i = 0; i < MAX_CARTRIDGE_SLOTS; i++)
            m_cartridges[i]->Clear();
    }

    return true;
}

bool HorusCassette::RedockCassette()
{
    return _dock(true);
}

bool HorusCassette::DockCassette()
{
    return _dock(false);
}

bool HorusCassette::UndockCassette()
{
    if (! m_docked)
        return false;

    m_docked = false;

    // Send undock event
    _sendEvent(HORUS_EVENT_CASSETTE_UNDOCKED);

    return true;
}

}
