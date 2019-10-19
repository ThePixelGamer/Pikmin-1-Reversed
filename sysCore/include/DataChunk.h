#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef DATACHUNK_H
#define DATACHUNK_H

//
//	Add any headers here!
//

class SYSCORE_API DataChunk
{
public:
    int m_dataIndex; // _0
    int m_dataSize;  // _4
    float* m_data;   // _8

    DataChunk();

    void addData(float toAdd);
    void getData(class CmdStream* stream);
    void read(class RandomAccessStream& stream);
    void write(class RandomAccessStream& stream);
    void setDataSize(int dataSize);
};

#endif
