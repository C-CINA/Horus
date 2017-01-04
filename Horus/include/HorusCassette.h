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
        HorusCartridge(HorusCassette *cassette, wxWindow *parent, size_t counter, wxWindowID id = wxID_ANY);
        ~HorusCartridge();

        void Clear();

        bool Unload();
        bool Load(bool = true, bool = false);

        size_t GetNumber()
        {
            return m_counter;
        }

        bool SetText(const wxString &str)
        {
            m_text->ChangeValue(str);
            _changeText(str);
            return true;
        }

        wxString GetText() const
        {
            return m_text->GetValue();
        }

        bool SetKeepItFlag(bool v = true)
        {
            m_keepIt->SetValue(v);
            return true;
        }

        bool GetKeepItFlag()
        {
            return m_keepIt->GetValue();
        }

        bool SetEmptyFlag(bool v)
        {
            m_empty->SetValue(v);
            return true;
        }

        bool GetEmptyFlag()
        {
            return m_empty->GetValue();
        }

        bool SetLoaded(bool v)
        {
            return Load(v, true);
        }

        bool GetLoaded()
        {
            return (m_state == CARTRIDGE_STATE_LOADED);
        }

        void SetSilent(bool silent)
        {
            m_silent = silent;
        }

        bool IsSilent()
        {
            return m_silent;
        }

    private:
        void _changeText(const wxString &);
        void OnContextMenu(wxContextMenuEvent &);
        void OnText(wxCommandEvent &);
        void OnEmpty(wxCommandEvent &);
        void OnKeepIt(wxCommandEvent &);
        void OnToggleLoad(wxCommandEvent &);

        void _setState(HorusCartridgeState);
        void _sendEvent(HorusCassetteEvent);

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

        bool Load(HorusCartridge *cartridge);

        bool Unload()
        {
            if (m_cartridge)
            {
                HorusCartridge *pCartridge = m_cartridge;

                m_cartridge = NULL;

                return pCartridge->Load(false, true);
            }

            return false;
        }

        bool IsEmpty();
        HorusCartridge *GetLoadedCartridge() const;

    private:
        bool _loaded(HorusCartridge *cartridge)
        {
            if (m_cartridge)
                return false;

            m_cartridge = cartridge;
            return true;
        }

    private:
        HorusCartridge                 *m_cartridge;
        bool                            m_keepOnStage;
};

class HorusCassette
{
    public:
        HorusCassette(wxWindow *parent, wxBoxSizer *sizer);
        ~HorusCassette();

        bool DockCassette();
        bool RedockCassette();
        bool UndockCassette();
        bool IsCassetteDocked()
        {
            return m_docked;
        }

        bool IsStageEmpty()
        {
            return m_stage->IsEmpty();
        }

        bool UnloadStage()
        {
            return m_stage->Unload();
        }

        bool CartridgeLoaded(HorusCartridge *cartridge)
        {
            return m_stage->_loaded(cartridge);
        }

        HorusCartridge *GetCartridge(size_t offset) const
        {
            if (offset >= 0 && offset < MAX_CARTRIDGE_SLOTS)
                return m_cartridges[offset];

            return NULL;
        }

        HorusCartridge *GetLoadedCartridge() const
        {
            return m_stage->GetLoadedCartridge();
        }

        void SetSilent(bool silent)
        {
            for (size_t i = 0; i < MAX_CARTRIDGE_SLOTS; i++)
                m_cartridges[i]->SetSilent(silent);
        }

        bool IsSilent(size_t offset)
        {
            if (offset >= 0 && offset < MAX_CARTRIDGE_SLOTS)
                return m_cartridges[offset]->IsSilent();

            return false;
        }

        void SetCassetteDocked(bool docked)
        {
            m_docked = docked;
        }

    private:
        void _sendEvent(HorusCassetteEvent eventID)
        {
            HorusEventCassetteData *data = new HorusEventCassetteData(NULL);
            wxCommandEvent          event(wxEVT_HORUS_CASSETTE, wxID_ANY);

            event.SetInt(eventID);

            event.SetClientData((void *)data);

            wxPostEvent((wxEvtHandler *)m_parent, event);
        }

        bool _dock(bool);

    private:
        wxWindow                       *m_parent;
        HorusCartridge                 *m_cartridges[MAX_CARTRIDGE_SLOTS];
        HorusStage                     *m_stage;
        bool                            m_docked;
};


}

#endif // HORUSCASSETTE_H
