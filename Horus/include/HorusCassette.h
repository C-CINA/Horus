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
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_HORUS_CASSETTE, wxNewEventType())
END_DECLARE_EVENT_TYPES()

/// \brief Cartridge state enum
///
enum HorusCartridgeState
{
    CARTRIDGE_STATE_EMPTY, ///< Cartridge is empty
    CARTRIDGE_STATE_OCCUPIED, ///< Cartridge is occupied
    CARTRIDGE_STATE_LOADED, ///< Cartrige is loaded on the stage
    CARTRIDGE_STATE_UNLOADED, ///< Cartrige has been unloaded from the stage
    CARTRIDGE_STATE_UNKNOWN ///< Cartridge unknown state
};

/// \brief Cassette event enum
///
enum HorusCassetteEvent
{
    HORUS_EVENT_CARTRIDGE_LOAD, ///< Cartridge has been loaded on stage
    HORUS_EVENT_CARTRIDGE_UNLOAD, ///< Cartridge has been unloaded from stage
    HORUS_EVENT_CARTRIDGE_UPDATE, ///< Cartridge properties has been updated
    HORUS_EVENT_CASSETTE_DOCKED, ///< Cassette has been docked
    HORUS_EVENT_CASSETTE_REDOCKED, ///< Cassette has been redocked
    HORUS_EVENT_CASSETTE_UNDOCKED ///< Cassette has been undocked
};


class HorusCassette; // Opaque
struct HorusEventCassetteData; // Opaque

/// \brief Class cartridge
///
class HorusCartridge: public wxPanel
{
    friend HorusEventCassetteData;

    public:
        /// \brief Constructor
        ///
        /// \param cassette HorusCassette* Cassette object pointer
        /// \param parent wxWindow* parent window
        /// \param counter size_t cartridge number
        /// \param id wxWindowID window ID
        ///
        ///
        HorusCartridge(HorusCassette *cassette, wxWindow *parent, size_t counter, wxWindowID id = wxID_ANY);

        /// \brief Destructor
        ///
        ///
        ///
        ~HorusCartridge();

        /// \brief Load a cartridge on stage
        ///
        /// \param load bool cartridge loading state
        /// \param force bool overriding messagebox
        /// \return bool true on success
        ///
        ///
        bool                            Load(bool load = true, bool force = false);

        /// \brief Unload the cartridge from the stage
        ///
        /// \return bool true on success
        ///
        ///
        bool                            Unload();

        /// \brief Clear cartridge text description, and reset emptiness
        ///
        /// \return void
        ///
        ///
        void                            Clear();

        /// \brief Get cartridge number
        ///
        /// \return size_t cartridge number, numberred from 1
        ///
        ///
        size_t                          GetNumber();

        /// \brief Set cartridge text description
        ///
        /// \param str const wxString& text description
        /// \return bool true on success
        ///
        ///
        bool                            SetText(const wxString &str);

        /// \brief Returns cartridge text description
        ///
        /// \return wxString text description
        ///
        ///
        wxString                        GetText() const;

        /// \brief Define keep it flag state
        ///
        /// \param v bool state
        /// \return bool true on success
        ///
        ///
        bool                            SetKeepItFlag(bool v = true);

        /// \brief Get keep it flag state
        ///
        /// \return bool flag state
        ///
        ///
        bool                            GetKeepItFlag();

        /// \brief Set cartridge emptiness state
        ///
        /// \param v bool state
        /// \return bool true on success
        ///
        ///
        bool                            SetEmptyFlag(bool v);

        /// \brief Get cartridge emptiness state
        ///
        /// \return bool state
        ///
        ///
        bool                            GetEmptyFlag();

        /// \brief Set cartridge load status
        ///
        /// \param v bool status
        /// \return bool true on success
        ///
        ///
        bool                            SetLoaded(bool v);

        /// \brief Get cartridge load status
        ///
        /// \return bool status
        ///
        ///
        bool                            GetLoaded();

        /// \brief Set cartridge silent state (as event sending POV)
        ///
        /// \param silent bool state
        /// \return void
        ///
        ///
        void                            SetSilent(bool silent);

        /// \brief Get cartridge silent state
        ///
        /// \return bool true if silent
        ///
        ///
        bool                            IsSilent();

    private:
        /// \brief Text changing event receiver
        ///
        /// \param event wxCommandEvent& event
        /// \return void
        ///
        ///
        void                            OnText(wxCommandEvent &event);

        /// \brief Empty checkbox event receiver
        ///
        /// \param event wxCommandEvent& event
        /// \return void
        ///
        ///
        void                            OnEmpty(wxCommandEvent &event);

        /// \brief KeepIt checkbox event receiver
        ///
        /// \param event wxCommandEvent& event
        /// \return void
        ///
        ///
        void                            OnKeepIt(wxCommandEvent &event);

#if 0
        /// \brief Load toggle button event receiver
        ///
        /// \param event wxCommandEvent& event
        /// \return void
        ///
        ///
        void                            OnToggleLoad(wxCommandEvent &event);
#endif // 0

        /// \brief Catch mouse right down event to reflect wxBitmapToggleButton after confirmation and not before.
        ///
        /// \param event wxMouseEvent& event
        /// \return void
        ///
        ///
        void                            OnRightDown(wxMouseEvent& event);

        /// \brief Define the busy state and send event after text is altered
        ///
        /// \param event const wxString& event
        /// \return void
        ///
        ///
        void                            _changeText(const wxString &event);

        /// \brief Update cartridge status according to the given state
        ///
        /// \param state HorusCartridgeState cartridge state to set
        /// \return void
        ///
        ///
        void                            _setState(HorusCartridgeState state);

        /// \brief Send a event to the receiver
        ///
        /// \param eventID HorusCassetteEvent event to send
        /// \return void
        ///
        ///
        void                            _sendEvent(HorusCassetteEvent eventID);

    private:
        HorusCassette                  *m_cassette; ///< Pointer to the cassette container
        wxWindow                       *m_parent; ///< Parent window
        wxPanel                        *m_panelLabel; ///< Panel containing the number text label
        wxStaticText                   *m_label; ///< Number text label
        wxTextCtrl                     *m_text; ///< Text description input
        wxBitmapToggleButton           *m_loadToggle; ///< Load toggle button
        wxCheckBox                     *m_keepIt; ///< Keep it checkbox
        wxCheckBox                     *m_empty; ///< Empty checkbox
        size_t                          m_counter; ///< Cartridge number
        HorusCartridgeState             m_state; ///< Cartridge state
        HorusCartridgeState             m_stateUnloaded; ///< Cartridge state before loading on stage
        bool                            m_silent; ///< Silent flag
};

/// \brief Structure available in cartridge events
///
struct HorusEventCassetteData
{
    HorusEventCassetteData(HorusCartridge *cartridge) : Cartridge(cartridge)
    {
        TimeStamp = wxDateTime::Now().GetTicks();
    }

    ~HorusEventCassetteData()
    {
    }

    time_t                              TimeStamp; ///< Timestamp of the event
    HorusCartridge                     *Cartridge; ///< Pointer to source cartridge
};


/// \brief Class stage
///
class HorusStage
{
    friend HorusCassette;

    public:
        /// \brief Constructor
        ///
        ///
        ///
        HorusStage();

        /// \brief Destructor
        ///
        ///
        ///
        ~HorusStage();

        /// \brief Load a cartridge on the stage
        ///
        /// \param cartridge HorusCartridge* cartridge loaded
        /// \return bool true on success
        ///
        ///
        bool                            Load(HorusCartridge *cartridge);

        /// \brief Unload the cartridge on stage
        ///
        /// \return bool true on success
        ///
        ///
        bool                            Unload();

        /// \brief Get stage emptiness status
        ///
        /// \return bool status
        ///
        ///
        bool                            IsEmpty();

        /// \brief Get loaded cartridge
        ///
        /// \return HorusCartridge* non NULL if a cartridge is loaded.
        ///
        ///
        HorusCartridge                 *GetLoadedCartridge() const;

    private:
        /// \brief Get loaded cartridge
        ///
        /// \param cartridge HorusCartridge* non NULL if a cartridge is loaded.
        /// \return bool true on success
        ///
        ///
        bool                            _loaded(HorusCartridge *cartridge);

    private:
        HorusCartridge                 *m_cartridge; ///< Loaded cartridge
        bool                            m_keepOnStage; ///< Keep on stage state
};

/// \brief Class Cassette
///
class HorusCassette
{
    public:
        /// \brief Constructor
        ///
        /// \param parent wxWindow* parent window
        /// \param sizer wxBoxSizer* sizer which contains the cartridges widgets
        ///
        ///
        HorusCassette(wxWindow *parent, wxBoxSizer *sizer);

        /// \brief Destructor
        ///
        ///
        ///
        ~HorusCassette();

        /// \brief Dock the cassette
        ///
        /// \return bool true on success
        ///
        ///
        bool                            DockCassette();

        /// \brief Redock the current cassette
        ///
        /// \return bool true on success
        ///
        ///
        bool                            RedockCassette();

        /// \brief Undock the cassette
        ///
        /// \return bool true on success
        ///
        ///
        bool                            UndockCassette();

        /// \brief Get cassette docking status
        ///
        /// \return bool true if the cassette is docked
        ///
        ///
        bool                            IsCassetteDocked();

        /// \brief Get stage state
        ///
        /// \return bool true if no cartridge is loaded
        ///
        ///
        bool                            IsStageEmpty();

        /// \brief Unload the cartridge from the stage
        ///
        /// \return bool true on success
        ///
        ///
        bool                            UnloadStage();

        /// \brief Set the loaded cartridge (used by cartridge themselves)
        ///
        /// \param cartridge HorusCartridge* cartridge to load
        /// \return bool
        ///
        ///
        bool                            CartridgeLoaded(HorusCartridge *cartridge);

        /// \brief Get cartridge at cassette offset
        ///
        /// \param offet size_t offset, starts from 0
        /// \return HorusCartridge* cartridge pointer, null if offset is out of boundaries
        ///
        ///
        HorusCartridge                 *GetCartridge(size_t offet) const;

        /// \brief Get loaded cartridge
        ///
        /// \return HorusCartridge* loaded cartridge
        ///
        ///
        HorusCartridge                 *GetLoadedCartridge() const;

        /// \brief Define cartridges silent state
        ///
        /// \param silent bool silent state
        /// \return void
        ///
        ///
        void                            SetSilent(bool silent);

        /// \brief Get given cartridge silent state
        ///
        /// \param offset size_t offset, starts from 0
        /// \return bool cartridge state, of false if offset is out of boundaries
        ///
        ///
        bool                            IsSilent(size_t offset);

        /// \brief Set cassette docked status
        ///
        /// \param docked bool docked status
        /// \return void
        ///
        ///
        void                            SetCassetteDocked(bool docked);

    private:
        /// \brief Send a cassette event to the receiver
        ///
        /// \param eventID HorusCassetteEvent event ID
        /// \return void
        ///
        ///
        void                            _sendEvent(HorusCassetteEvent eventID);

        /// \brief Dock/Redock the cassette
        ///
        /// \param redock bool true for redock
        /// \return bool true on success
        ///
        ///
        bool                            _dock(bool redock);

    private:
        wxWindow                       *m_parent; ///< Parent window
        HorusCartridge                 *m_cartridges[MAX_CARTRIDGE_SLOTS]; ///< Cartridges holder
        HorusStage                     *m_stage; ///< Stage object
        bool                            m_docked; ///< Docked status
};


}

#endif // HORUSCASSETTE_H
