#include "Plane.h"

void Plane::bounceVector(Vector3f &a1, float a2) {
  float nDP = -a1.DP(*this) * a2;
  if (nDP <= 0)
    return;
  a1.mX = nDP * this->mX + a1.mX;
  a1.mY = nDP * this->mY + a1.mY;
  a1.mZ = nDP * this->mZ + a1.mZ;
}

double Plane::calcRadScale() { return 0; }
