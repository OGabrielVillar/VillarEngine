#include "Camera.h"

Transformation* Camera::GetTransformation()
{
	return &transformation;
}

void Camera::SetTransformation(const Transformation & transf_in)
{
	transformation = transf_in;
}
