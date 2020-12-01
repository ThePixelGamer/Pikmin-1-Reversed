#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ATXSTREAM_H
#define ATXSTREAM_H

#include <Stream/Stream.h>

void ATXPRINT(const char* fmt, ...);

/*
 *  Part of the ATX/AGE enigma, unsure of purpose
 */
class SYSCORE_API AtxStream : public Stream
{
public:
    // 0h - vtbl
    // 4h - stream var
    class TcpStream* m_stream; // 8h
    int m_0C;              // Ch

    AtxStream() : Stream() { init(); }

    void init();
    bool open(char*, int);
    virtual void close();
    virtual void flush();
    virtual int getPending();
    virtual void read(void*, int);
    virtual void write(void*, int);
};

#endif