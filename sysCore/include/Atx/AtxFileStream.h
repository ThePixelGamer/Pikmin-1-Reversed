#pragma once

#ifndef ATXFILESTREAM_H
#define ATXFILESTREAM_H

#include <Atx/AtxStream.h>
#include <Stream/RandomAccessStream.h>

class SYSCORE_API AtxFileStream : public RandomAccessStream
{
public:
    int position;     // 8h
    int length;       // Ch
    AtxStream stream; // 10h

    AtxFileStream() {}

    bool open(char*, unsigned __int32);
    void close();
    virtual int getLength();
    virtual int getPending();
    virtual int getPosition();

    virtual void read(void*, int);
    virtual void write(void*, int);

    virtual void setPosition(int);
    virtual void setLength(int);
};

#endif