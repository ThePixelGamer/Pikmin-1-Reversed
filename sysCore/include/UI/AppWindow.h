#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef APPWINDOW_H
#define APPWINDOW_H

//
#include <UI/UIWindow.h>
//

class SYSCORE_API AppWindow : public UIWindow
{
public:
    AppWindow(UIWindow * parent, int unk1, int dwStyle, int dwExStyle, bool unk2) :
        UIWindow(parent, unk1, dwStyle, dwExStyle, unk2){}
    ~AppWindow();

    virtual int processMessage(HWND, unsigned int, WPARAM, long);
};

#endif