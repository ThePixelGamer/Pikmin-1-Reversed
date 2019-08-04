#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef QUAT_H
#define QUAT_H

#include "Vector3f.h"

class Vector3f;

class SYSCORE_API Quat {
public:
	Vector3f m_unk; // 0h
	int m_unk2; //Ch

	Quat();
	Quat(float, float, float, float);
};

#endif