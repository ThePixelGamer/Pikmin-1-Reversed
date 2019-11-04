#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include <Stream/RandomAccessStream.h>

#ifndef VTXMATRIX_H
#define VTXMATRIX_H

// VtxMatrix, used by MOD and DMD
class SYSCORE_API VtxMatrix
{
public:
    bool m_partiallyWeighted;
    int m_index;

    void read(RandomAccessStream&);
    void write(RandomAccessStream&);
};

#endif