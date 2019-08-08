#include "Vector3f.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Vector3f class functions
//////////////////////////////////////////////////////////////////////

Vector3f::Vector3f() {  //asm matches
    this->mZ = 0;
    this->mY = 0;
    this->mX = 0;
}

Vector3f::Vector3f(const float& x, const float& y, const float& z) { //asm matches
    this->mX = x;
    this->mY = y;
    this->mZ = z;
}

Vector3f::Vector3f(const Vector3f& a2) { //asm matches
    this->mX = a2.mX;
    this->mY = a2.mY;
    this->mZ = a2.mZ;
}

void Vector3f::CP(Vector3f& a2) { //asm matches
    Vector3f tmp;
    tmp.mX = this->mY * a2.mZ - this->mZ * a2.mY;
    tmp.mY = this->mZ * a2.mX - this->mX * a2.mZ;
    tmp.mZ = this->mX * a2.mY - this->mY * a2.mX;
    this->mX = tmp.mX;
    this->mY = tmp.mY;
    this->mZ = tmp.mZ;
}

float Vector3f::DP(Vector3f& a2) { //asm matches
    return (this->mX * a2.mX) + (this->mY * a2.mY) + (this->mZ * a2.mZ);
}

void Vector3f::add(Vector3f& a2) { //asm matches
    this->mX += a2.mX;
    this->mY += a2.mY;
    this->mZ += a2.mZ;
}

void Vector3f::add(Vector3f& a2, Vector3f& a3) { //asm matches
    this->mX = a2.mX + a3.mX;
    this->mY = a2.mY + a3.mY;
    this->mZ = a2.mZ + a3.mZ;
}

void Vector3f::add(float a2, float a3, float a4) { //asm matches
    this->mX += a2;
    this->mY += a3;
    this->mZ += a4;
}

void Vector3f::add2(Vector3f& a2, Vector3f& a3) { //asm matches
    float z = a2.mZ + a3.mZ;
    float y = a2.mY + a3.mY;
    float x = a2.mX + a3.mX;
    set(x, y, z);
}

void Vector3f::bounce(Vector3f& a2, float a3) { //asm matches
    float v3 = -this->DP(a2) * a3;
    if(v3 > 0.0) {
        this->mX += v3 * a2.mX;
        this->mY += v3 * a2.mY;
        this->mZ += v3 * a2.mZ;
    }
}

void Vector3f::cross(Vector3f& a2, Vector3f& a3) { //asm matches
    float z = a2.mX * a3.mY - a2.mY * a3.mX;
    float y = a2.mZ * a3.mX - a2.mX * a3.mZ;
    float x = a2.mY * a3.mZ - a2.mZ * a3.mY;
    set(x, y, z);
}

float Vector3f::distance(Vector3f& a2) { //asm matches
    Vector3f tmp;
    tmp.sub2(a2, *this);
    return tmp.length();
}

void Vector3f::div(float a2) { //asm matches
    this->mX /= a2;
    this->mY /= a2;
    this->mZ /= a2;
}

float Vector3f::dot(Vector3f& a2) { //asm matches
    return (this->mX * a2.mX) + (this->mY * a2.mY) + (this->mZ * a2.mZ);
}

void Vector3f::genAge(AgeServer& a2, char* a3, Vector3f& a4, Vector3f& a5) {} //asm matches

void Vector3f::input(Vector3f& a2) { //asm matches
    this->set(a2.mX, a2.mY, a2.mZ);
}

float doFabs(float a2) { //asm matches (used elsewhere)
    return fabs(a2);
}

bool Vector3f::isSame(Vector3f& a2) { //asm matches
    if(doFabs(this->mX - a2.mX) < 0.000099999997f) {
        if(doFabs(this->mY - a2.mY) < 0.000099999997f) {
            if(doFabs(this->mZ - a2.mZ) < 0.000099999997f)
                return true;
        }
    }

    return false;
}

float Vector3f::length() { //asm matches
    return doFabs((this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ));
}

void Vector3f::lerpTo(Vector3f& a2, float a3, Vector3f& a4) { //asm matches
    a4.mX = (a2.mX - this->mX) * a3 + this->mX;
    a4.mY = (a2.mY - this->mY) * a3 + this->mY;
    a4.mZ = (a2.mZ - this->mZ) * a3 + this->mZ;
}

void Vector3f::middle(Vector3f& a2, Vector3f& a3) { //asm matches
    this->add2(a2, a3);
    this->scale(0.5);
}

void Vector3f::multMatrix(Matrix4f& a2) { //asm matches
    Vector3f tmp;
    tmp.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[0][1] * this->mY + a2.mMatrix4f[0][2] * this->mZ + a2.mMatrix4f[0][3];
    tmp.mY = a2.mMatrix4f[1][0] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[1][2] * this->mZ + a2.mMatrix4f[1][3];
    tmp.mZ = a2.mMatrix4f[2][0] * this->mX + a2.mMatrix4f[2][1] * this->mY + a2.mMatrix4f[2][2] * this->mZ + a2.mMatrix4f[2][3];
    *this = tmp;
}

void Vector3f::multMatrixTo(Matrix4f& a2, Vector3f& a3) { //asm matches
    a3.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[0][1] * this->mY + a2.mMatrix4f[0][2] * this->mZ + a2.mMatrix4f[0][3];
    a3.mY = a2.mMatrix4f[1][0] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[1][2] * this->mZ + a2.mMatrix4f[1][3];
    a3.mZ = a2.mMatrix4f[2][0] * this->mX + a2.mMatrix4f[2][1] * this->mY + a2.mMatrix4f[2][2] * this->mZ + a2.mMatrix4f[2][3];
}

void Vector3f::multiply(float a2) { //asm matches
    this->mX *= a2;
    this->mY *= a2;
    this->mZ *= a2;
}

void Vector3f::negate() { //asm matches
    this->mX = -this->mX;
    this->mY = -this->mY;
    this->mZ = -this->mZ;
}

float Vector3f::normalise() { //asm matches
    float v2 = this->length();
    if(v2 != 0.0f) {
        this->div(v2);
    }
    return v2;
}

void Vector3f::normalize() { //asm matches
    normalise();
}

void Vector3f::output(Vector3f& a2) { //asm matches
    a2.set(this->mX, this->mY, this->mZ);
}

void Vector3f::project(Vector3f& a2) { //asm matches
    float v3 = this->DP(a2);
    this->mX = -(v3 * a2.mX - this->mX);
    this->mY = -(v3 * a2.mY - this->mY);
    this->mZ = -(v3 * a2.mZ - this->mZ);
}

void Vector3f::read(Stream& a3) { //asm matches
    this->mX = a3.readFloat();
    this->mY = a3.readFloat();
    this->mZ = a3.readFloat();
}

void Vector3f::rotate(Matrix4f& a2) { //asm matches
    Vector3f tmp;
    tmp.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[0][1] * this->mY + a2.mMatrix4f[0][2] * this->mZ;
    tmp.mY = a2.mMatrix4f[1][0] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[1][2] * this->mZ;
    tmp.mZ = a2.mMatrix4f[2][0] * this->mX + a2.mMatrix4f[2][1] * this->mY + a2.mMatrix4f[2][2] * this->mZ;
    *this = tmp;
}

void Vector3f::rotate(Quat& a2) { //asm matches
    Quat tmp;
    tmp.mX =  a2.mY * this->mZ - a2.mZ * this->mY + a2.mW * this->mX;
    tmp.mY = -a2.mX * this->mZ + a2.mZ * this->mX + a2.mW * this->mY;
    tmp.mZ =  a2.mX * this->mY - a2.mY * this->mX + a2.mW * this->mZ;
    tmp.mW = -a2.mX * this->mX - a2.mY * this->mY - a2.mZ * this->mZ;
    this->mX =  tmp.mX * a2.mW + -a2.mZ * tmp.mY - -a2.mY * tmp.mZ + -a2.mX * tmp.mW;
    this->mY = -tmp.mX * -a2.mZ + tmp.mY * a2.mW + -a2.mX * tmp.mZ + -a2.mY * tmp.mW;
    this->mZ = -a2.mY  * tmp.mX - -a2.mX * tmp.mY + tmp.mZ * a2.mW + -a2.mZ * tmp.mW;
}

void Vector3f::rotateInverse(Quat& a2) { //asm matches
    Quat temp(-a2.mX, -a2.mY, -a2.mZ, -a2.mW);
    this->rotate(temp);
}

void Vector3f::rotateTo(Matrix4f& a2, Vector3f& a3) { //asm matches
    a3.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[0][1] * this->mY + a2.mMatrix4f[0][2] * this->mZ;
    a3.mY = a2.mMatrix4f[1][0] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[1][2] * this->mZ;
    a3.mZ = a2.mMatrix4f[2][0] * this->mX + a2.mMatrix4f[2][1] * this->mY + a2.mMatrix4f[2][2] * this->mZ;
}

void Vector3f::rotateTranspose(Matrix4f& a2) { //asm matches
    Vector3f tmp;
    tmp.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[1][0] * this->mY + a2.mMatrix4f[2][0] * this->mZ;
    tmp.mY = a2.mMatrix4f[0][1] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[2][1] * this->mZ;
    tmp.mZ = a2.mMatrix4f[0][2] * this->mX + a2.mMatrix4f[1][2] * this->mY + a2.mMatrix4f[2][2] * this->mZ;
    *this = tmp;
}

void Vector3f::scale(float a2) { //asm matches
    this->mX *= a2;
    this->mY *= a2;
    this->mZ *= a2;
}

void Vector3f::scale2(float a2, Vector3f& a3) { //asm matches
    this->mX = a3.mX * a2;
    this->mY = a3.mY * a2;
    this->mZ = a3.mZ * a2;
}

void Vector3f::set(const Vector3f& a2) { //asm matches
    this->set(a2.mX, a2.mY, a2.mZ);
}

void Vector3f::set(const float& a2, const float& a3, const float& a4) { //asm matches
    this->mX = a2;
    this->mY = a3;
    this->mZ = a4;
}

float Vector3f::squaredLength() { //asm matches
    return (this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ);
}

void Vector3f::sub(Vector3f& a2) { //asm matches
    this->mX -= a2.mX;
    this->mY -= a2.mY;
    this->mZ -= a2.mZ;
}

void Vector3f::sub(Vector3f& a2, Vector3f& a3) { //asm matches
    this->mX = a2.mX - a3.mX;
    this->mY = a2.mY - a3.mY;
    this->mZ = a2.mZ - a3.mZ;
}

void Vector3f::sub2(Vector3f& a2, Vector3f& a3) { //asm matches
    float z = a2.mZ - a3.mZ;
    float y = a2.mY - a3.mY;
    float x = a2.mX - a3.mX;
    set(x, y, z);
}

void Vector3f::write(Stream& a2) { //asm matches
    a2.writeFloat(this->mX);
    a2.writeFloat(this->mY);
    a2.writeFloat(this->mZ);
}

//////////////////////////////////////////////////////////////////////
// Quat class functions
//////////////////////////////////////////////////////////////////////

Quat::Quat() : Vector3f() {} //asm matches

Quat::Quat(float a2, float a3, float a4, float a5) : Vector3f() { //asm matches
    this->set(a2, a3, a4, a5);
}

float doSin(float a2) { //asm matches (used elsewhere)
    return sin(a2);
}

float doCos(float a2) { //asm matches (used elsewhere)
    return cos(a2);
}

void Quat::fromEuler(Vector3f& a2) { //asm matches
    float tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
    Quat tmp1, tmp2, tmp3;

    tmp4 = a2.mX;
    tmp5 = a2.mY;
    tmp6 = a2.mZ;

    tmp7 = tmp4 * 0.5f;
    tmp8 = tmp5 * 0.5f;
    tmp9 = tmp6 * 0.5f;

    tmp1.mX = doSin(tmp7);
    tmp1.mY = 0;
    tmp1.mZ = 0;
    tmp1.mW = doCos(tmp7);

    tmp2.mX = 0;
    tmp2.mY = doSin(tmp8);
    tmp2.mZ = 0;
    tmp2.mW = doCos(tmp8);

    tmp3.mX = 0;
    tmp3.mY = 0;
    tmp3.mZ = doSin(tmp9);
    tmp3.mW = doCos(tmp9);

    this->multiplyTo(tmp1, tmp2);
    this->multiplyTo(*this, tmp3);
    this->normalise();
}

float doSqrt(float a2) { //asm matches (used elsewhere)
    return sqrt(a2);
}

void Quat::fromMat3f(Matrix3f& mtx) {
    float tmp1 = (mtx.mMatrix3f[0][0] + mtx.mMatrix3f[1][1] + mtx.mMatrix3f[2][2] + 1.0f) * 0.25f;
    float tmp2 = tmp1 - (mtx.mMatrix3f[1][1] + mtx.mMatrix3f[2][2]) * 0.5f;
    float tmp3 = tmp1 - (mtx.mMatrix3f[2][2] + mtx.mMatrix3f[0][0]) * 0.5f;
    float tmp4 = tmp1 - (mtx.mMatrix3f[0][0] + mtx.mMatrix3f[1][1]) * 0.5f;

	float tmp7;
    int tmp6; 

    int wtf1; 
    int wtf2;
    int wtf3;
    int wtf4;
    int wtf5; 
    int wtf6;
    int wtf7;

    if(tmp1 > tmp2) {
        if(tmp1 > tmp3) {
            if(tmp1 > tmp4) {
                wtf1 = 0;
            }
            else {
                wtf1 = 3;
            }
            wtf2 = wtf1;
        }
        else { 
            if(tmp3 > tmp4) {
                wtf3 = 2;
            }
            else {
                wtf3 = 3;
            }
            wtf2 = wtf3;
        }
        wtf4 = wtf2;
    }
    else {
        if(tmp2 > tmp3) {
            if(tmp2 > tmp4) {
                wtf5 = 1;
            }
            else {
                wtf5 = 3;
            }
            wtf6 = wtf5;
        }
        else {
            if(tmp3 > tmp4) {
                wtf7 = 2;
            }
            else {
                wtf7 = 3;
            }
            wtf6 = wtf7;
        }
        wtf4 = wtf6;
    }
    
    tmp6 = wtf4;

    switch(tmp6) {
        case 0: {
            this->mW = doSqrt(tmp1);
            tmp7 = 0.25f / this->mW;
            this->mX = (mtx.mMatrix3f[2][1] - mtx.mMatrix3f[1][2]) * tmp7;
            this->mY = (mtx.mMatrix3f[0][2] - mtx.mMatrix3f[2][0]) * tmp7;
            this->mZ = (mtx.mMatrix3f[1][0] - mtx.mMatrix3f[0][1]) * tmp7;
        } break;

        case 1: {
            this->mX = doSqrt(tmp2);
            tmp7 = 0.25f / this->mX;
            this->mW = (mtx.mMatrix3f[2][1] - mtx.mMatrix3f[1][2]) * tmp7;
            this->mY = (mtx.mMatrix3f[0][1] + mtx.mMatrix3f[1][0]) * tmp7;
            this->mZ = (mtx.mMatrix3f[0][2] + mtx.mMatrix3f[2][0]) * tmp7;
        } break;

        case 2: {
            this->mY = doSqrt(tmp3);
            tmp7 = 0.25f / this->mY;
            this->mW = (mtx.mMatrix3f[0][2] - mtx.mMatrix3f[2][0]) * tmp7;
            this->mZ = (mtx.mMatrix3f[1][2] + mtx.mMatrix3f[2][1]) * tmp7;
            this->mX = (mtx.mMatrix3f[1][0] + mtx.mMatrix3f[0][1]) * tmp7;
        } break;

        case 3: {
            this->mZ = doSqrt(tmp4);
            tmp7 = 0.25f / this->mZ;
            this->mW = (mtx.mMatrix3f[1][0] - mtx.mMatrix3f[0][1]) * tmp7;
            this->mX = (mtx.mMatrix3f[2][0] + mtx.mMatrix3f[0][2]) * tmp7;
            this->mY = (mtx.mMatrix3f[2][1] + mtx.mMatrix3f[1][2]) * tmp7;
        } break;

        default: break;
    }

    if(this->mW < 0.0f) {
        this->mW = -this->mW;
        this->mX = -this->mX;
        this->mY = -this->mY;
        this->mZ = -this->mZ;
    }

    tmp7 = 1.0f / doSqrt(this->mW * this->mW + this->mX * this->mX + this->mY * this->mY + this->mZ * this->mZ);
    this->mW *= tmp7;
    this->mX *= tmp7;
    this->mY *= tmp7;
    this->mZ *= tmp7;
}

void Quat::genVectorX() {

}

void Quat::genVectorY() {

}

void Quat::genVectorZ() {

}

void Quat::multiply() {

}

void Quat::multiplyTo(Quat& a2, Quat& a3) {

}

void Quat::normalise() {

}

void Quat::rotate() {

}

void Quat::set(float a2, float a3, float a4, float a5) { //asm matches
  this->mX = a2;
  this->mY = a3;
  this->mZ = a4;
  this->mW = a5;
}
	
void Quat::slerp() {

}