#pragma once

#ifndef TCPSTREAM_H
#define TCPSTREAM_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include <Networking/WSocket.h>

/*
 * Simple TCP stream, basically a WSocket wrapper
 */
class SYSCORE_API TcpStream : public Stream
{
public:
    // 0h - vtbl
    // Stream member variable - 4h
    WSocket* m_wSock;  // 8h
    int m_streamInUse; // Ch (used in System::setStreamType)

    TcpStream();
    TcpStream(WSocket*);

    virtual void read(void*, int);
    virtual void write(void*, int);
    virtual int getPending();
    virtual int getAvailable();
    virtual void close();
    virtual void flush();
    virtual bool closing();

    bool connect(char* name, int port);
};

#endif
