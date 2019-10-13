#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <windows.h>

class ControllerMgr
{
public:
    // 4h - vtbl pointer
    PBYTE lpKeyState;

    ControllerMgr();

    void update();

    virtual bool keyDown(int key);
};

#endif
