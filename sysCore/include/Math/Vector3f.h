#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <math.h>

#include <Math/Matrix3f.h>
#include <Math/Matrix4f.h>
#include <Stream/Stream.h>

class AgeServer;
class Quat;
class Matrix4f;

/*
 *  Contains 3 floats, used for a LOT more things than Vector2f, e.g.: Vertex positions, positions, scale, ect.
 */
class SYSCORE_API Vector3f
{
public:
    float mX; // 0h
    float mY; // 4h
    float mZ; // 8h

    Vector3f();
    Vector3f(const float&, const float&, const float&);
    Vector3f(const Vector3f&);

    void CP(Vector3f&);  // cross product
    float DP(Vector3f&); // dot product
    void add(Vector3f&);
    void add(Vector3f&, Vector3f&);
    void add(float, float, float);
    void add2(Vector3f&, Vector3f&);
    void bounce(Vector3f&, float);
    void cross(Vector3f&, Vector3f&);
    float distance(Vector3f&);
    void div(float);
    float dot(Vector3f&);
    void genAge(AgeServer&, char* name, Vector3f& scaleUpperBounds, Vector3f& scaleLowerBounds);
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
    void normalize();
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

#endif
