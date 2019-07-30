// AgeAtx.h: interface for the AgeAtx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGEATX_H__B57A4C0A_B5BC_44EF_A6A7_8560E9FB8277__INCLUDED_)
#define AFX_AGEATX_H__B57A4C0A_B5BC_44EF_A6A7_8560E9FB8277__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream.h"

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

class SYSCORE_API AtxRouter
{
public:
	virtual bool openRoute (class AtxStream *, int) = 0;
	virtual void closeRoute(class AtxStream *) = 0;
	virtual void lock() {}
	virtual void unlock() {}
	virtual void closeAll() {}
	virtual void reset() = 0;
	virtual bool isConnected() { return false; }
	virtual void setWindow(unsigned __int32) {}
};

class SYSCORE_API AtxStream
	: public Stream
{
public:
	int dword8;
	int dwordC;

	AtxStream() { this->init(); } 

	void init() {}
};

class SYSCORE_API AtxDirectRouter
	: public AtxRouter
{
public:
	int dword4;
	int dword8;
	char byteC;
	bool isconnected;
	struct TcpStream * networkStream;


	virtual bool openRoute (AtxStream *, int) {return false;} // to do
	virtual void closeRoute(AtxStream *) {}
	virtual void lock() {}
	virtual void unlock() {}
	virtual void closeAll() {}
	virtual void reset() {}
	virtual bool isConnected() { return this->isconnected; }
	virtual void setWindow(unsigned __int32) {}	
};

#endif // !defined(AFX_AGEATX_H__B57A4C0A_B5BC_44EF_A6A7_8560E9FB8277__INCLUDED_)
