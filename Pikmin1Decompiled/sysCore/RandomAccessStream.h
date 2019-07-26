#pragma once
#ifndef RAS_H
#define RAS_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "Stream.h"

class SYSCORE_API RandomAccessStream : public Stream
{
public:
	void skipPadding(unsigned __int32 paddingAmount);
	RandomAccessStream();
	virtual int getPending();
	virtual int getLength() { return this->getAvailable(); }
	virtual void setPosition(int) { }
	virtual int getPosition() { return 0; } 

	void padFile(unsigned __int32 toPad);
	void padFileTo(unsigned __int32 a1, unsigned __int32 a2);
	void readFrom(int arg1, void * buffer, int length);
	int readIntFrom(int position);
};

#endif

