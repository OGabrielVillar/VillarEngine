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
	signed short x_chunk_in = (signed short)(rhs.x / 128.0f);
	signed short y_chunk_in = (signed short)(rhs.y / 128.0f);
	x = rhs.x - 128.0f * (float)x_chunk_in;
	y = rhs.y - 128.0f * (float)y_chunk_in;
	x_chunk = x_chunk_in;
	y_chunk = y_chunk_in;
}

WPosition::WPosition(float x_in, float y_in, signed short x_chunk_in, signed short y_chunk_in) :
	x_chunk(x_chunk_in),
	y_chunk(y_chunk_in),
	x(x_in),
	y(y_in)
{
	if (x >= 128.0f || x < -128.0f || y >= 128.0f || y < -128.0f)
	{
		signed short x_chunk_in = (signed short)(x / 128.0f);
		signed short y_chunk_in = (signed short)(y / 128.0f);
		x -= 128.0f * (float)x_chunk_in;
		y -= 128.0f * (float)y_chunk_in;
		x_chunk += x_chunk_in;
		y_chunk += y_chunk_in;
	}
}

WPosition WPosition::operator+(const WPosition & rhs) const
{
	float x_in = x + rhs.x;
	float y_in = y + rhs.y;
	if (x_in >= 128.0f || x_in < -128.0f || y_in >= 128.0f || y_in < -128.0f)
	{
		if (x_chunk >= _SHORT_SIZE)
		{
			//TO CODE
		}
		signed short x_chunk_in = (signed short)(x_in / 128.0f);
		signed short y_chunk_in = (signed short)(y_in / 128.0f);
		return WPosition(x_in - (128.0f * (float)x_chunk_in), y_in - (128.0f * (float)y_chunk_in), x_chunk + x_chunk_in + rhs.x_chunk, y_chunk + y_chunk_in + rhs.y_chunk);
	}
	return WPosition(x_in, y_in, x_chunk + rhs.x_chunk, y_chunk + rhs.y_chunk);
}

WPosition WPosition::operator+(const Vec2 & rhs) const
{
	float x_in = x + rhs.x;
	float y_in = y + rhs.y;
	if (x_in >= 128.0f || x_in < -128.0f || y_in >= 128.0f || y_in < -128.0f)
	{
		signed short x_chunk_in = (signed short)(x_in / 128.0f);
		signed short y_chunk_in = (signed short)(y_in / 128.0f);
		return WPosition(x_in - (128.0f * (float)x_chunk_in), y_in - (128.0f * (float)y_chunk_in), x_chunk + x_chunk_in, y_chunk + y_chunk_in);
	}
	return WPosition(x_in, y_in, x_chunk, y_chunk);
}

WPosition & WPosition::operator+=(const Vec2 & rhs)
{
	x += rhs.x;
	y += rhs.y;
	if (x >= 128.0f || x < -128.0f || y >= 128.0f || y < -128.0f)
	{
		signed short x_chunk_in = (signed short)(x / 128.0f);
		signed short y_chunk_in = (signed short)(y / 128.0f);
		x -= 128.0f * (float)x_chunk_in;
		y -= 128.0f * (float)y_chunk_in;
		x_chunk += x_chunk_in;
		y_chunk += y_chunk_in;
	}
	return *this;
}

WPosition WPosition::operator-(const WPosition & rhs) const
{
	float x_in = x - rhs.x;
	float y_in = y - rhs.y;
	if (x_in >= 128.0f || x_in < -128.0f || y_in >= 128.0f || y_in < -128.0f)
	{
		signed short x_chunk_in = (signed short)(x_in / 128.0f);
		signed short y_chunk_in = (signed short)(y_in / 128.0f);
		return WPosition(x_in - (128.0f * (float)x_chunk_in), y_in - (128.0f * (float)y_chunk_in), x_chunk + x_chunk_in - rhs.x_chunk, y_chunk + y_chunk_in - rhs.y_chunk);
	}
	return WPosition(x_in, y_in, x_chunk - rhs.x_chunk, y_chunk - rhs.y_chunk);
}

WPosition WPosition::operator-(const Vec2 & rhs) const
{
	float x_in = x - rhs.x;
	float y_in = y - rhs.y;
	if (x_in >= 128.0f || x_in < -128.0f || y_in >= 128.0f || y_in < -128.0f)
	{
		signed short x_chunk_in = (signed short)(x_in / 128.0f);
		signed short y_chunk_in = (signed short)(y_in / 128.0f);
		return WPosition(x_in - (128.0f * (float)x_chunk_in), y_in - (128.0f * (float)y_chunk_in), x_chunk + x_chunk_in, y_chunk + y_chunk_in);
	}
	return WPosition(x_in, y_in, x_chunk, y_chunk);
}

WPosition & WPosition::operator-=(const Vec2 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	if (x >= 128.0f || x < -128.0f || y >= 128.0f || y < -128.0f)
	{
		signed short x_chunk_in = (signed short)(x / 128.0f);
		signed short y_chunk_in = (signed short)(y / 128.0f);
		x -= 128.0f * (float)x_chunk_in;
		y -= 128.0f * (float)y_chunk_in;
		x_chunk += x_chunk_in;
		y_chunk += y_chunk_in;
	}
	return *this;
}

WPosition WPosition::operator-() const
{
	return WPosition(-x,-y,-x_chunk,-y_chunk);
}

WPosition & WPosition::operator=(const Vec2 & rhs)
{
	signed short x_chunk_in = (signed short)(rhs.x / 128.0f);
	signed short y_chunk_in = (signed short)(rhs.y / 128.0f);
	x = rhs.x - 128.0f * (float)x_chunk_in;
	y = rhs.y - 128.0f * (float)y_chunk_in;
	x_chunk = x_chunk_in;
	y_chunk = y_chunk_in;

	return *this;
}

Vec2 WPosition::GetPosition() const
{
	return Vec2(x + ((float)x_chunk * 128.0f) , y + ((float)y_chunk * 128.0f));
}
