#pragma once

#ifndef WSOCKET_H
#define WSOCKET_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include <System/System.h>
#include <winsock.h>
#pragma comment(lib, "wsock32.lib")

/*
 *  Essentially a Windows Socket wrapper
 */
class SYSCORE_API WSocket
{
public:
    // This would be a SOCKET, however that causes the compiler
    // to not use the correct 'jump if ...' instruction, and this does!
    int m_listeningSock;
    int m_acceptedSock;

    bool checkForConnections(); // incomplete
    void close();
    bool closing();
    void connect();
    bool create(char* unused, int port);
    static void flushWrite();
    static void init();
    bool open(char* name, int port);
    u_long pending();
    void setASync(HWND hWnd, unsigned __int32 wMsg, unsigned __int32 lEvent, int sock);

    void read(void* buf, int length);
    void write(void* buf, int length);
};

#endif
