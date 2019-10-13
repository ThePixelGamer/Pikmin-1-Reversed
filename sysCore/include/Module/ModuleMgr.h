#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef MODULEMGR_H
#define MODULEMGR_H

//
#include <Module/Module.h>
//

class SYSCORE_API ModuleMgr
{
public:
    Module* topModule;
    int moduleCount;

    ModuleMgr();
    ~ModuleMgr();

    void* Alloc(char*);
    void UnLoad(Module*);
    Module* findModule(char*);
    void listModules();
    Module* loadModule(char*);
};

extern SYSCORE_API ModuleMgr* modMgr;

#endif