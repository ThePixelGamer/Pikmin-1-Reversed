// WSocket.h: interface for the WSocket class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WSOCKET_H
#define WSOCKET_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "../System/System.h"
#include <winsock.h>
#pragma comment(lib, "wsock32.lib")

class SYSCORE_API WSocket  
{
public:
	SOCKET m_listeningSock;
	SOCKET m_acceptedSock;

	bool checkForConnections(); // incomplete
	void close();
	bool closing();
	void connect();
	bool create(char* unused, int port); // if statement compiles wrong
	static void flushWrite();
	static void init();
	bool open(char* name, int port);
	unsigned long pending();
	void setASync(HWND hWnd, unsigned __int32 wMsg, unsigned __int32 lEvent, int sock); // if statement compiles wrong

	void read(void* buf, int length);
	void write(void* buf, int length);
};

#endif
