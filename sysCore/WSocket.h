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

class SYSCORE_API WSocket  
{
public:
	WSocket();
	virtual ~WSocket();

};

#endif
