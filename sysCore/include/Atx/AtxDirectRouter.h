#pragma once

#ifndef ATXDIRECTROUTER_H
#define ATXDIRECTROUTER_H

#include "AtxRouter.h"

class SYSCORE_API AtxDirectRouter : public AtxRouter
{
public:
    // 0h - vtable
    char* m_hostname;                 // 4h
    int m_dword8;                     // 8h
    char m_byteC;                     // Ch
    bool m_connected;                 // Dh
    class TcpStream* m_networkStream; // 10h

    AtxDirectRouter(char*);

    virtual bool openRoute(AtxStream*, int);                 // ASM MATCHES
    virtual void closeRoute(AtxStream*) {}                   // empty
    virtual void lock() {}                                   // empty
    virtual void unlock() {}                                 // empty
    virtual void closeAll() {}                               // empty
    virtual void reset() {}                                  // empty
    virtual bool isConnected() { return this->m_connected; } // ASM MATCHES
    virtual void setWindow(unsigned __int32);                // ASM MATCHES
};

#endif