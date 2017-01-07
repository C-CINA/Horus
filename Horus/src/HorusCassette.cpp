/// -----------------------------------------------------------------------------
///
/// \file HorusCassette.cpp
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

#include "../HorusMain.h"

namespace Horus
{

DEFINE_EVENT_TYPE(wxEVT_HORUS_CASSETTE); ///< Event that receiver may handle

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
    m_label->SetToolTip(wxT("Cartridge #") + wxString::Format(wxT("%zu"), counter));

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
    m_text->SetToolTip(wxT("Grid description."));
    m_text->SetMaxLength(80);
    staticBoxSizer1->Add(m_text, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxBoxSizer *boxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    //wxStaticBoxSizer *staticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, wxEmptyString);

    m_loadToggle = new wxBitmapToggleButton(this, wxNewId(), *hUtils::CreateBitmapFromPNGResource(wxT("TOGGLE_OUT")), wxDefaultPosition, wxDefaultSize, wxNO_BORDER, wxDefaultValidator);
    m_loadToggle->SetToolTip(wxT("Cartridge insertion/ejection."));
    //staticBoxSizer2->Add(m_loadToggle, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_loadToggle->SetBitmapDisabled(*hUtils::CreateBitmapFromPNGResource(wxT("TOGGLE_OUT_DISABLED")));
    m_loadToggle->SetBitmapPressed(*hUtils::CreateBitmapFromPNGResource(wxT("TOGGLE_IN")));
    m_loadToggle->Enable(false);

    //boxSizer3->Add(staticBoxSizer2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer3->Add(m_loadToggle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticBoxSizer1->Add(boxSizer3, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    wxBoxSizer *boxSizer4 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *boxSizer5 = new wxBoxSizer(wxVERTICAL);
    m_keepIt = new wxCheckBox(this, wxNewId(), _("Keep It"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
    m_keepIt->SetToolTip(wxT("Keep the cartridge on next docking."));
    m_keepIt->SetValue(false);
    boxSizer5->Add(m_keepIt, 0, wxALL|wxEXPAND, 5);
    m_empty = new wxCheckBox(this, wxNewId(), _("Empty"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
    m_empty->SetToolTip(wxT("Set cartridge emptiness state."));
    m_empty->SetValue(true);
    boxSizer5->Add(m_empty, 0, wxALL|wxEXPAND, 5);
    boxSizer4->Add(boxSizer5, 1, wxALL|wxEXPAND, 5);
    staticBoxSizer1->Add(boxSizer4, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    boxSizer1->Add(staticBoxSizer1, 1, wxEXPAND, 0);
    this->SetSizer(boxSizer1);
    boxSizer1->Fit(this);
    boxSizer1->SetSizeHints(this);

    //Connect(wxEVT_CONTEXT_MENU, (wxObjectEventFunction)&HorusCartridge::OnContextMenu);
    Connect(m_text->GetId(), wxEVT_COMMAND_TEXT_UPDATED, (wxObjectEventFunction)&HorusCartridge::OnText);
    Connect(m_empty->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&HorusCartridge::OnEmpty);
    Connect(m_keepIt->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&HorusCartridge::OnKeepIt);
    //Connect(m_loadToggle->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, (wxObjectEventFunction)&HorusCartridge::OnToggleLoad);
    m_loadToggle->Connect(m_loadToggle->GetId(), wxEVT_LEFT_DOWN, (wxObjectEventFunction)&HorusCartridge::OnRightDown, NULL, this);

    _setState(m_state);
}

HorusCartridge::~HorusCartridge()
{

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

void HorusCartridge::Clear()
{
    if (! m_keepIt->GetValue() && ! m_loadToggle->GetValue())
    {
        m_text->SetValue(wxEmptyString);
        m_empty->SetValue(true);
    }
}

size_t HorusCartridge::GetNumber()
{
    return m_counter;
}

bool HorusCartridge::SetText(const wxString &str)
{
    m_text->ChangeValue(str);
    _changeText(str);
    return true;
}

wxString HorusCartridge::GetText() const
{
    return m_text->GetValue();
}

bool HorusCartridge::SetKeepItFlag(bool v)
{
    m_keepIt->SetValue(v);
    return true;
}

bool HorusCartridge::GetKeepItFlag()
{
    return m_keepIt->GetValue();
}

bool HorusCartridge::SetEmptyFlag(bool v)
{
    m_empty->SetValue(v);
    return true;
}

bool HorusCartridge::GetEmptyFlag()
{
    return m_empty->GetValue();
}

bool HorusCartridge::SetLoaded(bool v)
{
    return Load(v, true);
}

bool HorusCartridge::GetLoaded()
{
    return (m_state == CARTRIDGE_STATE_LOADED);
}

void HorusCartridge::SetSilent(bool silent)
{
    m_silent = silent;
}

bool HorusCartridge::IsSilent()
{
    return m_silent;
}

#if 0
void HorusCartridge::OnContextMenu(wxContextMenuEvent &event)
{
    wxMenu menu;

    menu.SetTitle(wxString::Format(wxT("Slot #%zu"), m_counter));
    menu.Append(wxNewId(), wxT("Entry 1"), wxEmptyString, wxITEM_NORMAL);
    menu.Append(wxNewId(), wxT("Entry 2"), wxEmptyString, wxITEM_NORMAL);
    menu.AppendSeparator();
    menu.Append(wxNewId(), wxT("Entry 3"), wxEmptyString, wxITEM_NORMAL);
    menu.Append(wxNewId(), wxT("Entry 4"), wxEmptyString, wxITEM_NORMAL);

    PopupMenu(&menu);
}
#endif // 0

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

#if 0
void HorusCartridge::OnToggleLoad(wxCommandEvent &event)
{
    wxLogStatus(wxT("POUET"));
    if (Load(m_loadToggle->GetValue()))
        event.Skip();
}
#endif

void HorusCartridge::OnRightDown(wxMouseEvent& event)
{
    event.LeftUp();

    // Need to invert GetValue() since the toggle button is not toggled yet because we
    // catch got Down event.
    if (! Load(! m_loadToggle->GetValue()))
        event.Skip();
}

void HorusCartridge::_changeText(const wxString &str)
{
    _setState(((str != wxEmptyString) && str.Len()) ? CARTRIDGE_STATE_OCCUPIED : CARTRIDGE_STATE_EMPTY);

    _sendEvent(HORUS_EVENT_CARTRIDGE_UPDATE);
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
            m_empty->SetValue(true);
            m_empty->Enable(true);
            m_loadToggle->Enable(false);
            break;

        case CARTRIDGE_STATE_OCCUPIED:
            m_label->SetForegroundColour(wxColour(255, 255, 255));
            m_panelLabel->SetBackgroundColour(wxColour(40, 40, 255));
            m_empty->SetValue(false);
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

bool HorusStage::Unload()
{
    if (m_cartridge)
    {
        HorusCartridge *pCartridge = m_cartridge;

        m_cartridge = NULL;

        return pCartridge->Load(false, true);
    }

    return false;
}

bool HorusStage::IsEmpty()
{
    return (m_cartridge == NULL);
}

HorusCartridge *HorusStage::GetLoadedCartridge() const
{
    return m_cartridge;
}

bool HorusStage::_loaded(HorusCartridge *cartridge)
{
    if (m_cartridge)
        return false;

    m_cartridge = cartridge;
    return true;
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

bool HorusCassette::DockCassette()
{
    return _dock(false);
}

bool HorusCassette::RedockCassette()
{
    return _dock(true);
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

bool HorusCassette::IsCassetteDocked()
{
    return m_docked;
}

bool HorusCassette::IsStageEmpty()
{
    return m_stage->IsEmpty();
}

bool HorusCassette::UnloadStage()
{
    return m_stage->Unload();
}

bool HorusCassette::CartridgeLoaded(HorusCartridge *cartridge)
{
    return m_stage->_loaded(cartridge);
}

HorusCartridge *HorusCassette::GetCartridge(size_t offset) const
{
    if (offset >= 0 && offset < MAX_CARTRIDGE_SLOTS)
        return m_cartridges[offset];

    return NULL;
}

HorusCartridge *HorusCassette::GetLoadedCartridge() const
{
    return m_stage->GetLoadedCartridge();
}

void HorusCassette::SetSilent(bool silent)
{
    for (size_t i = 0; i < MAX_CARTRIDGE_SLOTS; i++)
        m_cartridges[i]->SetSilent(silent);
}

bool HorusCassette::IsSilent(size_t offset)
{
    if (offset >= 0 && offset < MAX_CARTRIDGE_SLOTS)
        return m_cartridges[offset]->IsSilent();

    return false;
}

void HorusCassette::SetCassetteDocked(bool docked)
{
    m_docked = docked;
}

void HorusCassette::_sendEvent(HorusCassetteEvent eventID)
{
    HorusEventCassetteData *data = new HorusEventCassetteData(NULL);
    wxCommandEvent          event(wxEVT_HORUS_CASSETTE, wxID_ANY);

    event.SetInt(eventID);

    event.SetClientData((void *)data);

    wxPostEvent((wxEvtHandler *)m_parent, event);
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


}
