/***************************************************************
 * Name:      HorusMain.h
 * Purpose:   Defines Application Frame
 * Author:    Daniel Caujolle-Bert (daniel.caujolle-bert@unibas.ch)
 * Created:   2016-12-16
 * Copyright: Daniel Caujolle-Bert (https://c-cina.unibas.ch/bioem/)
 * License:
 **************************************************************/

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

class hTreeItemData: public wxTreeItemData
{
    public:
        hTreeItemData(const wxString &op, const wxString &dbFilename) : wxTreeItemData(), m_operator(op), m_dbFilename(dbFilename)
        {
        }

        wxString const GetOperatorName()
        {
            return m_operator;
        }

        wxString const GetDatabaseFilename()
        {
            return m_dbFilename;
        }

    private:
        wxString                        m_operator;
        wxString                        m_dbFilename;

};

class HorusFrame: public wxFrame, HorusDatabaseEventRestore
{
    public:
        HorusFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~HorusFrame();

    private:

        //(*Handlers(HorusFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void Onm_addOperatorClick(wxCommandEvent& event);
        void Onm_deleteOperatorClick(wxCommandEvent& event);
        void Onm_operatorChoiceSelect(wxCommandEvent& event);
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

        void OnCassetteEvent(wxCommandEvent &);
        void OnDatabasePoolEvent(wxCommandEvent &);

        void HorusEventRestore(time_t, const wxString &, const wxString &);

        void _updateOperatorChoice();
        void _logEvent(wxRichTextCtrl *, time_t, const wxString &, const wxString &, bool, bool = true);
        void _dockCassette(bool, bool = false);

        wxTreeItemId _getItemID(wxTreeItemId, const wxString &);
        wxString const _getOperatorFromUUID(const wxString &);
        void _addCassetteToTree(time_t, const wxString &, const wxString &);
        bool _extractCassetteFromDatabase(const wxString &dbName);
        void _initBrowser();
        void _displayCassetteInfos(const wxString &, const wxString &);

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

        static const int MAX_SASH_POSITION;

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

        HorusCassette                  *m_cassette;
        HorusDatabasePool              *m_databases;
        wxArrayOperator                 m_operators;
        bool                            m_eventLoggerLockout;


        DECLARE_EVENT_TABLE()
};


}

#endif // HORUSMAIN_H
