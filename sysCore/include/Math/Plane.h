#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef PLANE_H
#define PLANE_H

//
#include <Math/Vector3f.h>
//

/*
 *  A standard 3D plane (space plane;)
 */
class SYSCORE_API Plane : public Vector3f
{ // TODO
public:
    float mD;

    Plane() {}

    void bounceVector(Vector3f&, float);
    double calcRadScale(); // TODO,
};

#endif
