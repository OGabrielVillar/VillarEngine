#include "Form.h"

Form::Form(float radius_in)
	:
	radius(radius_in)
{
}

Form::Form(float radius_in, Type type_in)
	:
	radius(radius_in),
	type(type_in)
{
}

void Form::SetRadius(float radius_in)
{
	radius = radius_in;
}

bool Form::IsCircle()
{
	return type == Type::Point;
}

float Form::GetRadius()
{
	return radius;
}
