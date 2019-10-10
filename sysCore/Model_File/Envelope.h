#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "../Stream/RandomAccessStream.h"

#ifndef ENVELOPE_H
#define ENVELOPE_H

// Skinning Envelope, used by MOD and DMD
class SYSCORE_API Envelope {
public:
	int m_indicesCount;
	int* m_indices;
	float* m_weights;

	Envelope();
	void read(RandomAccessStream&);
	void write(RandomAccessStream&);
};

#endif