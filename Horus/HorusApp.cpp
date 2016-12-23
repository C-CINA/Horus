/***************************************************************
 * Name:      HorusApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Daniel Caujolle-Bert (daniel.caujolle-bert@unibas.ch)
 * Created:   2016-12-16
 * Copyright: Daniel Caujolle-Bert (https://c-cina.unibas.ch/bioem/)
 * License:
 **************************************************************/

#include "HorusApp.h"

//(*AppHeaders
#include "HorusMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(HorusApp);
DECLARE_APP(HorusApp);

using namespace Horus;

bool HorusApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	HorusFrame* Frame = new HorusFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
