#include "Transformation.h"

Transformation::Transformation(Vec2 position_in)
{
	position = position_in;
}

Transformation::Transformation(Vec2 position_in, Vec2 scale_in, Vec2 rotation_in)
{
	position = position_in;
	scale = scale_in;
	rotation = rotation_in;
}

Transformation Transformation::operator+(const Transformation & rhs) const
{
	return Transformation(position + rhs.position, Vec2(scale.x * rhs.scale.x, scale.y * rhs.scale.y), rotation + rhs.rotation);
}

Transformation & Transformation::operator+=(const Transformation & rhs)
{
	return *this = *this + rhs;
}

Transformation Transformation::operator*(float rhs) const
{
	return Transformation(position * rhs, scale * rhs, rotation * rhs);
}

Transformation & Transformation::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Transformation Transformation::operator-(const Transformation & rhs) const
{
	return Transformation(position - rhs.position, scale - rhs.scale, rotation - rhs.rotation);
}

Transformation & Transformation::operator-=(const Transformation & rhs)
{
	return *this = *this - rhs;
}

Vec2 Transformation::GetPosition()
{
	return position;
}
