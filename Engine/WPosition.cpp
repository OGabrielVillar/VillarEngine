#define OFFSET_REARRANGEMENT = 256.0f //128.0f;
#include "WPosition.h"

WPosition::WPosition() :
x(0.0f),
y(0.0f),
x_chunk(0),
y_chunk(0)
{
}

WPosition::WPosition(const Vec2 & rhs)
{
	*this = WPosition(rhs.x, rhs.y, 0, 0);
//	if (x >= 128.0f || y >= 128.0f)
//	{
//		signed short x_chunk_in = (signed short)((x / 256.0f));
//		signed short y_chunk_in = (signed short)((y / 256.0f));
//		x -= 256.0f * (float)x_chunk_in;
//		y -= 256.0f * (float)y_chunk_in;
//		x_chunk = x_chunk_in;
//		y_chunk = y_chunk_in;
//	}
//	else if (x < -128.0f || y < -128.0f)
//	{
//		signed short x_chunk_in = (signed short)((x / 256.0f) - 0.5f);
//		signed short y_chunk_in = (signed short)((y / 256.0f) - 0.5f);
//		x -= 256.0f * (float)x_chunk_in;
//		y -= 256.0f * (float)y_chunk_in;
//		x_chunk = x_chunk_in;
//		y_chunk = y_chunk_in;
//	}
}

WPosition::WPosition(float x_in, float y_in, signed short x_chunk_in, signed short y_chunk_in) :
	x_chunk(x_chunk_in),
	y_chunk(y_chunk_in),
	x(x_in),
	y(y_in)
{
	signed short x_chunk_off(0);
	signed short y_chunk_off(0);
	if (x >= 128.0f)
	{
		x_chunk_off = (signed short)((x / 256.0f) + 0.5f);
		
	}
	else if (x < 128.0f)
	{
		x_chunk_off = (signed short)((x / 256.0f) - 0.5f);
	}
	if (y >= 128.0f)
	{
		y_chunk_off = (signed short)((y / 256.0f) + 0.5f);
	}
	else if (y < 128.0f)
	{
		y_chunk_off = (signed short)((y / 256.0f) - 0.5f);
	}
	x -= 256.0f * (float)x_chunk_off;
	y -= 256.0f * (float)y_chunk_off;
	x_chunk += x_chunk_off;
	y_chunk += y_chunk_off;
	return;
}

WPosition WPosition::operator+(const WPosition & rhs) const
{
	return WPosition(x + rhs.x, y + rhs.y, x_chunk + rhs.x_chunk, y_chunk + rhs.y_chunk);
}

WPosition WPosition::operator+(const Vec2 & rhs) const
{
	return WPosition(x + rhs.x, y + rhs.y, x_chunk, y_chunk);
}

WPosition & WPosition::operator+=(const WPosition & rhs)
{
	return *this = *this + rhs;
}

WPosition & WPosition::operator+=(const Vec2 & rhs)
{
	return *this = *this + rhs;
}

WPosition WPosition::operator-(const WPosition & rhs) const
{
	return WPosition(x - rhs.x, y - rhs.y, x_chunk - rhs.x_chunk, y_chunk - rhs.y_chunk);
}

WPosition WPosition::operator-(const Vec2 & rhs) const
{
	return WPosition(x - rhs.x, y - rhs.y, x_chunk, y_chunk);
}

WPosition & WPosition::operator-=(const Vec2 & rhs)
{
	return *this = *this - rhs;
}

WPosition WPosition::operator-() const
{
	return WPosition(-x,-y,-x_chunk,-y_chunk);
}

WPosition & WPosition::operator=(const Vec2 & rhs)
{
	return *this = WPosition(rhs);
}

Vec2 WPosition::GetPosition() const
{
	return Vec2(x + ((float)x_chunk * 256.0f) , y + ((float)y_chunk * 256.0f));
}

void WPosition::Reset()
{
	x = 0.0f;
	y = 0.0f;
	x_chunk = 0;
	y_chunk = 0;
}
