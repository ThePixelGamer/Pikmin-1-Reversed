#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef STREAM_H
#define STREAM_H

#include "../String.h"
#include <cstdarg>
#include <algorithm>

class SYSCORE_API Stream {
public:
	// 0h - vtable
	char* currentWorkingDir; // 4h

	Stream();

	// Reading functions
	virtual int readInt();
	virtual char readByte();
	virtual short readShort();
	virtual float readFloat();
	virtual char* readString();
	virtual void readString(String&);
	virtual void readString(char*, int);

	//Writing functions
	virtual void writeInt(int);
	virtual void writeByte(unsigned __int8);
	virtual void writeShort(short);
	virtual void writeFloat(float);
	virtual void writeString(char*);
	virtual void writeString(String&);

	// Core read/write functions
	virtual void read(void*, int) {}
	virtual void write(void*, int) {}

	// 'Getter' functions
	virtual int getPending() { return 0; }
	virtual int getAvailable() { return 0; }

	// Misc. functions (gets overloaded)
	virtual void close() {}
	virtual bool getClosing() { return 0; }
	virtual void flush() {}

	// Printing functions
	void print(char*, ...);
	void vPrintf(char*, char*);
};

#endif