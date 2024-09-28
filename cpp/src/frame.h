#ifndef MY_FRAME_H
#define MY_FRAME_H

#include <wx/filedlg.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/wx.h>

#include "defs.h"

enum
{
    ID_CREATE_FILE = 1,
    ID_OPEN_FILE = 2,
    ID_SAVE_FILE = 3,
    ID_DATABASE_CONNECTIONS = 4,
    ID_LICENSES = 5,
};

class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString &title);

    private:
        /**
         * This should be executed right before terminating an application.
         */
        void OnClose(wxCloseEvent &event);
        void OnExit(wxCommandEvent &event);
        void OnCreateFile(wxCommandEvent &event);
        void OnOpenFile(wxCommandEvent &event);
        void OnSaveFile(wxCommandEvent &event);
        void OnDatabaseConnections(wxCommandEvent &event);
        void OnLicenses(wxCommandEvent &event);
        void OnAbout(wxCommandEvent &event);
};

#endif
