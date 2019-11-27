#pragma once

#include "Vec2.h"


class Transformation
{
public:
	Transformation() = default;
	Transformation(Vec2 position_in);
	Transformation(Vec2 position_in, Vec2 scale_in, Vec2 rotation_in);
	Transformation operator+(const Transformation& rhs) const;
	Transformation& operator+=(const Transformation& rhs);
	Transformation operator*(float rhs) const;
	Transformation& operator*=(float rhs);
	Transformation operator-(const Transformation& rhs) const;
	Transformation& operator-=(const Transformation& rhs);
	Vec2 GetPosition();
public:
	Vec2 position;
	Vec2 scale = Vec2(1.0f, 1.0f);
	Vec2 rotation;
};