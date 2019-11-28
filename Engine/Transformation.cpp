#include "Transformation.h"

Transformation::Transformation(Vec2 position_in)
{
	position = position_in;
}

Transformation::Transformation(Vec2 position_in, Vec2 scale_in, float orientation_in)
{
	position = position_in;
	scale = scale_in;
	orientation = orientation_in;
}

Transformation Transformation::operator+(const Transformation & rhs) const
{
	return Transformation(position + rhs.position, Vec2(scale.x * rhs.scale.x, scale.y * rhs.scale.y), orientation + rhs.orientation);
}

Transformation & Transformation::operator+=(const Transformation & rhs)
{
	return *this = *this + rhs;
}

Transformation Transformation::operator*(float rhs) const
{
	return Transformation(position * rhs, scale * rhs, orientation * rhs);
}

Transformation & Transformation::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Transformation Transformation::operator-(const Transformation & rhs) const
{
	return Transformation(position - rhs.position, scale - rhs.scale, orientation - rhs.orientation);
}

Transformation & Transformation::operator-=(const Transformation & rhs)
{
	return *this = *this - rhs;
}

Vec2 Transformation::GetPosition()
{
	return Vec2(position.x, position.y);
}
