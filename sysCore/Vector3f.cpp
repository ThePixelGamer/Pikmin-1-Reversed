#include "Vector3f.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Vector3f class functions
//////////////////////////////////////////////////////////////////////

Vector3f::Vector3f() {  //asm matches
    this->m_z = 0;
    this->m_y = 0;
    this->m_x = 0;
}

Vector3f::Vector3f(const float& x, const float& y, const float& z) { //asm matches
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
}

Vector3f::Vector3f(const Vector3f& a2) { //asm matches
    this->m_x = a2.m_x;
    this->m_y = a2.m_y;
    this->m_z = a2.m_z;
}

void Vector3f::CP(Vector3f& a2) { //asm matches
    Vector3f tmp;
    tmp.m_x = this->m_y * a2.m_z - this->m_z * a2.m_y;
    tmp.m_y = this->m_z * a2.m_x - this->m_x * a2.m_z;
    tmp.m_z = this->m_x * a2.m_y - this->m_y * a2.m_x;
    this->m_x = tmp.m_x;
    this->m_y = tmp.m_y;
    this->m_z = tmp.m_z;
}

float Vector3f::DP(Vector3f& a2) { //asm matches
    return (this->m_x * a2.m_x) + (this->m_y * a2.m_y) + (this->m_z * a2.m_z);
}

void Vector3f::add(Vector3f& a2) { //asm matches
    this->m_x += a2.m_x;
    this->m_y += a2.m_y;
    this->m_z += a2.m_z;
}

void Vector3f::add(Vector3f& a2, Vector3f& a3) { //asm matches
    this->m_x = a2.m_x + a3.m_x;
    this->m_y = a2.m_y + a3.m_y;
    this->m_z = a2.m_z + a3.m_z;
}

void Vector3f::add(float a2, float a3, float a4) { //asm matches
    this->m_x += a2;
    this->m_y += a3;
    this->m_z += a4;
}

void Vector3f::add2(Vector3f& a2, Vector3f& a3) { //asm matches
    float z = a2.m_z + a3.m_z;
    float y = a2.m_y + a3.m_y;
    float x = a2.m_x + a3.m_x;
    set(x, y, z);
}

void Vector3f::bounce(Vector3f& a2, float a3) { //asm matches
    float v3 = -Vector3f::DP(a2) * a3;
    if(v3 > 0.0) {
        this->m_x += v3 * a2.m_x;
        this->m_y += v3 * a2.m_y;
        this->m_z += v3 * a2.m_z;
    }
}

void Vector3f::cross(Vector3f& a2, Vector3f& a3) { //asm matches
    float z = a2.m_x * a3.m_y - a2.m_y * a3.m_x;
    float y = a2.m_z * a3.m_x - a2.m_x * a3.m_z;
    float x = a2.m_y * a3.m_z - a2.m_z * a3.m_y;
    set(x, y, z);
}

float Vector3f::distance(Vector3f& a2) { //asm matches
    Vector3f tmp;
    tmp.sub2(a2, *this);
    return tmp.length();
}

void Vector3f::div(float a2) { //asm matches
    this->m_x /= a2;
    this->m_y /= a2;
    this->m_z /= a2;
}

float Vector3f::dot(Vector3f& a2) { //asm matches
    return (this->m_x * a2.m_x) + (this->m_y * a2.m_y) + (this->m_z * a2.m_z);
}

void Vector3f::genAge(AgeServer& a2, char* a3, Vector3f& a4, Vector3f& a5) {} //asm matches

void Vector3f::input(Vector3f& a2) { //asm matches
    this->set(a2.m_x, a2.m_y, a2.m_z);
}

float doFabs(float a2) { //asm matches (used elsewhere)
    return fabs(a2);
}

bool Vector3f::isSame(Vector3f& a2) { //asm matches
    if(doFabs(this->m_x - a2.m_x) < 0.000099999997f) {
        if(doFabs(this->m_y - a2.m_y) < 0.000099999997f) {
            if(doFabs(this->m_z - a2.m_z) < 0.000099999997f)
                return true;
        }
    }

    return false;
}

float Vector3f::length() {
    float v2 = (this->m_x * this->m_x) + (this->m_y * this->m_y) + (this->m_z * this->m_z);
    return fabs(v2);
}

void Vector3f::lerpTo(Vector3f& a2, float a3, Vector3f& a4) {
    a4.m_x = a2.m_x - this->m_x * a3 + this->m_x;
    a4.m_y = a2.m_y - this->m_y * a3 + this->m_y;
    a4.m_z = a2.m_z - this->m_z * a3 + this->m_z;
}

void Vector3f::middle(Vector3f& a2, Vector3f& a3) {
    this->add2(a2, a3);
    this->scale(0.5);
}

void Vector3f::multMatrix(Matrix4f& a2) {
    Vector3f tmp;
    tmp.m_x = a2.m_matrix[0][0] * this->m_x + a2.m_matrix[0][1] * this->m_y + a2.m_matrix[0][2] * this->m_z + a2.m_matrix[0][3];
    tmp.m_y = a2.m_matrix[1][0] * this->m_x + a2.m_matrix[1][1] * this->m_y + a2.m_matrix[1][2] * this->m_z + a2.m_matrix[1][3];
    tmp.m_z = a2.m_matrix[2][0] * this->m_x + a2.m_matrix[2][1] * this->m_y + a2.m_matrix[2][2] * this->m_z + a2.m_matrix[2][3];
    this->m_x = tmp.m_x;
    this->m_y = tmp.m_y;
    this->m_z = tmp.m_z;
}

void Vector3f::multMatrixTo(Matrix4f& a2, Vector3f& a3) {
    a3.m_x = a2.m_matrix[0][0] * this->m_x + a2.m_matrix[0][1] * this->m_y + a2.m_matrix[0][2] * this->m_z + a2.m_matrix[0][3];
    a3.m_y = a2.m_matrix[1][0] * this->m_x + a2.m_matrix[1][1] * this->m_y + a2.m_matrix[1][2] * this->m_z + a2.m_matrix[1][3];
    a3.m_z = a2.m_matrix[2][0] * this->m_x + a2.m_matrix[2][1] * this->m_y + a2.m_matrix[2][2] * this->m_z + a2.m_matrix[2][3];
}

void Vector3f::multiply(float a2) {
    this->m_x *= a2;
    this->m_y *= a2;
    this->m_z *= a2;
}

void Vector3f::negate() {
    this->m_x = -this->m_x;
    this->m_y = -this->m_y;
    this->m_z = -this->m_z;
}

float Vector3f::normalise() {
    float v2 = this->length();
    if(v2 != 0.0) {
        this->div(v2);
    }
    return v2;
}

float Vector3f::normalize() {
    return normalise();
}

void Vector3f::output(Vector3f& a2) {
    a2.set(this->m_x, this->m_y, this->m_z);
}

void Vector3f::project(Vector3f& a2) {
    float v3 = this->DP(a2);
    this->m_x = -(v3 * a2.m_x - this->m_x);
    this->m_y = -(v3 * a2.m_y - this->m_y);
    this->m_z = -(v3 * a2.m_z - this->m_z);
}

void Vector3f::read(Stream& a3) {
    this->m_x = a3.readFloat();
    this->m_y = a3.readFloat();
    this->m_z = a3.readFloat();
}

void Vector3f::rotate(Matrix4f& a2) {
    Vector3f tmp;
    tmp.m_x = a2.m_matrix[0][0] * this->m_x + a2.m_matrix[0][1] * this->m_y + a2.m_matrix[0][2] * this->m_z;
    tmp.m_y = a2.m_matrix[1][0] * this->m_x + a2.m_matrix[1][1] * this->m_y + a2.m_matrix[1][2] * this->m_z;
    tmp.m_z = a2.m_matrix[2][0] * this->m_x + a2.m_matrix[2][1] * this->m_y + a2.m_matrix[2][2] * this->m_z;
    this->m_x = tmp.m_x;
    this->m_y = tmp.m_y;
    this->m_z = tmp.m_z;
}

void Vector3f::rotate(Quat& a2) { //plz end me if this doesn't produce the right output
    Quat tmp;
    tmp.m_x =  a2.m_y * this->m_z - a2.m_z * this->m_y + a2.m_w * this->m_x;
    tmp.m_y = -a2.m_x * this->m_z + a2.m_z * this->m_x + a2.m_w * this->m_y;
    tmp.m_z =  a2.m_x * this->m_y - a2.m_y * this->m_x + a2.m_w * this->m_z;
    tmp.m_w = -a2.m_x * this->m_x - a2.m_y * this->m_y - a2.m_z * this->m_z;
    this->m_x =  tmp.m_x * a2.m_w + -a2.m_z * tmp.m_y - -a2.m_y * tmp.m_z + -a2.m_x * tmp.m_w;
    this->m_y = -tmp.m_x * -a2.m_z + tmp.m_y * a2.m_w + -a2.m_x * tmp.m_z + -a2.m_y * tmp.m_w;
    this->m_z = -a2.m_y  * tmp.m_x - -a2.m_x * tmp.m_y + tmp.m_z * a2.m_w + -a2.m_z * tmp.m_w;
}

void Vector3f::rotateInverse(Quat& a2) {
    Quat temp(-a2.m_x, -a2.m_y, -a2.m_z, -a2.m_w);
    this->rotate(temp);
}

void Vector3f::rotateTo(Matrix4f& a2, Vector3f& a3) {
    a3.m_x = a2.m_matrix[0][0] * this->m_x + a2.m_matrix[0][1] * this->m_y + a2.m_matrix[0][2] * this->m_z;
    a3.m_y = a2.m_matrix[1][0] * this->m_x + a2.m_matrix[1][1] * this->m_y + a2.m_matrix[1][2] * this->m_z;
    a3.m_z = a2.m_matrix[2][0] * this->m_x + a2.m_matrix[2][1] * this->m_y + a2.m_matrix[2][2] * this->m_z;
}

void Vector3f::rotateTranspose(Matrix4f& a2) {
    Vector3f tmp;
    tmp.m_x = a2.m_matrix[0][0] * this->m_x + a2.m_matrix[1][0] * this->m_y + a2.m_matrix[2][0] * this->m_z;
    tmp.m_y = a2.m_matrix[0][1] * this->m_x + a2.m_matrix[1][1] * this->m_y + a2.m_matrix[2][1] * this->m_z;
    tmp.m_z = a2.m_matrix[0][2] * this->m_x + a2.m_matrix[1][2] * this->m_y + a2.m_matrix[2][2] * this->m_z;
    this->m_x = tmp.m_x;
    this->m_y = tmp.m_y;
    this->m_z = tmp.m_z;
}

void Vector3f::scale(float a2) {
    this->m_x *= a2;
    this->m_y *= a2;
    this->m_z *= a2;
}

void Vector3f::scale2(float a2, Vector3f& a3) {
    this->m_x = a3.m_x * a2;
    this->m_y = a3.m_y * a2;
    this->m_z = a3.m_z * a2;
}

void Vector3f::set(const Vector3f& a2) {
    this->set(a2.m_x, a2.m_y, a2.m_z);
}

void Vector3f::set(const float& a2, const float& a3, const float& a4) {
    this->m_x = a2;
    this->m_y = a3;
    this->m_z = a4;
}

float Vector3f::squaredLength() {
    return (this->m_x * this->m_x) + (this->m_y * this->m_y) + (this->m_z * this->m_z);
}

void Vector3f::sub(Vector3f& a2) {
    this->m_x -= a2.m_x;
    this->m_y -= a2.m_y;
    this->m_z -= a2.m_z;
}

void Vector3f::sub(Vector3f& a2, Vector3f& a3) {
    this->m_x = a2.m_x - a3.m_x;
    this->m_y = a2.m_y - a3.m_y;
    this->m_z = a2.m_z - a3.m_z;
}

void Vector3f::sub2(Vector3f& a2, Vector3f& a3) {
    float z = a2.m_z - a3.m_z;
    float y = a2.m_y - a3.m_y;
    float x = a2.m_x - a3.m_x;
    set(x, y, z);
}

void Vector3f::write(Stream& a2) {
    a2.writeFloat(this->m_x);
    a2.writeFloat(this->m_y);
    a2.writeFloat(this->m_z);
}

//////////////////////////////////////////////////////////////////////
// Quat class functions
//////////////////////////////////////////////////////////////////////

Quat::Quat() : Vector3f() {} //done

Quat::Quat(float a2, float a3, float a4, float a5) : Vector3f() { //done
    this->set(a2, a3, a4, a5);
}

void Quat::set(float a2, float a3, float a4, float a5) { //done
  this->m_x = a2;
  this->m_y = a3;
  this->m_z = a4;
  this->m_w = a5;
}