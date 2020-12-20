#pragma once

#include "Transformation.h"

class Camera
{
public:
	Camera() = default;
	~Camera() = default;
	Transformation* GetTransformation();
	void SetTransformation(const Transformation& transf_in);
private:
	Transformation transformation;
public:
	float zoom = 1.0f;
};