#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <windows.h>

class SYSCORE_API ControllerMgr
{
public:
    // 4h - vtbl pointer
    BYTE lpKeyState[0x100];

    ControllerMgr();

    void update();
    void updateController(class Controller*);

    virtual bool keyDown(int key);
};

#endif
