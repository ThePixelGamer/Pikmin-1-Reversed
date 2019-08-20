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
	virtual int readInt(); // 0h
	virtual unsigned __int8 readByte(); // 4h
	virtual short readShort(); // 8h
	virtual float readFloat(); // Ch
	virtual void readString(char*, int); // 10h
	virtual void readString(String&); // 14h
	virtual char* readString(); // 18h

	//Writing functions
	virtual void writeInt(int); // 1Ch
	virtual void writeByte(unsigned __int8); // 20h
	virtual void writeShort(short); // 24h
	virtual void writeFloat(float); // 28h
	virtual void writeString(char*); // 2Ch
	virtual void writeString(String&); // 30h

	// Core read/write functions
	virtual void read(void*, int) {} // 34h
	virtual void write(void*, int) {} // 38h

	// 'Getter' functions
	virtual int getPending() { return 0; } // 3Ch
	virtual int getAvailable() { return 0; } // 40h

	// Misc. functions (gets overloaded)
	virtual void close() {} // 44h
	virtual bool getClosing() { return 0; } // 48h
	virtual void flush() {} // 4Ch

	// Printing functions
	void print(char*, ...);
	void vPrintf(char*, char*);
};

#endif