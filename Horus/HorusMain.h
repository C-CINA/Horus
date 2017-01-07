/// -----------------------------------------------------------------------------
///
/// \file HorusMain.h
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

#ifndef HORUSMAIN_H
#define HORUSMAIN_H

//(*Headers(HorusFrame)
#include <wx/scrolwin.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/checkbox.h>
#include <wx/splitter.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/log.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/bmpbuttn.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/msgdlg.h>
#include <wx/bitmap.h>
#include <wx/mstream.h>
#include <wx/datetime.h>
#include <wx/tglbtn.h>
#include <wx/wxsqlite3.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/textdlg.h>
#include <wx/dynarray.h>
#include <wx/splash.h>

// Windows
#include <Uxtheme.h>
#include <windows.h>

#include "version.h"
#include "HorusApp.h"

#include "hUtils.h"

#include "HorusCassette.h"
#include "HorusDatabasePool.h"

#include "../HorusAbout/HorusAbout/HorusAboutMain.h"

namespace Horus
{

/// \brief Horus item tree ID class
///
class hTreeItemData: public wxTreeItemData
{
    public:

        /// \brief Constructor
        ///
        /// \param op const wxString& operator name
        /// \param dbFilename const wxString& database filename
        ///
        ///
        hTreeItemData(const wxString &op, const wxString &dbFilename) : wxTreeItemData(), m_operator(op), m_dbFilename(dbFilename)
        {
        }

        /// \brief Returns operator name
        ///
        /// \return wxString const
        ///
        ///
        wxString const GetOperatorName()
        {
            return m_operator;
        }

        /// \brief Returns database filename
        ///
        /// \return wxString const
        ///
        ///
        wxString const GetDatabaseFilename()
        {
            return m_dbFilename;
        }

    private:
        wxString                        m_operator; ///< Operator name
        wxString                        m_dbFilename; ///< Database filename

};

class HorusFrame: public wxFrame, HorusDatabaseEventRestore
{
    public:

        /// \brief Constructor
        ///
        /// \param parent wxWindow* parent window
        /// \param id wxWindowID window ID
        ///
        ///
        HorusFrame(wxWindow *parent, wxWindowID id = wxID_ANY);

        /// \brief Destructor
        ///
        /// \return virtual
        ///
        ///
        virtual ~HorusFrame();

    private:

        //(*Handlers(HorusFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void Onm_addOperatorClick(wxCommandEvent& event);
        void Onm_deleteOperatorClick(wxCommandEvent& event);
        void Onm_dockCassetteClick(wxCommandEvent& event);
        void Onm_unloadStageClick(wxCommandEvent& event);
        void Onm_undockCassetteClick(wxCommandEvent& event);
        void Onm_keepOnStageClick(wxCommandEvent& event);
        void Onm_wredockCassetteClick(wxCommandEvent& event);
        void OnCassettesSelectionChanged(wxTreeEvent& event);
        void OnBrowserGridResize(wxSizeEvent& event);
        void Onm_wtreeExpandAllClick(wxCommandEvent& event);
        void Onm_wtreeCollapseAllClick(wxCommandEvent& event);
        void OnSplitterWindow1SashPosChanging(wxSplitterEvent& event);
        //*)

        /// \brief Cassette event receiver
        ///
        /// \param event wxCommandEvent& cassette event
        /// \return void
        ///
        ///
        void                            OnCassetteEvent(wxCommandEvent &event);

        /// \brief Database event receiver
        ///
        /// \param event wxCommandEvent& database event
        /// \return void
        ///
        ///
        void                            OnDatabasePoolEvent(wxCommandEvent &event);

        /// \brief Callback used by database pool on startup, when restoring events
        ///
        /// \param ts time_t event timestamp
        /// \param op const wxString& event operator
        /// \param message const wxString& event text
        /// \return void
        ///
        ///
        void                            HorusEventRestore(time_t ts, const wxString &op, const wxString &message);

        /// \brief Update the operator choice list widget
        ///
        /// \return void
        ///
        ///
        void                            _updateOperatorChoice();

        /// \brief Display the formatted event in the given RichText ctrl. Could save this event into the database
        ///
        /// \param ctrl wxRichTextCtrl* destination widget
        /// \param ts time_t event timestamp
        /// \param op const wxString& event operator
        /// \param message const wxString& event text
        /// \param frozen bool freeze the RichText widget
        /// \param saveToDatabase bool save to the database
        /// \return void
        ///
        ///
        void                            _logEvent(wxRichTextCtrl *ctrl, time_t ts, const wxString &op, const wxString &message, bool frozen, bool saveToDatabase = true);

        /// \brief Cassette docking
        ///
        /// \param dock bool dock state
        /// \param redock bool redock flag
        /// \return void
        ///
        ///
        void                            _dockCassette(bool dock, bool redock = false);

        /// \brief Search for an item ID matching the text string, from parent ID
        ///
        /// \param parent wxTreeItemId parent ID
        /// \param name const wxString& text string to find
        /// \return wxTreeItemId found ID, wxTreeItemId::IsOk() == true if found.
        ///
        ///
        wxTreeItemId                    _getItemID(wxTreeItemId parent, const wxString &name);

        /// \brief Get operator name from given UUID
        ///
        /// \param uuid const wxString& UUID to search for
        /// \return wxString const operator name, wxEmptyString if not found.
        ///
        ///
        wxString const                  _getOperatorFromUUID(const wxString &uuid);

        /// \brief Add cassette entry in the right place of the tree
        ///
        /// \param ts time_t timestamp or the cassette entry
        /// \param uuid const wxString& cassette operator UUID
        /// \param dbName const wxString& cassette database filename.
        /// \return void
        ///
        ///
        void                            _addCassetteToTree(time_t ts, const wxString &uuid, const wxString &dbName);

        /// \brief Extract information from the given database, add it to the tree
        ///
        /// \param dbName const wxString& database filename
        /// \return bool true on success.
        ///
        ///
        bool                            _extractCassetteFromDatabase(const wxString &dbName);

        /// \brief Initialize the cassettes browser tab
        ///
        /// \return void
        ///
        ///
        void                            _initBrowser();

        /// \brief Display given cassette database information into browser tab
        ///
        /// \param opName const wxString& operator name
        /// \param dbName const wxString& database filename
        /// \return void
        ///
        ///
        void                            _displayCassetteInfos(const wxString &opName, const wxString &dbName);

        //(*Identifiers(HorusFrame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON3;
        static const long ID_BUTTON6;
        static const long ID_STATICTEXT3;
        static const long ID_SCROLLEDWINDOW1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_CHECKBOX1;
        static const long ID_BUTTON2;
        static const long ID_SCROLLEDWINDOW2;
        static const long ID_CHOICE1;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_RICHTEXTCTRL1;
        static const long ID_PANEL1;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_TREECTRL1;
        static const long ID_PANEL3;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_GRID1;
        static const long ID_RICHTEXTCTRL2;
        static const long ID_PANEL4;
        static const long ID_SPLITTERWINDOW1;
        static const long ID_PANEL2;
        static const long ID_AUINOTEBOOK1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        static const int MAX_SASH_POSITION; ///< Max Sash width

        //(*Declarations(HorusFrame)
        wxScrolledWindow* m_wscrolledStage;
        wxChoice* m_woperatorChoice;
        wxButton* m_wtreeExpandAll;
        wxButton* m_waddOperator;
        wxCheckBox* m_wkeepOnStage;
        wxStaticText* m_wbrowserDocked;
        wxStaticBoxSizer* m_wcassetteSizer;
        wxButton* m_wundockCassette;
        wxButton* m_wtreeCollapseAll;
        wxStaticText* m_wbrowserFuneral;
        wxStaticText* m_wcartridgeNum;
        wxButton* m_wunloadStage;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* m_wbrowserOperator;
        wxPanel* m_wbrowserPanel;
        wxButton* m_wdockCassette;
        wxScrolledWindow* m_wscrolledCartridges;
        wxPanel* m_wloggerPanel;
        wxRichTextCtrl* m_wbrowserText;
        wxGrid* m_wbrowserGrid;
        wxStatusBar* StatusBar1;
        wxAuiNotebook* AuiNotebook1;
        wxRichTextCtrl* m_wtextLogger;
        wxStaticBoxSizer* m_wstageSizer;
        wxBoxSizer* m_wslotSizer;
        wxPanel* Panel2;
        wxStaticBoxSizer* StaticBoxSizer1;
        wxButton* m_wdeleteOperator;
        wxButton* m_wredockCassette;
        wxSplitterWindow* SplitterWindow1;
        wxStaticText* m_wdockedLabel;
        wxTreeCtrl* m_wtreeCassettes;
        //*)

        HorusCassette                  *m_cassette; ///< Cassette object
        HorusDatabasePool              *m_databases; ///< Database pool object
        wxHorusArrayOperator            m_operators; ///< Operators list
        bool                            m_eventLoggerLockout; ///< lockout events from database, used on database reload.

        DECLARE_EVENT_TABLE()
};


}

#endif // HORUSMAIN_H
