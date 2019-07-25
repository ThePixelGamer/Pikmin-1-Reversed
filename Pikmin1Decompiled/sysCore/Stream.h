#pragma once
#ifndef STREAM_H
#define STREAM_H
#include "String.h"
#include <cstdarg>
#include <algorithm>

class SYSCORE_API Stream
{
public:
	Stream();

	virtual int readInt();
	virtual char readByte();
	virtual short readShort();
	virtual double readFloat ();
	virtual char * readString();
	virtual void readString(String &);
	virtual void readString(char *, int);

	virtual void writeInt(int);
	virtual void writeByte(unsigned __int8);
	virtual void writeShort(short);
	virtual void writeFloat(float);
	virtual void writeString(char*);
	virtual void writeString(String&);

	virtual void read(void*, int) {}
	virtual void write(void*, int) {}

	virtual int getPending  () { return 0; }
	virtual int getAvailable() { return 0; }

	virtual void close() {} // although I would've wanted it to be a pure virtual function, there are 
	virtual bool getClosing  () { return 0; } // instances of this class on its own (errCon & sysCon), meaning that there
	virtual void flush() {} // can't be any pure virtual functions because it wouldn't have compiled otherwise.

	void print(char*, ...);
	void vPrintf(char*, char*);
};

#endif

