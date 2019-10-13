#include <Math/Vector3f.h>

#include <Math/Quat.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Vector3f class functions
//////////////////////////////////////////////////////////////////////

Vector3f::Vector3f()
{ // asm matches
    this->mZ = 0;
    this->mY = 0;
    this->mX = 0;
}

Vector3f::Vector3f(const float& x, const float& y, const float& z)
{ // asm matches
    this->mX = x;
    this->mY = y;
    this->mZ = z;
}

Vector3f::Vector3f(const Vector3f& a2)
{ // asm matches
    this->mX = a2.mX;
    this->mY = a2.mY;
    this->mZ = a2.mZ;
}

void Vector3f::CP(Vector3f& a2)
{ // asm matches
    Vector3f tmp;
    tmp.mX = this->mY * a2.mZ - this->mZ * a2.mY;
    tmp.mY = this->mZ * a2.mX - this->mX * a2.mZ;
    tmp.mZ = this->mX * a2.mY - this->mY * a2.mX;
    this->mX = tmp.mX;
    this->mY = tmp.mY;
    this->mZ = tmp.mZ;
}

float Vector3f::DP(Vector3f& a2)
{ // asm matches
    return (this->mX * a2.mX) + (this->mY * a2.mY) + (this->mZ * a2.mZ);
}

void Vector3f::add(Vector3f& a2)
{ // asm matches
    this->mX += a2.mX;
    this->mY += a2.mY;
    this->mZ += a2.mZ;
}

void Vector3f::add(Vector3f& a2, Vector3f& a3)
{ // asm matches
    this->mX = a2.mX + a3.mX;
    this->mY = a2.mY + a3.mY;
    this->mZ = a2.mZ + a3.mZ;
}

void Vector3f::add(float a2, float a3, float a4)
{ // asm matches
    this->mX += a2;
    this->mY += a3;
    this->mZ += a4;
}

void Vector3f::add2(Vector3f& a2, Vector3f& a3)
{ // asm matches
    float z = a2.mZ + a3.mZ;
    float y = a2.mY + a3.mY;
    float x = a2.mX + a3.mX;
    set(x, y, z);
}

void Vector3f::bounce(Vector3f& a2, float a3)
{ // asm matches
    float v3 = -this->DP(a2) * a3;
    if (v3 > 0.0)
    {
        this->mX += v3 * a2.mX;
        this->mY += v3 * a2.mY;
        this->mZ += v3 * a2.mZ;
    }
}

void Vector3f::cross(Vector3f& a2, Vector3f& a3)
{ // asm matches
    float z = a2.mX * a3.mY - a2.mY * a3.mX;
    float y = a2.mZ * a3.mX - a2.mX * a3.mZ;
    float x = a2.mY * a3.mZ - a2.mZ * a3.mY;
    set(x, y, z);
}

float Vector3f::distance(Vector3f& a2)
{ // asm matches
    Vector3f tmp;
    tmp.sub2(a2, *this);
    return tmp.length();
}

void Vector3f::div(float a2)
{ // asm matches
    this->mX /= a2;
    this->mY /= a2;
    this->mZ /= a2;
}

float Vector3f::dot(Vector3f& a2)
{ // asm matches
    return (this->mX * a2.mX) + (this->mY * a2.mY) + (this->mZ * a2.mZ);
}

void Vector3f::genAge(AgeServer& a2, char* a3, Vector3f& a4, Vector3f& a5) {} // asm matches

void Vector3f::input(Vector3f& a2)
{ // asm matches
    this->set(a2.mX, a2.mY, a2.mZ);
}

float doFabs(float a2)
{ // asm matches (used elsewhere)
    return fabs(a2);
}

bool Vector3f::isSame(Vector3f& a2)
{ // asm matches
    if (doFabs(this->mX - a2.mX) < 0.000099999997f)
    {
        if (doFabs(this->mY - a2.mY) < 0.000099999997f)
        {
            if (doFabs(this->mZ - a2.mZ) < 0.000099999997f)
                return true;
        }
    }

    return false;
}

float Vector3f::length()
{ // asm matches
    return doFabs((this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ));
}

void Vector3f::lerpTo(Vector3f& a2, float a3, Vector3f& a4)
{ // asm matches
    a4.mX = (a2.mX - this->mX) * a3 + this->mX;
    a4.mY = (a2.mY - this->mY) * a3 + this->mY;
    a4.mZ = (a2.mZ - this->mZ) * a3 + this->mZ;
}

void Vector3f::middle(Vector3f& a2, Vector3f& a3)
{ // asm matches
    this->add2(a2, a3);
    this->scale(0.5);
}

void Vector3f::multMatrix(Matrix4f& a2)
{ // asm matches
    Vector3f tmp;
    tmp.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[0][1] * this->mY + a2.mMatrix4f[0][2] * this->mZ +
             a2.mMatrix4f[0][3];
    tmp.mY = a2.mMatrix4f[1][0] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[1][2] * this->mZ +
             a2.mMatrix4f[1][3];
    tmp.mZ = a2.mMatrix4f[2][0] * this->mX + a2.mMatrix4f[2][1] * this->mY + a2.mMatrix4f[2][2] * this->mZ +
             a2.mMatrix4f[2][3];
    *this = tmp;
}

void Vector3f::multMatrixTo(Matrix4f& a2, Vector3f& a3)
{ // asm matches
    a3.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[0][1] * this->mY + a2.mMatrix4f[0][2] * this->mZ +
            a2.mMatrix4f[0][3];
    a3.mY = a2.mMatrix4f[1][0] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[1][2] * this->mZ +
            a2.mMatrix4f[1][3];
    a3.mZ = a2.mMatrix4f[2][0] * this->mX + a2.mMatrix4f[2][1] * this->mY + a2.mMatrix4f[2][2] * this->mZ +
            a2.mMatrix4f[2][3];
}

void Vector3f::multiply(float a2)
{ // asm matches
    this->mX *= a2;
    this->mY *= a2;
    this->mZ *= a2;
}

void Vector3f::negate()
{ // asm matches
    this->mX = -this->mX;
    this->mY = -this->mY;
    this->mZ = -this->mZ;
}

float Vector3f::normalise()
{ // asm matches
    float v2 = this->length();
    if (v2 != 0.0f)
    {
        this->div(v2);
    }
    return v2;
}

void Vector3f::normalize()
{ // asm matches
    normalise();
}

void Vector3f::output(Vector3f& a2)
{ // asm matches
    a2.set(this->mX, this->mY, this->mZ);
}

void Vector3f::project(Vector3f& a2)
{ // asm matches
    float v3 = this->DP(a2);
    this->mX = -(v3 * a2.mX - this->mX);
    this->mY = -(v3 * a2.mY - this->mY);
    this->mZ = -(v3 * a2.mZ - this->mZ);
}

void Vector3f::read(Stream& a3)
{ // asm matches
    this->mX = a3.readFloat();
    this->mY = a3.readFloat();
    this->mZ = a3.readFloat();
}

void Vector3f::rotate(Matrix4f& a2)
{ // asm matches
    Vector3f tmp;
    tmp.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[0][1] * this->mY + a2.mMatrix4f[0][2] * this->mZ;
    tmp.mY = a2.mMatrix4f[1][0] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[1][2] * this->mZ;
    tmp.mZ = a2.mMatrix4f[2][0] * this->mX + a2.mMatrix4f[2][1] * this->mY + a2.mMatrix4f[2][2] * this->mZ;
    *this = tmp;
}

void Vector3f::rotate(Quat& a2)
{ // asm matches
    Quat tmp;
    tmp.mX = a2.mY * this->mZ - a2.mZ * this->mY + a2.mW * this->mX;
    tmp.mY = -a2.mX * this->mZ + a2.mZ * this->mX + a2.mW * this->mY;
    tmp.mZ = a2.mX * this->mY - a2.mY * this->mX + a2.mW * this->mZ;
    tmp.mW = -a2.mX * this->mX - a2.mY * this->mY - a2.mZ * this->mZ;
    this->mX = tmp.mX * a2.mW + -a2.mZ * tmp.mY - -a2.mY * tmp.mZ + -a2.mX * tmp.mW;
    this->mY = -tmp.mX * -a2.mZ + tmp.mY * a2.mW + -a2.mX * tmp.mZ + -a2.mY * tmp.mW;
    this->mZ = -a2.mY * tmp.mX - -a2.mX * tmp.mY + tmp.mZ * a2.mW + -a2.mZ * tmp.mW;
}

void Vector3f::rotateInverse(Quat& a2)
{ // asm matches
    Quat temp(-a2.mX, -a2.mY, -a2.mZ, -a2.mW);
    this->rotate(temp);
}

void Vector3f::rotateTo(Matrix4f& a2, Vector3f& a3)
{ // asm matches
    a3.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[0][1] * this->mY + a2.mMatrix4f[0][2] * this->mZ;
    a3.mY = a2.mMatrix4f[1][0] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[1][2] * this->mZ;
    a3.mZ = a2.mMatrix4f[2][0] * this->mX + a2.mMatrix4f[2][1] * this->mY + a2.mMatrix4f[2][2] * this->mZ;
}

void Vector3f::rotateTranspose(Matrix4f& a2)
{ // asm matches
    Vector3f tmp;
    tmp.mX = a2.mMatrix4f[0][0] * this->mX + a2.mMatrix4f[1][0] * this->mY + a2.mMatrix4f[2][0] * this->mZ;
    tmp.mY = a2.mMatrix4f[0][1] * this->mX + a2.mMatrix4f[1][1] * this->mY + a2.mMatrix4f[2][1] * this->mZ;
    tmp.mZ = a2.mMatrix4f[0][2] * this->mX + a2.mMatrix4f[1][2] * this->mY + a2.mMatrix4f[2][2] * this->mZ;
    *this = tmp;
}

void Vector3f::scale(float a2)
{ // asm matches
    this->mX *= a2;
    this->mY *= a2;
    this->mZ *= a2;
}

void Vector3f::scale2(float a2, Vector3f& a3)
{ // asm matches
    this->mX = a3.mX * a2;
    this->mY = a3.mY * a2;
    this->mZ = a3.mZ * a2;
}

void Vector3f::set(const Vector3f& a2)
{ // asm matches
    this->set(a2.mX, a2.mY, a2.mZ);
}

void Vector3f::set(const float& a2, const float& a3, const float& a4)
{ // asm matches
    this->mX = a2;
    this->mY = a3;
    this->mZ = a4;
}

float Vector3f::squaredLength()
{ // asm matches
    return (this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ);
}

void Vector3f::sub(Vector3f& a2)
{ // asm matches
    this->mX -= a2.mX;
    this->mY -= a2.mY;
    this->mZ -= a2.mZ;
}

void Vector3f::sub(Vector3f& a2, Vector3f& a3)
{ // asm matches
    this->mX = a2.mX - a3.mX;
    this->mY = a2.mY - a3.mY;
    this->mZ = a2.mZ - a3.mZ;
}

void Vector3f::sub2(Vector3f& a2, Vector3f& a3)
{ // asm matches
    float z = a2.mZ - a3.mZ;
    float y = a2.mY - a3.mY;
    float x = a2.mX - a3.mX;
    set(x, y, z);
}

void Vector3f::write(Stream& a2)
{ // asm matches
    a2.writeFloat(this->mX);
    a2.writeFloat(this->mY);
    a2.writeFloat(this->mZ);
}