/***************************************************************
 * Name:      HorusApp.h
 * Purpose:   Defines Application Class
 * Author:    Daniel Caujolle-Bert (daniel.caujolle-bert@unibas.ch)
 * Created:   2016-12-16
 * Copyright: Daniel Caujolle-Bert (https://c-cina.unibas.ch/bioem/)
 * License:
 **************************************************************/

#ifndef HORUSAPP_H
#define HORUSAPP_H

#include <wx/app.h>

namespace Horus
{
    class HorusFrame;
}


class HorusApp : public wxApp
{
    public:
        virtual bool OnInit();
};

DECLARE_APP(HorusApp)

#endif // HORUSAPP_H
