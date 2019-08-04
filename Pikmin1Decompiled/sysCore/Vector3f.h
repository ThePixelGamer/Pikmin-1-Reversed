#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef VECTOR3F_H
#define VECTOR3F_H

#include "Stream/Stream.h"
#include "Matrix4f.h"

class AgeServer;
class Matrix4f;
class Quat;

class SYSCORE_API Vector3f {
public:
	float m_x; // 0h
	float m_y; // 4h
	float m_z; // 8h

	Vector3f();
	Vector3f(const float&, const float&, const float&);

	void CP(Vector3f&);
	float DP(Vector3f&);
	void add(Vector3f&);
	void add(Vector3f&, Vector3f&);
	void add(float, float, float);
	void add2(Vector3f&, Vector3f&);
	void bounce(Vector3f&, float);
	void cross(Vector3f&, Vector3f&);
	float distance(Vector3f&);
	void div(float);
	float dot(Vector3f&);
	void genAge(AgeServer&, char*, Vector3f&, Vector3f&);
	void input(Vector3f&);
	bool isSame(Vector3f&);
	float length();
	void lerpTo(Vector3f&, float, Vector3f&);
	void middle(Vector3f&, Vector3f&);
	void multMatrix(Matrix4f&);
	void multMatrixTo(Matrix4f&, Vector3f&);
	void multiply(float);
	void negate();
	float normalise();
	float normalize();
	void output(Vector3f&);
	void project(Vector3f&);
	void read(Stream&);
	void rotate(Matrix4f&);
	void rotate(Quat&);
	void rotateInverse(Quat&);
	void rotateTo(Matrix4f&, Vector3f&);
	void rotateTranspose(Matrix4f&);
	void scale(float);
	void scale2(float, Vector3f&);
	void set(const Vector3f&);
	void set(const float&, const float&, const float&);
	float squaredLength();
	void sub(Vector3f&);
	void sub(Vector3f&, Vector3f&);
	void sub2(Vector3f&, Vector3f&);
	void write(Stream&);
};

class SYSCORE_API Quat : public Vector3f {
public:
	// (Vector3f: 0h-8h)
	float m_w; //Ch

	Quat();
	Quat(float, float, float, float);

	void set(float, float, float, float);
};

#endif
