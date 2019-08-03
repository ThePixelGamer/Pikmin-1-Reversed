#include "Vector3f.h"

Vector3f::Vector3f() {
    this->m_z = 0;
    this->m_y = 0;
    this->m_x = 0;
}

Vector3f::Vector3f(const float& x, const float& y, const float& z) {
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
}

void Vector3f::CP(Vector3f& a2) {
    Vector3f tmp;
    tmp.m_x = this->m_y * a2.m_z - this->m_z * a2.m_y;
    tmp.m_y = this->m_z * a2.m_x - this->m_x * a2.m_z;
    tmp.m_z = this->m_x * a2.m_y - this->m_y * a2.m_x;
    this->m_x = tmp.m_x;
    this->m_y = tmp.m_y;
    this->m_z = tmp.m_z;
}

float Vector3f::DP(Vector3f& a2) {
    return (this->m_x * a2.m_x) + (this->m_y * a2.m_y) + (this->m_z * a2.m_z);
}

void Vector3f::add(Vector3f& a2) {
    this->m_x += a2.m_x;
    this->m_y += a2.m_y;
    this->m_z += a2.m_z;
}

void Vector3f::add(Vector3f& a2, Vector3f& a3) {
    this->m_x = a2.m_x + a3.m_x;
    this->m_y = a2.m_y + a3.m_y;
    this->m_z = a2.m_z + a3.m_z;
}

void Vector3f::add(float a2, float a3, float a4) {
    this->m_x += a2;
    this->m_y += a3;
    this->m_z += a4;
}

void Vector3f::add2(Vector3f& a2, Vector3f& a3) {
    float z = a2.m_z + a3.m_z;
    float y = a2.m_y + a3.m_y;
    float x = a2.m_x + a3.m_x;
    set(x, y, z);
}

void Vector3f::bounce(Vector3f&, float) {

}

void Vector3f::cross(Vector3f&, Vector3f&) {

}

void Vector3f::distance(Vector3f&) {

}

void Vector3f::div(float) {

}

void Vector3f::dot(Vector3f&) {

}

void Vector3f::genAge(AgeServer&, char*, Vector3f&, Vector3f&) {

}

void Vector3f::input(Vector3f&) {

}

void Vector3f::isSame(Vector3f&) {

}

void Vector3f::length() {

}

void Vector3f::lerpTo(Vector3f&, float, Vector3f&) {

}

void Vector3f::middle(Vector3f&, Vector3f&) {

}

void Vector3f::multMatrix(Matrix4f&) {

}

void Vector3f::multMatrixTo(Matrix4f&, Vector3f&) {

}

void Vector3f::multiply(float) {

}

void Vector3f::negate() {

}

void Vector3f::normalise() {

}

void Vector3f::normalize() {

}

void Vector3f::output(Vector3f&) {

}

void Vector3f::project(Vector3f&) {

}

void Vector3f::read(Stream& a3) {
    this->m_x = a3.readFloat();
    this->m_y = a3.readFloat();
    this->m_z = a3.readFloat();
}

void Vector3f::rotate(Matrix4f&) {

}

void Vector3f::rotate(Quat&) {

}

void Vector3f::rotateInverse(Quat&) {

}

void Vector3f::rotateTo(Matrix4f&, Vector3f&) {

}

void Vector3f::rotateTranspose(Matrix4f&) {

}

void Vector3f::scale(float) {

}

void Vector3f::scale2(float, Vector3f&) {

}

void Vector3f::set(const Vector3f&) {

}

void Vector3f::set(const float& a2, const float& a3, const float& a4) {
    this->m_x = a2;
    this->m_y = a3;
    this->m_z = a4;
}

void Vector3f::squaredLength() {

}

void Vector3f::sub(Vector3f&) {

}

void Vector3f::sub(Vector3f&, Vector3f&) {

}

void Vector3f::sub2(Vector3f&, Vector3f&) {

}

void Vector3f::write(Stream&) {

}