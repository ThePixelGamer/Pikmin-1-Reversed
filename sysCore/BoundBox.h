#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef BOUNDBOX_H
#define BOUNDBOX_H

//
#include "Geometry/Vector3f.h"
#include "Stream/RandomAccessStream.h"
//

class Graphics;

class SYSCORE_API BoundBox {
public:
  Vector3f m_maxBounds;
  Vector3f m_minBounds;

  BoundBox();
  BoundBox(Vector3f &, Vector3f &);

  void read(RandomAccessStream &);
  void write(RandomAccessStream &);

  void expandBound(BoundBox &);
  void expandBound(Vector3f &);

  void draw(Graphics &); //< TODO
  bool intersects(BoundBox &);
  void resetBound();
};

#endif
