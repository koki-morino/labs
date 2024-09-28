#include "frame.h"

// A parent widget takes care of its all children.
// Do NOT manually delete the memory allocations.

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_CREATE_FILE, "&新規作成\tCtrl+N",
                     "新しいファイルを作成する");
    menuFile->Append(ID_OPEN_FILE, "&ファイルを開く\tCtrl+O", "ファイルを開く");
    menuFile->Append(ID_SAVE_FILE, "&ファイルを保存する\tCtrl+S",
                     "ファイルを保存する");
    menuFile->Append(wxID_EXIT, "&終了\tCtrl+Q", "アプリケーションを終了する");

    wxMenu *menuDatabase = new wxMenu;
    menuDatabase->Append(ID_DATABASE_CONNECTIONS, "接続情報の追加または削除",
                         "データベースの接続情報を管理する");

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(ID_LICENSES, "ライセンス", "ライセンスを表示する");
    menuHelp->Append(wxID_ABOUT, "&" APP_NAME "について",
                     APP_NAME "の情報を表示する");

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&ファイル");
    menuBar->Append(menuDatabase, "&データベース");
    menuBar->Append(menuHelp, "&ヘルプ");

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainFrame::OnCreateFile, this, ID_CREATE_FILE);
    Bind(wxEVT_MENU, &MainFrame::OnOpenFile, this, ID_OPEN_FILE);
    Bind(wxEVT_MENU, &MainFrame::OnSaveFile, this, ID_SAVE_FILE);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnDatabaseConnections, this,
         ID_DATABASE_CONNECTIONS);
    Bind(wxEVT_MENU, &MainFrame::OnLicenses, this, ID_LICENSES);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);

    wxSplitterWindow *splitter =
        new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                             wxSP_BORDER | wxSP_LIVE_UPDATE);

    wxPanel *leftPanel = new wxPanel(splitter);
    wxPanel *rightPanel = new wxPanel(splitter);

    splitter->SetMinimumPaneSize(50);
    splitter->SplitVertically(leftPanel, rightPanel);
    splitter->SetBorderSize(100);

    wxNotebook *notebook =
        new wxNotebook(rightPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxBoxSizer *notebookSizer = new wxBoxSizer(wxHORIZONTAL);
    notebookSizer->Add(notebook, 1, wxEXPAND);
    rightPanel->SetSizer(notebookSizer);

    wxPanel *tabPanel = new wxPanel(notebook);
    notebook->AddPage(tabPanel, "File-1", true, wxID_ANY);
    wxTextCtrl *textCtrl =
        new wxTextCtrl(tabPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                       wxTE_MULTILINE);
    wxBoxSizer *tabPanelSizer = new wxBoxSizer(wxVERTICAL);
    tabPanelSizer->Add(textCtrl, 1, wxEXPAND);
    tabPanel->SetSizer(tabPanelSizer);

    CreateStatusBar(3);
}
void MainFrame::OnClose(wxCloseEvent &event)
{
    event.Skip();
}
void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("バージョン：0.1.0\nライセンス：GPLv3", APP_NAME "について",
                 wxOK | wxICON_INFORMATION);
}

void MainFrame::OnCreateFile(wxCommandEvent &event) {}

void MainFrame::OnOpenFile(wxCommandEvent &event)
{
    wxFileDialog openFileDialog(this, "ファイルを開く", "", "");
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
}

void MainFrame::OnSaveFile(wxCommandEvent &event) {}

void MainFrame::OnDatabaseConnections(wxCommandEvent &event) {}

void MainFrame::OnLicenses(wxCommandEvent &event) {}
