#ifndef MY_APP_H
#define MY_APP_H

#include <wx/wx.h>

#include "defs.h"

class App : public wxApp
{
    public:
        bool OnInit() override;
};

#endif
