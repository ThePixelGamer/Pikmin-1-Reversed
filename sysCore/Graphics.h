#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Colour.h"
#include "Geometry/Matrix4f.h"
#include "Geometry/Vector2f.h"
#include "Geometry/Vector3f.h"
#include "System/System.h"
#include "Texturing/Texture.h"
#pragma comment(lib, "opengl32.lib")
#include <gl/GL.h>

#define TAU 6.2831855

static float unused[4096];  // flt_101CF090
static float unused2[4096]; // flt_101CB090

class Joint;
class Joint__MatPoly; // Joint::MatPoly
class PVWLightingInfo;
class Light;
class Camera;
class LightCamera;
class Plane;
class Material;
class MaterialHandler;
class Font;
class Shape;
class BaseShape;
class ShapeDynMaterials;
class BoundBox;

class SYSCORE_API Graphics {
public:
  static Matrix4f ident;

  // 0h vtbl
  int m_unk1; // 4h
  // Light m_lights; // 14h

  Colour m_unkColour1; // 318h
  Colour m_unkColour2; // 31Ch
  Colour m_unkColour3; // 320h

  Vector3f m_unkVec3f; // 340h

  Colour m_unkColour4; // 368h
  Colour m_unkColour5; // 36Ch
  Colour m_unkColour6; // 370h

  float m_unk2;

  Graphics();
  virtual void videoReset() {}
  virtual void setVerticalFilter(char *) {}
  virtual void getVerticalFilter(unsigned __int8 *) {}
  virtual unsigned __int8 *getDListPtr() { return nullptr; }
  virtual unsigned __int32 getDListRemainSize() { return 0; }
  virtual unsigned __int32 compileMaterial(Material *) { return 0; }
  virtual void useDList(unsigned __int32) {}

  // needs resetMatrixBuffer and resetCacheBuffer
  virtual void initRender(int, int) {}
  virtual void resetCopyFilter() = 0;
  virtual void setAmbient() {} // actually empty
  virtual void setLighting(bool, PVWLightingInfo *) = 0;
  virtual void setLight(Light *, int) = 0;
  virtual void clearBuffer(int, bool) = 0;
  virtual void setPerspective(float * [4], float, float, float, float,
                              float) = 0;
  virtual void setOrthogonal(float * [4], RectArea &) = 0;
  virtual void setLightCam(LightCamera *) {} // TODO
  virtual void setViewport(RectArea &) = 0;
  virtual void setViewportOffset(RectArea &) = 0;
  virtual void setScissor(RectArea &) = 0;
  virtual void setBlendMode(uchar, uchar,
                            uchar) = 0; // matches function signature
  virtual void setCullFront(int) = 0;
  virtual void setDepth(bool) = 0;
  virtual void setCBlending(int) = 0;
  virtual void setPointSize(float) = 0;
  virtual void setLineWidth(float) = 0;
  virtual void setCamera(Camera *) = 0;
  virtual void calcViewMatrix(Matrix4f &, Matrix4f &) = 0;
  virtual void useMatrix(Matrix4f &, int) = 0;
  virtual void setClippingPlane(bool, Plane *) = 0;
  virtual void initMesh(Shape *) = 0;
  virtual void drawSingleMatpoly(Shape *, Joint__MatPoly *) = 0;
  virtual void drawMeshes(Camera &, Shape *) = 0;
  virtual void initParticle(bool) = 0;
  virtual void drawParticle(Camera &, Vector3f &, float) = 0;
  virtual void drawRotParticle(Camera &, Vector3f &, ushort, float) = 0;
  virtual void drawCamParticle(Camera &, Vector3f &, Vector2f &, Vector2f &,
                               Vector2f &) = 0;
  virtual void drawLine(Vector3f &, Vector3f &) = 0;
  virtual void drawPoints(Vector3f *, int) = 0;
  virtual void drawOneTri(Vector3f *, Vector3f *, Vector2f *, int) = 0;
  virtual void drawOneStrip(Vector3f *, Vector3f *, Vector2f *, int) = 0;
  virtual void setColour(Colour &, bool) = 0;
  virtual void setAuxColour(Colour &) = 0;
  virtual void setPrimEnv(Colour *, Colour *) = 0;
  virtual void setClearColour(Colour &) = 0;
  virtual void setFog(bool) = 0;
  virtual void setFog(bool, Colour &, float, float, float) = 0;
  virtual void setMatHandler(MaterialHandler *) {} // TODO
  virtual void setMaterial(Material *, bool) = 0;
  virtual void useMaterial(Material *) {} // TODO
  virtual void useTexture(Texture *, int) = 0;
  virtual void drawRectangle(RectArea &, RectArea &, Vector3f *) = 0;
  virtual void fillRectangle(RectArea &) = 0;
  virtual void blatRectangle(RectArea &) = 0;
  virtual void lineRectangle(RectArea &) = 0;
  virtual void testRectangle(RectArea &) {} // actually empty
  virtual void initProjTex(bool, LightCamera *) = 0;
  virtual void initReflectTex(bool) = 0;
  virtual void texturePrintf(Font *, int, int, char *, ...) = 0;
  virtual void perspPrintf(Font *, Vector3f &, int, int, char *, ...);
  virtual void useMatrixQuick(Matrix4f &, int) = 0;
  virtual void drawOutline(Camera &, Shape *) = 0;

  void addLight(Light *); // TODO
  void cacheShape(BaseShape *, ShapeDynMaterials *);
  int calcBoxLighting(BoundBox &);
  int calcLighting(float);
  int calcSphereLighting(Vector3f &, float);
  void drawCircle(Vector3f &, float, Matrix4f &);
  void drawCylinder(Vector3f &, Vector3f &, float, Matrix4f &);
  void drawSphere(Vector3f &, float, Matrix4f &);
  void flushCachedShapes();
  void genAge(AgeServer &);
  Matrix4f *getMatrices(int);
  void resetCacheBuffer();
  void resetLights();
  void resetMatrixBuffer();
};

#endif
