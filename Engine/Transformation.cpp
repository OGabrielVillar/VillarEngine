#include "Transformation.h"

Transformation::Transformation(Vec2 position_in)
{
	position = position_in;
}

Transformation::Transformation(WPosition position_in)
{
	position = position_in;
}

Transformation::Transformation(WPosition position_in, Vec2 scale_in, Vec2 orientation_in)
{
	position = position_in;
	scale = scale_in;
	SetOrientation(orientation_in);
}

Transformation::Transformation(WPosition position_in, float scale_in, Vec2 orientation_in)
{
	position = position_in;
	scale = scale_in;
	SetOrientation(orientation_in);
}

Transformation::Transformation(WPosition position_in, Vec2 scale_in, float orientationrad_in)
{
	position = position_in;
	scale = scale_in;
	SetOrientationInRadians(orientationrad_in);
}

Transformation::Transformation(WPosition position_in, Vec2 scale_in, Vec2 orientation_in, float orientationrad_in)
{
	position = position_in;
	scale = scale_in;
	orientation = orientation_in;
	orientation_rad = orientationrad_in;
}

Transformation Transformation::operator+(const Transformation & rhs) const
{
	return Transformation(position + GetRotated(rhs.position,orientation),scale*rhs.scale,GetRotated(rhs.orientation,orientation));
}

Transformation & Transformation::operator+=(const Transformation & rhs)
{
	return *this = *this + rhs;
}

Transformation Transformation::operator-(const Transformation & rhs) const
{
	return Transformation(GetRotated((rhs.position - position), GetInvertedAngle(orientation))*scale, scale*rhs.scale, GetRotated(rhs.orientation, GetInvertedAngle(orientation)));
}

Transformation & Transformation::operator-=(const Transformation & rhs)
{
	return *this = *this - rhs;
}


Transformation Transformation::operator-(const Vec2 & position_rhs) const
{
	return Transformation(position - position_rhs, scale, orientation);
}

Transformation & Transformation::operator-=(const Vec2 & position_rhs)
{
	return *this = *this - position_rhs;
}

Transformation Transformation::operator+(const Vec2 & position_rhs) const
{
	return Transformation(position + position_rhs, scale, orientation);
}

Transformation & Transformation::operator+=(const Vec2 & position_rhs)
{
	return *this = *this + position_rhs;
}

void Transformation::SetPosition(const Vec2 & rhs)
{
	position = rhs;
}

void Transformation::RotatesBy(const Vec2 & rhs)
{
	SetOrientation(GetRotated(orientation,rhs));
}

void Transformation::ScalesBy(float const rhs)
{
	scale *= rhs;
}

void Transformation::MovesBy(const Vec2 & rhs)
{
	position += rhs;
}

void Transformation::MovesBy(const WPosition & rhs)
{
	position += rhs;
}

void Transformation::MoveTo(const WPosition & rhs)
{
	position = rhs;
}

Vec2 Transformation::GetPosition() const
{
	return position.GetPosition();
}

WPosition Transformation::GetWPosition() const
{
	return position;
}

Vec2 Transformation::GetOrientation()
{
	return orientation;
}

float Transformation::GetOrientationDegrees()
{
	return std::atan2(orientation.y, orientation.x) * 180 / PI;
}

float Transformation::GetScale() const
{
	return scale.x;
}

void Transformation::SetOrientation(Vec2 orientation_in)
{
	//x=cos, y=sin
	orientation = orientation_in;
}

void Transformation::SetOrientationInRadians(float orientation_in)
{
	orientation_rad = orientation_in;
	orientation = Vec2(std::cos(orientation_in), std::sin(orientation_in));
}
