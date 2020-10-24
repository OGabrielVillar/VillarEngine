#include "Camera.h"

Transformation* Camera::GetTransformation()
{
	return &transformation;
}

void Camera::SetTransformation(Transformation & const transf_in)
{
	transformation = transf_in;
}
