#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2( float x_in,float y_in )
	:
	x( x_in ),
	y( y_in )
{
}

Vec2 Vec2::operator+( const Vec2& rhs ) const
{
	return Vec2( x + rhs.x,y + rhs.y );
}

Vec2& Vec2::operator+=( const Vec2& rhs )
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator*( float rhs ) const
{
	return Vec2( x * rhs,y * rhs );
}

Vec2& Vec2::operator*=( float rhs )
{
	return *this = *this * rhs;
}

Vec2 Vec2::operator-( const Vec2& rhs ) const
{
	return Vec2( x - rhs.x,y - rhs.y );
}

Vec2& Vec2::operator-=( const Vec2& rhs )
{
	return *this = *this - rhs;
}

float Vec2::GetLength() const
{
	return std::sqrt( GetLengthSq() );
}

float Vec2::GetLengthSq() const
{
	return x * x + y * y;
}

Vec2& Vec2::Normalize()
{
	return *this = GetNormalized();
}

Vec2 Vec2::GetNormalized() const
{
	const float len = GetLength();
	if( len != 0.0f )
	{
		return *this * (1.0f / len);
	}
	return *this;
}

Vec2::operator Vei2() const
{
	return{ int( x ),int( y ) };
}

float Vec2::GetTangencialRelativeDistance(Vec2 mdl_target, Vec2 end_target)
{
	Vec2 diference = end_target - Vec2(x,y);
	Vec2 mdl_diference = end_target - mdl_target, vec2;
	float sqr_hip = diference.x * diference.x + diference.y * diference.y;
	float mdl_sqr_hip = mdl_diference.x * mdl_diference.x + mdl_diference.y * mdl_diference.y;
	float final = 1 - ( mdl_sqr_hip / sqr_hip );
	return final;
}
