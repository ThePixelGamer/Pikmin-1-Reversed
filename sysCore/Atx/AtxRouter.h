#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef AGEATX_H
#define AGEATX_H

#include "AtxStream.h"

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

#endif