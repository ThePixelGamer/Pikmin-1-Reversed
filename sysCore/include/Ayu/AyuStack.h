#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef AYUSTACK_H
#define AYUSTACK_H

/*
 *  Used as a replacement stack, maybe to simulate the GC's own hardware limitations?
 */
class SYSCORE_API AyuStack
{
public:
    int m_allocType;       // 0h
    int m_size;            // 4h
    int m_used;            // 8h
    unsigned __int32* top; // Ch
    int m_topSize;         // 10h
    unsigned __int32* sp;  // 14h ( this + 20 ) | <- top probably???
    int m_topFree;         // 18h
    bool overflowProtect;  // 1Ch
    bool active;           // 1Dh ( this + 29 )
    char* name;            // 20h ( this + 32 )

    AyuStack();

    bool checkOverflow();
    void checkStack();
    void create(char*, int, void*, int, bool);

    int getFree();
    int getMaxFree();
    int getSize();
    int getTopUsed();
    int getUsed();

    void inactivate();

    void pop();
    unsigned __int32* push(int);

    void reset();
    void reset(int);

    int setAllocType(int);
};

#endif
