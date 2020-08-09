#pragma once

#include "Vec2.h"


class Transformation
{
public:
	Transformation() = default;
	Transformation(Vec2 position_in);
	Transformation(Vec2 position_in, Vec2 scale_in, Vec2 orientation_in);
	Transformation(Vec2 position_in, Vec2 scale_in, float orientationrad_in);
private: Transformation(Vec2 position_in, Vec2 scale_in, Vec2 orientation_in, float orientationrad_in);
public:
	Transformation operator+(const Transformation& rhs) const;
	Transformation& operator+=(const Transformation& rhs);
	Transformation operator*(float rhs) const;
	Transformation& operator*=(float rhs);
	void SetPosition(const Vec2& rhs);
	void RotatesBy(const Vec2& rhs);
	Vec2 GetPosition() const;
	Vec2 GetOrientation();
	void SetOrientation(Vec2 orientation_in);
	void SetOrientationRad(float orientation_in);
public:
	Vec2 position;
	Vec2 scale = Vec2(1.0f, 1.0f);
	float orientation_rad = 0.0f; // radians
	Vec2 orientation = Vec2(1.0f,0.0f); //(cos,sin)
};
inline Vec2 GetRotated(const Vec2& vec_in, const Vec2& sincos_in) {
	return Vec2(
		vec_in.x * sincos_in.x - vec_in.y * sincos_in.y,
		vec_in.x * sincos_in.y + vec_in.y * sincos_in.x);
}
inline Vec2 GetRotated(const float float_in, const Vec2& sincos_in) {
	return GetRotated(Vec2(float_in, 0.0f), sincos_in);
}
inline Vec2 GetYInvertedAngle(const Vec2& sincos_in) {
	return Vec2(sincos_in.x,-sincos_in.y);
}
inline Vec2 GetXInvertedAngle(const Vec2& sincos_in) {
	return Vec2(-sincos_in.x, sincos_in.y);
}
