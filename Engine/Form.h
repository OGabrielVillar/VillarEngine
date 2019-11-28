#pragma once

#include "Transformation.h"

class Form
{
public:
	Form() = default;
	Form(Transformation transformation_in, float radius_in);
public:
	enum class Type 
	{
		Point,
		Line,
		Polygon,
	};
public: //SETTERS
	void SetTransformation(Transformation transformation_in);
	void SetRadius(float radius_in);
public: //GETTERS
	Transformation GetTransformation();
	float GetRadius();
public:
	Type type = Type::Point;
	float radius = 1.0f;
	Vec2 vertices[3];
	Transformation transformation;
};