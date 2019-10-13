#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ANIMOBJINFO_H
#define ANIMOBJINFO_H

#include <Object/GfxobjInfo.h>

class AnimData;

class SYSCORE_API AnmobjInfo : public GfxobjInfo
{
public:
    //(GfxobjInfo: 0h-1Ch)
    AnimData* animData;

    AnmobjInfo();

    virtual void detach();
};

#endif