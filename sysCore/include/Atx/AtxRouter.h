#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef AGEATX_H
#define AGEATX_H

#include <Atx/AtxStream.h>

/*
 *  Part of the ATX/AGE enigma, unsure of purpose
 */
class SYSCORE_API AtxRouter
{
public:
    virtual bool openRoute(class AtxStream*, int) = 0; // 0
    virtual void closeRoute(class AtxStream*) = 0;     // 4
    virtual void lock() {}                             // 8
    virtual void unlock() {}                           // 12
    virtual void closeAll() {}                         // 16
    virtual void reset() = 0;                          // 20
    virtual bool isConnected() { return false; }       // 24
    virtual void setWindow(unsigned __int32) {}        // 28
};

#endif