#include "Form.h"

Form::Form(Transformation transformation_in, float radius_in)
{
	SetTransformation(transformation_in);
	SetRadius(radius_in);
}

void Form::SetTransformation(Transformation transformation_in)
{
	transformation = transformation_in;
}

void Form::SetRadius(float radius_in)
{
	radius = radius_in;
}

bool Form::IsCircle()
{
	return type == Type::Point;
}

Transformation Form::GetTransformation()
{
	return transformation;
}

Vec2 Form::GetPosition()
{
	return transformation.GetPosition();
}

float Form::GetRadius()
{
	return radius;
}
