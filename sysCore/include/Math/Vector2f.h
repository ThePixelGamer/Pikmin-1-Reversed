#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <Stream/Stream.h>

/*
 *  2 floats in a class, used for many things like UV's, 2D positions, scaling, ect.
 */
class SYSCORE_API Vector2f
{
    float x;
    float y;

    Vector2f() {}
    Vector2f(const float&, const float&);

    void read(Stream&);
    void write(Stream&);

    void set(float, float);
};

#endif