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
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/choice.h>
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

class HorusFrame: public wxFrame
{
    public:

        HorusFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~HorusFrame();

    private:

        //(*Handlers(HorusFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void Onm_addOperatorClick(wxCommandEvent& event);
        void Onm_deleteOperatorClick(wxCommandEvent& event);
        void Onm_operatorChoiceSelect(wxCommandEvent& event);
        //*)

        void OnCassetteEvent(wxCommandEvent &);
        void _updateOperatorChoice();


        //(*Identifiers(HorusFrame)
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_CHOICE1;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL1;
        static const long ID_AUINOTEBOOK1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(HorusFrame)
        wxTextCtrl* m_textLogger;
        wxButton* Button1;
        wxButton* m_unloadStage;
        wxBoxSizer* m_slotSizer;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxButton* m_addOperator;
        wxButton* m_deleteOperator;
        wxButton* Button3;
        wxStatusBar* StatusBar1;
        wxStaticText* m_cartridgeNum;
        wxChoice* m_operatorChoice;
        wxAuiNotebook* AuiNotebook1;
        //*)

        HorusCassette                  *m_cassette;
        HorusDatabasePool              *m_databases;
        //bool                            m_eventLock;
        wxArrayOperator                 m_operators;


        DECLARE_EVENT_TABLE()
};


}

#endif // HORUSMAIN_H
