#pragma once

#include "Transformation.h"

class Camera
{
public:
	Camera() = default;
	~Camera() = default;
	Transformation* GetTransformation();
	void SetTransformation(Transformation& const transf_in);
private:
	Transformation transformation;
	float zoom = 1.0f;
};