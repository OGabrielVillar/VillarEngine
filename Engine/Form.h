#pragma once

#include "Transformation.h"

class Form
{
public:
	enum class Type 
	{
		Point,
		Line,
		Polygon,
	};
public:
	Form() = default;
	Form(float radius_in);
	Form(float radius_in, Type type_in);
public: //SETTERS
	void SetRadius(float radius_in);
	bool IsCircle();
public: //GETTERS
	float GetRadius();
public:
	Type type = Type::Point;
	float radius = 1.0f;
	Vec2 vertices[3];
	bool inverted = false;
};