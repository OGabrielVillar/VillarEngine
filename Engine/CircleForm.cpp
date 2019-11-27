#include "CircleForm.h"

CircleForm::CircleForm(Transformation transformation_in, float radius_in)
{
	SetTransformation(transformation_in);
	SetRadius(radius_in);
}

void CircleForm::SetTransformation(Transformation transformation_in)
{
	transformation = transformation_in;
}

void CircleForm::SetRadius(float radius_in)
{
	radius = radius_in;
}

Transformation CircleForm::GetTransformation()
{
	return transformation;
}

float CircleForm::GetRadius()
{
	return radius;
}
