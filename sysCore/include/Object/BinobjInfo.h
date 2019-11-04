#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef BINOBJINFO_H
#define BINOBJINFO_H

//
#include <Object/GfxobjInfo.h>
//

class SYSCORE_API BinobjInfo : public GfxobjInfo
{
public:
    BinobjInfo();

    char* m_data;
};

#endif