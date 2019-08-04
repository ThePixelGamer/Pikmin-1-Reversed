#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef MATRIX4F_H
#define MATRIX4F_H

class Matrix4f {
public:
	float m_matrix[4][4];

	Matrix4f(float[4][4]);
	Matrix4f();

};

#endif 