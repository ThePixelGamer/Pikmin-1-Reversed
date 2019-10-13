#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <Object/GfxobjInfo.h>

class Texture;

class SYSCORE_API TexobjInfo : public GfxobjInfo
{
public:
    //(GfxobjInfo: 0h-1Ch)
    Texture* texData;

    TexobjInfo();

    virtual void detach();
};

#endif