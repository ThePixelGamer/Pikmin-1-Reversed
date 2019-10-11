#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef SRT_H
#define SRT_H

#include "Vector3f.h"
#include "../Stream/RandomAccessStream.h"

class SYSCORE_API SRT {
public:
	Vector3f m_scale;
	Vector3f m_rotation;
	Vector3f m_position;

	SRT();

	void read(RandomAccessStream&);
	void write(RandomAccessStream&);
};

#endif