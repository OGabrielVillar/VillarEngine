#pragma once

#include "Transformation.h"

class CircleForm
{
public:
	CircleForm() = default;
	CircleForm(Transformation transformation_in, float radius_in);
public: //SETTERS
	void SetTransformation(Transformation transformation_in);
	void SetRadius(float radius_in);
public: //GETTERS
	Transformation GetTransformation();
	float GetRadius();
private:
	float radius = 1.0f;
	Transformation transformation;
};