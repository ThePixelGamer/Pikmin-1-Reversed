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
  enum mode; // unknown
  enum do_not_initialize;

  float mMatrix3f[3][3];

protected:
  Matrix3f(do_not_initialize);

public:
  Matrix3f(mode);
  Matrix3f(const Vector3f &, mode);
  Matrix3f(float[3][3]);
  Matrix3f();
};

#endif
