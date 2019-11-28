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

Transformation Form::GetTransformation()
{
	return transformation;
}

float Form::GetRadius()
{
	return radius;
}
