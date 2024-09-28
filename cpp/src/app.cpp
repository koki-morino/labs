#include "app.h"

#include "frame.h"

bool App::OnInit()
{
    // Dark theme on Windows would be added at version 3.3.0.
    // There's no way to use it so far.

    wxFrame *mainFrame = new MainFrame(APP_NAME);
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();

    return true;
}
