#include <Math/Quat.h>


Quat::Quat() : Vector3f() {} // asm matches

Quat::Quat(float a2, float a3, float a4, float a5) : Vector3f()
{ // asm matches
    this->set(a2, a3, a4, a5);
}

float doSin(float a2)
{ // asm matches (used elsewhere)
    return sin(a2);
}

float doCos(float a2)
{ // asm matches (used elsewhere)
    return cos(a2);
}

void Quat::fromEuler(Vector3f& a2)
{ // asm matches
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

float doSqrt(float a2)
{ // asm matches (used elsewhere)
    return sqrt(a2);
}

void Quat::fromMat3f(Matrix3f& mtx)
{ // asm matches :')
    float tmp1 = (mtx.mMatrix3f[0][0] + mtx.mMatrix3f[1][1] + mtx.mMatrix3f[2][2] + 1.0f) * 0.25f;
    float tmp2 = tmp1 - (mtx.mMatrix3f[1][1] + mtx.mMatrix3f[2][2]) * 0.5f;
    float tmp3 = tmp1 - (mtx.mMatrix3f[2][2] + mtx.mMatrix3f[0][0]) * 0.5f;
    float tmp4 = tmp1 - (mtx.mMatrix3f[0][0] + mtx.mMatrix3f[1][1]) * 0.5f;

    float tmp7;
    int tmp6, wtf1, wtf2, wtf3, wtf4, wtf5, wtf6, wtf7;

    if (tmp1 > tmp2)
    {
        if (tmp1 > tmp3)
        {
            if (tmp1 > tmp4)
            {
                wtf1 = 0;
            }
            else
            {
                wtf1 = 3;
            }
            wtf2 = wtf1;
        }
        else
        {
            if (tmp3 > tmp4)
            {
                wtf3 = 2;
            }
            else
            {
                wtf3 = 3;
            }
            wtf2 = wtf3;
        }
        wtf4 = wtf2;
    }
    else
    {
        if (tmp2 > tmp3)
        {
            if (tmp2 > tmp4)
            {
                wtf5 = 1;
            }
            else
            {
                wtf5 = 3;
            }
            wtf6 = wtf5;
        }
        else
        {
            if (tmp3 > tmp4)
            {
                wtf7 = 2;
            }
            else
            {
                wtf7 = 3;
            }
            wtf6 = wtf7;
        }
        wtf4 = wtf6;
    }

    tmp6 = wtf4;

    switch (tmp6)
    {
    case 0:
    {
        this->mW = doSqrt(tmp1);
        tmp7 = 0.25f / this->mW;
        this->mX = (mtx.mMatrix3f[2][1] - mtx.mMatrix3f[1][2]) * tmp7;
        this->mY = (mtx.mMatrix3f[0][2] - mtx.mMatrix3f[2][0]) * tmp7;
        this->mZ = (mtx.mMatrix3f[1][0] - mtx.mMatrix3f[0][1]) * tmp7;
    }
    break;

    case 1:
    {
        this->mX = doSqrt(tmp2);
        tmp7 = 0.25f / this->mX;
        this->mW = (mtx.mMatrix3f[2][1] - mtx.mMatrix3f[1][2]) * tmp7;
        this->mY = (mtx.mMatrix3f[0][1] + mtx.mMatrix3f[1][0]) * tmp7;
        this->mZ = (mtx.mMatrix3f[0][2] + mtx.mMatrix3f[2][0]) * tmp7;
    }
    break;

    case 2:
    {
        this->mY = doSqrt(tmp3);
        tmp7 = 0.25f / this->mY;
        this->mW = (mtx.mMatrix3f[0][2] - mtx.mMatrix3f[2][0]) * tmp7;
        this->mZ = (mtx.mMatrix3f[1][2] + mtx.mMatrix3f[2][1]) * tmp7;
        this->mX = (mtx.mMatrix3f[1][0] + mtx.mMatrix3f[0][1]) * tmp7;
    }
    break;

    case 3:
    {
        this->mZ = doSqrt(tmp4);
        tmp7 = 0.25f / this->mZ;
        this->mW = (mtx.mMatrix3f[1][0] - mtx.mMatrix3f[0][1]) * tmp7;
        this->mX = (mtx.mMatrix3f[2][0] + mtx.mMatrix3f[0][2]) * tmp7;
        this->mY = (mtx.mMatrix3f[2][1] + mtx.mMatrix3f[1][2]) * tmp7;
    }
    break;

    default:
        break;
    }

    if (this->mW < 0.0f)
    {
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

void Quat::genVectorX(Vector3f& vec)
{ // asm matches
    vec.mX = 1.0f - (2 * (this->mY * this->mY)) - (2 * (this->mZ * this->mZ));
    vec.mY = (2 * (this->mX * this->mY)) + (2 * (this->mW * this->mZ));
    vec.mZ = (2 * (this->mX * this->mZ)) - (2 * (this->mW * this->mY));
}

void Quat::genVectorY(Vector3f& vec)
{ // asm matches
    vec.mX = (2 * (this->mX * this->mY)) + (2 * (this->mW * this->mZ));
    vec.mY = 1.0f - (2 * (this->mX * this->mX)) - (2 * (this->mZ * this->mZ));
    vec.mZ = (2 * (this->mY * this->mZ)) - (2 * (this->mW * this->mX));
}

void Quat::genVectorZ(Vector3f& vec)
{ // asm matches
    vec.mX = (2 * (this->mX * this->mZ)) - (2 * (this->mW * this->mY));
    vec.mY = (2 * (this->mY * this->mZ)) + (2 * (this->mW * this->mX));
    vec.mZ = 1.0f - (2 * (this->mX * this->mX)) - (2 * (this->mY * this->mY));
}

void Quat::multiply(Quat& a2)
{ // asm matches
    Quat quat;
    quat.mW = a2.mW * this->mW - a2.mX * this->mX - a2.mY * this->mY - a2.mZ * this->mZ;
    quat.mX = a2.mW * this->mX + a2.mX * this->mW + a2.mY * this->mZ - a2.mZ * this->mY;
    quat.mY = a2.mW * this->mY + a2.mY * this->mW + a2.mZ * this->mX - a2.mX * this->mZ;
    quat.mZ = a2.mW * this->mZ + a2.mZ * this->mW + a2.mX * this->mY - a2.mY * this->mX;
    *this = quat;
}

void Quat::multiplyTo(Quat& a2, Quat& a3)
{ // asm matches
    this->mW = a3.mW * a2.mW - a3.mX * a2.mX - a3.mY * a2.mY - a3.mZ * a2.mZ;
    this->mX = a3.mW * a2.mX + a3.mX * a2.mW + a3.mY * a2.mZ - a3.mZ * a2.mY;
    this->mY = a3.mW * a2.mY + a3.mY * a2.mW + a3.mZ * a2.mX - a3.mX * a2.mZ;
    this->mZ = a3.mW * a2.mZ + a3.mZ * a2.mW + a3.mX * a2.mY - a3.mY * a2.mX;
}

void Quat::normalise()
{ // asm matches
    float v2 = 1.0f / doSqrt(this->mX * this->mX + this->mY * this->mY + this->mZ * this->mZ + this->mW * this->mW);
    this->mX *= v2;
    this->mY *= v2;
    this->mZ *= v2;
    this->mW *= v2;
}

void Quat::rotate(Vector3f& rotateBy, float time)
{ // asm matches
    float v2 = doSin(time * 0.5f);
    Quat quat(rotateBy.mX * v2, rotateBy.mY * v2, rotateBy.mZ * v2, doCos(time * 0.5f));
    this->multiply(quat);
}

void Quat::set(float x, float y, float z, float w)
{ // asm matches
    this->mX = x;
    this->mY = y;
    this->mZ = z;
    this->mW = w;
}

float doACos(float a2)
{ // asm matches
    return acos(a2);
}

void Quat::slerp(Quat& slerpTo, float time, int unused)
{ // asm matches
    float v5, theta_0, v3;
    float dot = this->mX * slerpTo.mX + this->mY * slerpTo.mY + this->mZ * slerpTo.mZ + this->mW * slerpTo.mW;
    float theta;
    int b1;

    if (dot < 0.0f)
    {
        dot = -dot;
        b1 = 1;
    }
    else
    {
        b1 = 0;
    }

    if ((1.0f - dot) < 0.000001)
    {
        v5 = 1.0f - time;
    }
    else
    {
        theta_0 = doACos(dot);
        theta = theta_0;
        v3 = doSin(theta_0);
		// time * theta = angle between this and slerpTo 
        v5 = doSin(theta_0 - time * theta) / v3;
        time = doSin(time * theta) / v3;
    }

    if (b1)
    {
        time = -time;
    }

    this->mX = v5 * this->mX + time * slerpTo.mX;
    this->mY = v5 * this->mY + time * slerpTo.mY;
    this->mZ = v5 * this->mZ + time * slerpTo.mZ;
    this->mW = v5 * this->mW + time * slerpTo.mW;
}