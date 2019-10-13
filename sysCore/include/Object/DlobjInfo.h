#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef DLOBJINFO_H
#define DLOBJINFO_H

//
#include <Object/GfxobjInfo.h>
//

class DispList;

class SYSCORE_API DlobjInfo : public GfxobjInfo
{
public:
    //(GfxobjInfo: 0h-1Ch)
    DispList* m_displayList; // 20h

    DlobjInfo();

    virtual void attach();
    virtual void detach();
};

#endif