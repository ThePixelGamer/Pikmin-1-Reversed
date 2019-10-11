#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef SRTNODE_H
#define SRTNODE_H

//
#include "../Geometry/Matrix4f.h"
#include "../Geometry/SRT.h"
#include "Node.h"
//

class SYSCORE_API SRTNode : public Node {
public:
  // vtable 0h
  //(CoreNode: 4h-10h)
  //(Node: 14h-1Ch)
  Matrix4f m_mat4f; // 20h
  SRT m_srt;        // 60h

  SRTNode(char * = "<SRTNode>");

  //(CoreNode: 0 - 16)
  virtual void update();              // this+20
  virtual void concat();              // this+44
  virtual void concat(Matrix4f &);    // this+32
  virtual Matrix4f *getModelMatrix(); // this+48

  void genAge(AgeServer &);
  Vector3f *getPosition();
  Vector3f *getRotation();
  Vector3f *getScale();
  Vector3f *getWorldPosition();
  void setPosition(Vector3f &);
  void setRotation(Vector3f &);
  void setScale(Vector3f &);
};

#endif