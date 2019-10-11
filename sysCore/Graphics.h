#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Colour.h"
#include "Geometry/Matrix4f.h"
#include "System/System.h"
#pragma comment(lib, "opengl32.lib")
#include <gl/GL.h>

#define TAU 6.2831855

static float unused[4096];  // flt_101CF090
static float unused2[4096]; // flt_101CB090

class SYSCORE_API Graphics {
public:
  // 0h vtbl
  int m_unk1; // 4h

  Vector3f m_unkVec3f; // 340h
  Colour m_unkColour1; // 368h
  Colour m_unkColour2; // 36Ch
  Colour m_unkColour3; // 370h

  Graphics();
  virtual void videoReset();
  virtual void setVerticalFilter(char *);
  virtual void getVerticalFilter(unsigned __int8 *);
  virtual unsigned __int8 *getDListPtr();
  virtual unsigned __int32 getDListRemainSize();
};

#endif
