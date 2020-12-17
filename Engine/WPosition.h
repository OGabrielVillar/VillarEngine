#pragma once

#include "Vec2.h"

class WPosition
{
public:
	WPosition();
	WPosition(const Vec2& rhs);
	WPosition(float x_in, float y_in, signed short x_chunk_in, signed short y_chunk_in);
	~WPosition() = default;
	// +
	WPosition operator+(const WPosition& rhs) const;
	WPosition operator+(const Vec2& rhs) const;
	WPosition& operator+=(const WPosition& rhs);
	WPosition& operator+=(const Vec2& rhs);
	// -
	WPosition operator-(const WPosition& rhs) const;
	WPosition operator-(const Vec2& rhs) const;
	WPosition& operator-=(const Vec2& rhs);
	WPosition operator-() const;
	// =
	WPosition& operator=(const Vec2& rhs);
	//FUNCTIONS
	Vec2 GetPosition() const;
	void Reset();
public:
	signed short x_chunk = 0;
	signed short y_chunk = 0;
	float x;
	float y;
	signed char x_round;
	signed char y_round;
};
inline Vec2 DistFromTo(const WPosition& a, const WPosition& b)
{
	if (a.x_chunk == b.x_chunk && a.y_chunk == b.y_chunk) {
		return Vec2(b.x - a.x, b.y - a.y);
	}
	return Vec2((b.x + ((float)b.x_chunk * 128.0f)) - (a.x + ((float)a.x_chunk * 128.0f)), (b.y + ((float)b.y_chunk * 128.0f)) - (a.y + ((float)a.y_chunk * 128.0f)));
}