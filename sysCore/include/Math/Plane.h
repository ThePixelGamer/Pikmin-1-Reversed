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

class SYSCORE_API Plane : public Vector3f
{ // TODO
public:
    float m_unk2;

    Plane() {}

    void bounceVector(Vector3f&, float);
    double calcRadScale(); // TODO
};

#endif
