#pragma once

const float PI = 3.141592741f;
const float EPSILON = 0.0001f;
const float FOURTHIRDS = 4.0f / 3.0f;

#include "Vei2.h"
#include <vector>

class Vec2
{
public:
	Vec2();
	Vec2( float in );
	Vec2( float x_in,float y_in );
public://OPERATORS
		// +
		Vec2 operator+( const Vec2& rhs ) const;
		Vec2& operator+=( const Vec2& rhs );
		Vec2 operator+(float rhs) const;
		Vec2& operator+=(float rhs);
		// -
		Vec2 operator-(const Vec2& rhs) const;
		Vec2& operator-=(const Vec2& rhs);
		Vec2 operator-(float rhs) const;
		Vec2& operator-=(float rhs);
		Vec2 operator-() const;
		// *
		Vec2 operator*(const Vec2& rhs) const;
		Vec2& operator*=(const Vec2& rhs);
		Vec2 operator*( float rhs ) const;
		Vec2& operator*=( float rhs );
		// /
		Vec2 operator/(const Vec2& rhs) const;
		Vec2& operator/=(const Vec2& rhs);
		Vec2 operator/(float rhs) const;
		Vec2& operator/=(float rhs);

	void Set(float x_in, float y_in);
public://MATH FUNCTIONS
	float Len() const;
	float LenSqr() const;
	Vec2& Normalize();
	Vec2 GetNormalized() const;
	explicit operator Vei2() const;
	float GetTangencialRelativeDistance(Vec2 mdl_target, Vec2 end_target);
	float CrossProduct(const Vec2 & a, const Vec2 & b);
	Vec2 CrossProduct(const Vec2 & a, float s);
	Vec2 CrossProduct(float s, const Vec2 & a);
public:
	float x;
	float y;
};
inline float Dot(const Vec2& a, const Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}
inline Vec2 operator*(float s, const Vec2& v)
{
	return Vec2(s * v.x, s * v.y);
}
inline Vec2 operator/(float s, const Vec2& v)
{
	return Vec2(s / v.x, s / v.y);
}
inline float DistSqr(const Vec2& a, const Vec2& b)
{
	Vec2 c = a - b;
	return Dot(c, c);
}
inline Vec2 Cross(const Vec2& v, float a)
{
	return Vec2(a * v.y, -a * v.x);
}
inline Vec2 Cross(float a, const Vec2& v)
{
	return Vec2(-a * v.y, a * v.x);
}
inline float Cross(const Vec2& a, const Vec2& b)
{
	return a.x * b.y - a.y * b.x;
}
inline float Mag(const Vec2& a)
{
	return std::sqrt(a.x * a.x + a.y * a.y);
}
inline float GetAngle(const Vec2& v1)
{
	return atan2(v1.y, v1.x);
}
inline float GetAngleBetween(const Vec2& v1, const Vec2& v2)
{
	return GetAngle(v2-v1);
	//return atan2(v2.x-v1.x, v2.y-v1.y);
}
inline Vec2 GetRotated90(Vec2 vec_in) {
	return Vec2(vec_in.y, -vec_in.x);
}
inline Vec2 GetRotated90OnAxis(Vec2 vec_in,Vec2 axis_in) {
	Vec2 line_section = vec_in-axis_in;
	return Vec2(line_section.y+axis_in.x, -line_section.x+ axis_in.y);
}
inline Vec2 GetRotated(const Vec2& vec_in, float rad_in) {
	float sn = sin(rad_in);
	float cs = cos(rad_in);
	return Vec2(
		vec_in.x * cs - vec_in.y * sn, 
		vec_in.x * sn + vec_in.y * cs);
}