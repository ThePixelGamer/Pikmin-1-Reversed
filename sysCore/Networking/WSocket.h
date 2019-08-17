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

#include "../sysCore.h"
#include <Wsock32.h>
#pragma comment(lib, "winsock.lib")

class SYSCORE_API WSocket  
{
public:
	SOCKET m_listeningSock;
	SOCKET m_acceptedSock;

	bool checkForConnections();
	void close();
	bool closing();
	void flushWrite();
	void init();
	bool open(char* name, int port);
	unsigned long pending();
	void setASync(HWND hWnd, unsigned __int32 wMsg, unsigned __int32 lEvent, int sock);

	void read(char* buf, int length);
	void write(void* buf, int length);	
};

#endif
