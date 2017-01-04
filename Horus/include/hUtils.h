#ifndef HUTILS_H
#define HUTILS_H

#include "../HorusMain.h"


/// \brief Class Operator
///
class Operator
{
    public:
        Operator() : Name(wxEmptyString), UUID(wxEmptyString)
        {
        }

        Operator(const wxString &name, const wxString &uuid) : Name(name), UUID(uuid)
        {
        }

        ~Operator()
        {
        }

        wxString Name;
        wxString UUID;
};

/// \brief Declaration of Operator dynamic array
///
WX_DECLARE_OBJARRAY(Operator, wxArrayOperator);

class hUtils
{
    public:
        hUtils();
        virtual ~hUtils();

        static bool                     LoadDataFromResource(char * &, DWORD &, const wxString  &);
        static wxBitmap*                GetBitmapFromMemory(const char *, const DWORD);
        static wxBitmap*                CreateBitmapFromPNGResource(const wxString &);

        static wxString const           CreateGUID(int = 32);

        static wxString const           GetTimeStampString(wxDateTime, bool);
        static wxString const           GetTimeStampString(time_t, bool);

        static wxCMPFUNC_CONV           CompareOperators(Operator **l, Operator **h);


    protected:

    private:
};

#endif // HUTILS_H
