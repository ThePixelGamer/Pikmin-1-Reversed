#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "../Stream/RandomAccessStream.h"

#ifndef VTXMATRIX_H
#define VTXMATRIX_H

// VtxMatrix, used by MOD and DMD
class SYSCORE_API VtxMatrix {
public:
	bool m_partiallyWeighted; // 1 byte
	char PADDING[3]; // 3 bytes (4 bytes)
	short m_index; // 2 bytes (6 bytes)
	short PADDING_2; // 2 bytes (8 bytes), aligned perfectly!

	void read(RandomAccessStream&);
	void write(RandomAccessStream&);
};

#endif