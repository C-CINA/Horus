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
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/checkbox.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
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
#include <wx/filename.h>
#include <wx/textdlg.h>
#include <wx/dynarray.h>

// Windows
#include <Uxtheme.h>
#include <windows.h>

#include "version.h"
#include "HorusApp.h"

#include "hUtils.h"

#include "HorusCassette.h"
#include "HorusDatabasePool.h"

namespace Horus
{

class HorusFrame: public wxFrame, public HorusEventLoggerCallbackInterface
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
        //*)

        void OnCassetteEvent(wxCommandEvent &);
        void _updateOperatorChoice();
        void _logEvent(time_t, const wxString &, const wxString &);
        void _dockCassette(bool, bool = false);

        void cbiCallbackFunction(time_t ts, const wxString &op, const wxString &msg)
        {
            _logEvent(ts, op, msg);
        }

        //(*Identifiers(HorusFrame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON6;
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
        static const long ID_AUINOTEBOOK1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(HorusFrame)
        wxStaticBoxSizer* m_cassetteSizer;
        wxCheckBox* m_keepOnStage;
        wxButton* m_unloadStage;
        wxBoxSizer* m_slotSizer;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxScrolledWindow* m_scrolledStage;
        wxButton* m_addOperator;
        wxButton* m_deleteOperator;
        wxStatusBar* StatusBar1;
        wxRichTextCtrl* m_textLogger;
        wxStaticText* m_cartridgeNum;
        wxScrolledWindow* m_scrolledCartridges;
        wxChoice* m_operatorChoice;
        wxAuiNotebook* AuiNotebook1;
        wxButton* m_dockCassette;
        wxButton* m_undockCassette;
        wxStaticBoxSizer* m_stageSizer;
        //*)

        HorusCassette                  *m_cassette;
        HorusDatabasePool              *m_databases;
        wxArrayOperator                 m_operators;
        bool                            m_eventLockout;


        DECLARE_EVENT_TABLE()
};


}

#endif // HORUSMAIN_H
