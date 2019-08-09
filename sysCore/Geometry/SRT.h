#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef SRT_H
#define SRT_H

#include "Vector3f.h"
#include "../Stream/RandomAccessStream.h"

class SRT {
public:
	Vector3f mUnk1;
	Vector3f mUnk2;
	Vector3f mUnk3;

	SRT();
	SRT(const SRT&);

	void read(RandomAccessStream&);
	void write(RandomAccessStream&);
};

#endif