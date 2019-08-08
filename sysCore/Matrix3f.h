#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef MATRIX3F_H
#define MATRIX3F_H

#include "Vector3f.h"

class Vector3f;

class Matrix3f {
public:
	float mMatrix3f[3][3];

	Matrix3f();

};

#endif