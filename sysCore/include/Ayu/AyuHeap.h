#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef AYUHEAP_H
#define AYUHEAP_H

#include <Ayu/AyuStack.h>

class SYSCORE_API AyuHeap : public AyuStack
{
public:
    //(AyuStack: 0h-20h)
    int unk; // 24h

    void init(char*, int, void*, int);
};

#endif
