#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef RAS_H
#define RAS_H

#include "Stream.h"

class SYSCORE_API RandomAccessStream : public Stream {
public:
	// 0h - vtable
	// (Stream: 4h)

	// (Stream VTable 0 - 76)
	RandomAccessStream();
	virtual int getPending();// 80
	virtual int getPosition() { return 0; }//92
	virtual void setPosition(int) { }//88
	virtual int getLength() { return this->getAvailable(); } //84

	void padFile(unsigned __int32 toPad);
	void padFileTo(unsigned __int32 a1, unsigned __int32 a2);
	void readFrom(int arg1, void* buffer, int length);
	int readIntFrom(int position);
	void skipPadding(unsigned __int32 paddingAmount);
};

#endif