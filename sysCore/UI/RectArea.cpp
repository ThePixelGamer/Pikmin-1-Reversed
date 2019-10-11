#include "RectArea.h"

RectArea::RectArea() {
  this->x1 = 0;
  this->y1 = 0;
  this->x2 = 0;
  this->y2 = 0;
}

RectArea::RectArea(int x_1, int y_1, int x_2, int y_2) {
  this->x1 = x_1;
  this->y1 = y_1;
  this->x2 = x_2;
  this->y2 = y_2;
}

int RectArea::height() { return this->y2 - this->y1; }
int RectArea::width() { return this->x2 - this->x1; }
bool RectArea::pointInside(int x, int y) {
  return x > this->x1 && x < this->x2 && y > this->y1 && y < this->y2;
}

void RectArea::set(int x_1, int y_1, int x_2, int y_2) {
  this->x1 = x_1;
  this->y1 = y_1;
  this->x2 = x_2;
  this->y2 = y_2;
}