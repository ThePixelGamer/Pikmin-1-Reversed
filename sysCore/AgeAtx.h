#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef AGEATX_H
#define AGEATX_H

#include "Stream/Stream.h"

class SYSCORE_API AtxRouter {
public:
	virtual bool openRoute(class AtxStream*, int) = 0;
	virtual void closeRoute(class AtxStream*) = 0;
	virtual void lock() {}
	virtual void unlock() {}
	virtual void closeAll() {}
	virtual void reset() = 0;
	virtual bool isConnected() { return false; }
	virtual void setWindow(unsigned __int32) {}
};

class SYSCORE_API AtxStream : public Stream {
public:
	//0h - vtbl
	//4h - stream var
	int m_dword8; //8h = what fucking class is this>? it inherits stream!
	int m_dwordC; //Ch

	AtxStream() : Stream() { this->init(); }

	void init();
	bool open(char*, int);

	void close() {}
};

class SYSCORE_API AtxDirectRouter : public AtxRouter {
public:
	//0h - vtable
	char* m_dword4; //4h
	int m_dword8; //8h
	char m_byteC; //Ch
	bool m_connected; //Dh
	class TcpStream* m_networkStream; //10h

	AtxDirectRouter(char*);

	virtual bool openRoute(AtxStream*, int) { return false; } // to do
	virtual void closeRoute(AtxStream*) {}
	virtual void lock() {}
	virtual void unlock() {}
	virtual void closeAll() {}
	virtual void reset() {}
	virtual bool isConnected() { return this->m_connected; }
	virtual void setWindow(unsigned __int32) {}
};

#endif