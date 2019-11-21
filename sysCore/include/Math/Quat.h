#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef QUAT_H
#define QUAT_H

//
#include <Math/Vector3f.h>
//

/*
 *  Quaternion, represents orientation in 3D space
 */
class SYSCORE_API Quat : public Vector3f
{
public:
    // (Vector3f: 0h-8h)
    float mW; // Ch

    Quat();
    Quat(float, float, float, float);

    void fromEuler(Vector3f&);
    void fromMat3f(Matrix3f&);
    void genVectorX(Vector3f&);
    void genVectorY(Vector3f&);
    void genVectorZ(Vector3f&);
    void multiply(Quat&);
    void multiplyTo(Quat&, Quat&);
    void normalise();
    void rotate(Vector3f&, float);
    void set(float, float, float, float);
    void slerp(Quat&, float, int);
};

#endif