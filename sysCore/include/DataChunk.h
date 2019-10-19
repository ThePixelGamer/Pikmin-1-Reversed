#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef DATACHUNK_H
#define DATACHUNK_H

class RandomAccessStream;
class CmdStream;

class SYSCORE_API DataChunk
{
public:
    int m_dataIndex; // _0
    int m_dataSize;  // _4
    float* m_data;   // _8

    DataChunk();

    void addData(float toAdd);
    void getData(CmdStream* stream);
    void read(RandomAccessStream& stream);
    void write(RandomAccessStream& stream);
    void setDataSize(int dataSize);
};

#endif
