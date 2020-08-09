#pragma once

const int MAX_VERTICES = 5;

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
	void PushVertice(Transformation vertice_in);
	void MoveVerticeTo(int index,Vec2 position_in);
	void SetRadius(float radius_in);
	bool IsCircle();
public: //GETTERS
	float GetRadius() const;
	Type GetType() const;
	Transformation GetVertice(int index) const;
private: //PRIVATE FUNCTIONS
	void UpdateVertice(int index);
private:
	Type type = Type::Point;
	float radius = 1.0f;
	Transformation vertices[MAX_VERTICES];
	bool inverted = false;
	int current_vert = 0;
};