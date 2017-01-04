/***************************************************************
 * Name:      HorusAboutApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Daniel Caujolle-Bert (daniel.caujolle-bert@unibas.ch)
 * Created:   2016-11-14
 * Copyright: Daniel Caujolle-Bert (https://c-cina.unibas.ch/bioem/)
 * License:
 **************************************************************/

#include "HorusAboutApp.h"

//(*AppHeaders
#include "HorusAboutMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(HorusAboutApp);

bool HorusAboutApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	HorusAboutDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
