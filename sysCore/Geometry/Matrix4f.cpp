#include "Matrix4f.h"

Matrix4f::Matrix4f(float a2[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      this->mMatrix4f[i][j] = a2[i][j];
    }
  }
}

Matrix4f::Matrix4f() {}

void Matrix4f::blend(Matrix4f &a2, float a3) { // pseudocode fine, asm not
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j)
      this->mMatrix4f[i][j] =
          (a2.mMatrix4f[i][j] - this->mMatrieex4f[i][j]) * a3 +
          this->mMatrix4f[i][j];
  }
}

void Matrix4f::getColumn(int a2, Vector3f &a3) {
  a3.set(mMatrix4f[a2][0], mMatrix4f[a2][1], mMatrix4f[a2][2]);
}

void Matrix4f::getRow(int a2, Vector3f &a3) {
  a3.set(mMatrix4f[a2][0], mMatrix4f[a2 + 1][0], mMatrix4f[a2 + 2][0]);
}

void Matrix4f::makeIdentity() {
  // 1 0 0 0
  // 0 1 0 0
  // 0 0 1 0
  // 0 0 0 1
  // initialises matrix to above ^
  // 1st column
  this->mMatrix4f[0][0] = 1.0f;
  this->mMatrix4f[0][1] = 0.0f;
  this->mMatrix4f[0][2] = 0.0f;
  this->mMatrix4f[0][3] = 0.0f;
  // 2nd column
  this->mMatrix4f[1][0] = 0.0f;
  this->mMatrix4f[1][1] = 1.0f;
  this->mMatrix4f[1][2] = 0.0f;
  this->mMatrix4f[1][3] = 0.0f;
  // 3rd column
  this->mMatrix4f[2][0] = 0.0f;
  this->mMatrix4f[2][1] = 0.0f;
  this->mMatrix4f[2][2] = 1.0f;
  this->mMatrix4f[2][3] = 0.0f;
  // 4th column
  this->mMatrix4f[3][0] = 0.0f;
  this->mMatrix4f[3][1] = 0.0f;
  this->mMatrix4f[3][2] = 0.0f;
  this->mMatrix4f[3][3] = 1.0f;
}

void Matrix4f::multiply(Matrix4f &multBy) {
  Matrix4f temporary;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      temporary.mMatrix4f[x][y] = 0;
      for (int i = 0; i < 4; i++) {
        temporary.mMatrix4f[x][y] =
            this->mMatrix4f[x][i] * multBy.mMatrix4f[i][y] +
            temporary.mMatrix4f[x][y];
      }
    }
  }
  // actually used, generates a qmemcpy() call in the C pseudocode
  *this = temporary;
}
