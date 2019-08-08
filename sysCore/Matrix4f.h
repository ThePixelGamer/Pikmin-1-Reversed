#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef MATRIX4F_H
#define MATRIX4F_H

#include "Vector3f.h"

class Vector3f;

class SYSCORE_API Matrix4f {
public:
	float mMatrix4f[4][4];

	Matrix4f(float[4][4]);
	Matrix4f();

	void blend(Matrix4f&, float);
	void getColumn(int, Vector3f&);
	void getRow(int, Vector3f&);
};

#endif 