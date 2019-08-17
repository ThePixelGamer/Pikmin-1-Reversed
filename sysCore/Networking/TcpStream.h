// WSocket.h: interface for the WSocket class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TCPSTREAM_H
#define TCPSTREAM_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "WSocket.h"

class SYSCORE_API TcpStream : public Stream
{
public:
	//0h - vtbl
	//STREAM MEMBER VAR- 4h
	WSocket* m_wSock; //8h
	int m_streamInUse; //Ch (used in System::setStreamType)

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
