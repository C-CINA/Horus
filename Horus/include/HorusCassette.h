/// -----------------------------------------------------------------------------
///
/// \file HorusCassette.h
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

#ifndef HORUSCASSETTE_H
#define HORUSCASSETTE_H

#include "../HorusMain.h"

namespace Horus
{

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_HORUS_CASSETTE, wxNewEventType()) ///<
END_DECLARE_EVENT_TYPES()

enum HorusCartridgeState
{
    CARTRIDGE_STATE_EMPTY,
    CARTRIDGE_STATE_OCCUPIED,
    CARTRIDGE_STATE_LOADED,
    CARTRIDGE_STATE_UNLOADED,
    CARTRIDGE_STATE_UNKNOWN
};

enum HorusCassetteEvent
{
    HORUS_EVENT_CARTRIDGE_LOAD,
    HORUS_EVENT_CARTRIDGE_UNLOAD,
    HORUS_EVENT_CARTRIDGE_UPDATE,
    HORUS_EVENT_CASSETTE_DOCKED,
    HORUS_EVENT_CASSETTE_REDOCKED,
    HORUS_EVENT_CASSETTE_UNDOCKED
};


class HorusCassette; ///< Opaque
struct HorusEventCassetteData; ///< Opaque

class HorusCartridge: public wxPanel
{
    friend HorusEventCassetteData;

    public:
        HorusCartridge(HorusCassette *, wxWindow *, size_t, wxWindowID = wxID_ANY);
        ~HorusCartridge();

        bool                            Load(bool = true, bool = false);
        bool                            Unload();
        void                            Clear();


        size_t                          GetNumber();
        bool                            SetText(const wxString &);
        wxString                        GetText() const;
        bool                            SetKeepItFlag(bool = true);
        bool                            GetKeepItFlag();
        bool                            SetEmptyFlag(bool);
        bool                            GetEmptyFlag();
        bool                            SetLoaded(bool);
        bool                            GetLoaded();
        void                            SetSilent(bool);
        bool                            IsSilent();

    private:
        //void                            OnContextMenu(wxContextMenuEvent &);
        void                            OnText(wxCommandEvent &);
        void                            OnEmpty(wxCommandEvent &);
        void                            OnKeepIt(wxCommandEvent &);
        void                            OnToggleLoad(wxCommandEvent &);

        void                            _changeText(const wxString &);
        void                            _setState(HorusCartridgeState);
        void                            _sendEvent(HorusCassetteEvent);

    private:
        HorusCassette                  *m_cassette;
        wxWindow                       *m_parent;
        wxPanel                        *m_panelLabel;
        wxStaticText                   *m_label;
        wxTextCtrl                     *m_text;
        wxBitmapToggleButton           *m_loadToggle;
        wxCheckBox                     *m_keepIt;
        wxCheckBox                     *m_empty;
        size_t                          m_counter;
        HorusCartridgeState             m_state;
        HorusCartridgeState             m_stateUnloaded;
        bool                            m_silent;
};

struct HorusEventCassetteData
{
    HorusEventCassetteData(HorusCartridge *cartridge) : Cartridge(cartridge)
    {
        TimeStamp = wxDateTime::Now().GetTicks();
    }

    ~HorusEventCassetteData()
    {
    }

    time_t                              TimeStamp;
    HorusCartridge                     *Cartridge;
};


class HorusStage
{
    friend HorusCassette;

    public:
        HorusStage();
        ~HorusStage();

        bool                            Load(HorusCartridge *);
        bool                            Unload();
        bool                            IsEmpty();
        HorusCartridge                 *GetLoadedCartridge() const;

    private:
        bool                            _loaded(HorusCartridge *);

    private:
        HorusCartridge                 *m_cartridge;
        bool                            m_keepOnStage;
};

class HorusCassette
{
    public:
        HorusCassette(wxWindow *, wxBoxSizer *);
        ~HorusCassette();

        bool                            DockCassette();
        bool                            RedockCassette();
        bool                            UndockCassette();
        bool                            IsCassetteDocked();
        bool                            IsStageEmpty();
        bool                            UnloadStage();
        bool                            CartridgeLoaded(HorusCartridge *);
        HorusCartridge                 *GetCartridge(size_t) const;
        HorusCartridge                 *GetLoadedCartridge() const;
        void                            SetSilent(bool);
        bool                            IsSilent(size_t);
        void                            SetCassetteDocked(bool);

    private:
        void                            _sendEvent(HorusCassetteEvent);
        bool                            _dock(bool);

    private:
        wxWindow                       *m_parent;
        HorusCartridge                 *m_cartridges[MAX_CARTRIDGE_SLOTS];
        HorusStage                     *m_stage;
        bool                            m_docked;
};


}

#endif // HORUSCASSETTE_H
