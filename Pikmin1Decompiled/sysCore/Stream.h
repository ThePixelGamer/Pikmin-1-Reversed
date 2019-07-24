#pragma once
#ifndef STREAM_H
#define STREAM_H
#include "String.h"
#include <cstdarg>
#include <algorithm>

class Stream
{
public:
	Stream();
	~Stream();

	virtual void close() {} // although I would've wanted it to be a pure virtual function, there are 
	virtual void flush() {} // instances of this class on its own (errCon & sysCon), meaning that there
	virtual int getAvailable() { return 0; } // can't be any pure virtual functions because it wouldn't have compiled otherwise.
	virtual bool getClosing  () { return 0; }
	virtual int getPending  () { return 0; }
	virtual void read(void*, int) {}
	virtual void write(void*, int) {}

	void print(char*, ...);
	void vPrintf(char*, char*);

	virtual int readInt();
	virtual char readByte();
	virtual short readShort();
	virtual double readFloat ();
	virtual char * readString();
	virtual void readString(String &);
	virtual void readString(char *, int);

	virtual void writeInt(int);
	virtual void writeByte(unsigned __int8);
	virtual void writeShort(__int16);
	virtual void writeFloat(float);
	virtual void writeString(String&);
	virtual void writeString(char*);
};

#endif

