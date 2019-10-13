#include <Math/Vector2f.h>

Vector2f::Vector2f(const float& _x, const float& _y)
{
    this->x = _x;
    this->y = _y;
}

void Vector2f::read(Stream& stream)
{
    this->x = stream.readFloat();
    this->y = stream.readFloat();
}

void Vector2f::write(Stream& stream)
{
    stream.writeFloat(this->x);
    stream.writeFloat(this->y);
}

void Vector2f::set(float _x, float _y)
{
    this->x = _x;
    this->y = _y;
}
