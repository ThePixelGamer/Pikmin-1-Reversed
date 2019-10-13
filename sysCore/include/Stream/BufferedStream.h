#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef BUFFEREDSTREAM_H
#define BUFFEREDSTREAM_H

#include <Stream/RandomAccessStream.h>
#include <sysCore.h>

class SYSCORE_API BufferedInputStream : public RandomAccessStream
{
public:
    // 4h - Stream variable + vtbl ptr
    uchar* m_buffer;        // 8h
    int m_bufferSize;       // Ch
    int m_amountToRead;     // 10h
    int m_readLimit;        // 14h
    int m_position;         // 18h
    Stream* m_bufferStream; // 1Ch

    BufferedInputStream();
    BufferedInputStream(Stream* stream, unsigned __int8* buf, int bufSize);

    virtual void read(void* buffer, int size);
    virtual int getPending();
    virtual void close();
    virtual int getPosition();

    void fillBuffer();
    void init(Stream* stream, unsigned __int8* buf, int bufSize);
    void open(Stream* stream);
    void resetBuffer();
};

class SYSCORE_API BufferedOutputStream : public Stream
{
public:
    // 4h - Stream variable + vtbl ptr
    uchar* m_buffer;        // 8h
    int m_bufferPosition;   // Ch
    int m_bufferSize;       // 10h
    Stream* m_bufferStream; // 14h
    bool m_unk;             // 18h

    BufferedOutputStream(Stream* stream, int bufferSize, bool unk);

    virtual void write(void* buffer, int size);
    virtual void flush();

    void addChar(char);
};

class SYSCORE_API BufferedStream : public RandomAccessStream
{
public:
    // 4h - Stream variable + vtbl ptr
    RandomAccessStream* m_stream;     // 8h
    BufferedInputStream m_buffStream; // 1Ch

    BufferedStream(RandomAccessStream* stream, int bufferSize);
    BufferedStream();

    // Stream
    virtual void read(void*, int);
    virtual int getPending();
    virtual void close();
    // RandomAccessStream
    virtual int getPosition();
    virtual void setPosition(int);
    virtual int getLength();

    void init(RandomAccessStream*, int);
};

#endif
