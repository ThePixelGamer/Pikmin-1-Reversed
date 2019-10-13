#include "BoundBox.h"
#include "Graphics.h"

BoundBox::BoundBox() { this->resetBound(); }

BoundBox::BoundBox(Vector3f &min, Vector3f &max) {
  this->m_minBounds = min;
  this->m_maxBounds = max;
}

void BoundBox::read(RandomAccessStream &stream) {
  this->m_maxBounds.read(stream);
  this->m_minBounds.read(stream);
}

void BoundBox::write(RandomAccessStream &stream) {
  this->m_maxBounds.write(stream);
  this->m_minBounds.write(stream);
}

void BoundBox::expandBound(BoundBox &expandBy) {
  if (expandBy.m_maxBounds.mX < this->m_maxBounds.mX)
    this->m_maxBounds.mX = expandBy.m_maxBounds.mX;
  if (expandBy.m_maxBounds.mY < this->m_maxBounds.mY)
    this->m_maxBounds.mY = expandBy.m_maxBounds.mY;
  if (expandBy.m_maxBounds.mZ < this->m_maxBounds.mZ)
    this->m_maxBounds.mZ = expandBy.m_maxBounds.mZ;
  if (expandBy.m_minBounds.mX > this->m_minBounds.mX)
    this->m_minBounds.mX = expandBy.m_minBounds.mX;
  if (expandBy.m_minBounds.mY > this->m_minBounds.mY)
    this->m_minBounds.mY = expandBy.m_minBounds.mY;
  if (expandBy.m_minBounds.mZ > this->m_minBounds.mZ)
    this->m_minBounds.mZ = expandBy.m_minBounds.mZ;
}

void BoundBox::expandBound(Vector3f &expandBy) {
  if (expandBy.mX < this->m_maxBounds.mX)
    this->m_maxBounds.mX = expandBy.mX;
  if (expandBy.mY < this->m_maxBounds.mY)
    this->m_maxBounds.mY = expandBy.mY;
  if (expandBy.mZ < this->m_maxBounds.mZ)
    this->m_maxBounds.mZ = expandBy.mZ;
  if (expandBy.mX > this->m_minBounds.mX)
    this->m_minBounds.mX = expandBy.mX;
  if (expandBy.mY > this->m_minBounds.mY)
    this->m_minBounds.mY = expandBy.mY;
  if (expandBy.mZ > this->m_minBounds.mZ)
    this->m_minBounds.mZ = expandBy.mZ;
}

void BoundBox::draw(Graphics &gfx) {
  /* max min min min min min
  gfx.drawLine(Vector3f(this->m_maxBounds.mX, this->m_minBounds.mY,
  this->m_minBounds.mZ), Vector3f(this->m_minBounds.mX, this->m_minBounds.mY,
  this->m_minBounds.mZ));
  // max min max max min min
  gfx.drawLine(Vector3f(this->m_maxBounds.mX, this->m_minBounds.mY,
  this->m_maxBounds.mZ), Vector3f(this->m_maxBounds.mX, this->m_minBounds.mY,
  this->m_minBounds.mZ));
  // min min max max min max
  gfx.drawLine(Vector3f(this->m_minBounds.mX, this->m_minBounds.mY,
  this->m_maxBounds.mZ), Vector3f(this->m_maxBounds.mX, this->m_minBounds.mY,
  this->m_maxBounds.mZ));
  // min min min min min max
  gfx.drawLine(Vector3f(this->m_minBounds.mX, this->m_minBounds.mY,
  this->m_minBounds.mZ), Vector3f(this->m_minBounds.mX, this->m_minBounds.mY,
  this->m_maxBounds.mZ));
  // max max min min max min
  gfx.drawLine(Vector3f(this->m_maxBounds.mX, this->m_minBounds.mY,
  this->m_minBounds.mZ), Vector3f(this->m_minBounds.mX, this->m_minBounds.mY,
  this->m_minBounds.mZ));
  // min max max max max max
  gfx.drawLine(Vector3f(this->m_maxBounds.mX, this->m_minBounds.mY,
  this->m_maxBounds.mZ), Vector3f(this->m_maxBounds.mX, this->m_minBounds.mY,
  this->m_minBounds.mZ));
  // min min max max min max
  gfx.drawLine(Vector3f(this->m_minBounds.mX, this->m_minBounds.mY,
  this->m_maxBounds.mZ), Vector3f(this->m_maxBounds.mX, this->m_minBounds.mY,
  this->m_maxBounds.mZ));
  // min min min min min max
  gfx.drawLine(Vector3f(this->m_minBounds.mX, this->m_minBounds.mY,
  this->m_minBounds.mZ), Vector3f(this->m_minBounds.mX, this->m_minBounds.mY,
  this->m_maxBounds.mZ));*/

  // TODO
}

bool BoundBox::intersects(BoundBox &check) {
  return check.m_minBounds.mX <= this->m_maxBounds.mX &&
         check.m_maxBounds.mX >= this->m_minBounds.mX &&
         check.m_minBounds.mY <= this->m_maxBounds.mY &&
         check.m_maxBounds.mY >= this->m_minBounds.mY &&
         check.m_minBounds.mZ <= this->m_maxBounds.mZ &&
         check.m_maxBounds.mZ >= this->m_minBounds.mZ;
}

void BoundBox::resetBound() {
  this->m_maxBounds.set(32768.0f, 32768.0f, 32768.0f);
  this->m_minBounds.set(-32768.0f, -32768.0f, -32768.0f);
}
