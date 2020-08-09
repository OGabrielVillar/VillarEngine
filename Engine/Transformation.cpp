#include "Transformation.h"

Transformation::Transformation(Vec2 position_in)
{
	position = position_in;
}

Transformation::Transformation(Vec2 position_in, Vec2 scale_in, float orientation_in)
{
	position = position_in;
	scale = scale_in;
	orientation_rad = orientation_in;
}

Transformation Transformation::operator+(const Transformation & rhs) const
{
	return Transformation(position + rhs.position, Vec2(scale.x * rhs.scale.x, scale.y * rhs.scale.y), orientation_rad + rhs.orientation_rad);
}

Transformation & Transformation::operator+=(const Transformation & rhs)
{
	return *this = *this + rhs;
}

Transformation Transformation::operator*(float rhs) const
{
	return Transformation(position * rhs, scale * rhs, orientation_rad * rhs);
}

Transformation & Transformation::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Transformation Transformation::operator-(const Transformation & rhs) const
{
	return Transformation(position - rhs.position, scale - rhs.scale, orientation_rad - rhs.orientation_rad);
}

Transformation & Transformation::operator-=(const Transformation & rhs)
{
	return *this = *this - rhs;
}

void Transformation::SetPosition(const Vec2 & rhs)
{
	position = rhs;
}

Vec2 Transformation::GetPosition() const
{
	return Vec2(position.x, position.y);
}

Vec2 Transformation::GetOrientation()
{
	return Vec2(orientation.x , orientation.y);
}

void Transformation::SetOrientation(Vec2 orientation_in)
{
	//x=sin, y=cos
	orientation = orientation_in;
	orientation_rad = GetAngle(orientation_in);
}

void Transformation::SetOrientationRad(float orientation_in)
{
	orientation_rad = orientation_in;
	orientation = Vec2(std::sin(orientation_in), std::cos(orientation_in));
}
