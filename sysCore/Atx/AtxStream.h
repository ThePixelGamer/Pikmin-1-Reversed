#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ATXSTREAM_H
#define ATXSTREAM_H

#include "../Stream/Stream.h"

void ATXPRINT(const char* fmt, ...);

class SYSCORE_API AtxStream : public Stream {
public:
	//0h - vtbl
	//4h - stream var
	class TcpStream* m_stream; //8h
	int m_dwordC; //Ch

	AtxStream() : Stream() { this->init(); }

	void init();
	bool open(char*, int);

	void close() {}
};

#endif