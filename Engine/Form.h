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
		Curve3P,
	};
public:
	Form() = default;
	Form(float radius_in);
	Form(float radius_in, Type type_in);
public: //SETTERS
	void PushVertice(Transformation vertice_in);
	void SetVerticePosition(int index,Vec2 position_in);
	void MoveVerticeTo(int index, Vec2 position_in);
	void UpdateCentralPoint();
	void UpdateCentralPoint(Vec2 const vertice_movement);
	void SetRadius(float radius_in);
	bool IsCircle();
public: //GETTERS
	float GetRadius() const;
	float GetPerimeter() const;
	Type GetType() const;
	Vec2 GetCentralPoint() const;
	Transformation GetVertice(int index) const;
	int GetNumberOfVertices() const;
private: //PRIVATE FUNCTIONS
	void UpdateVertice(int index);
private:
	Type type = Type::Point;
	float radius = 1.0f;
	Transformation vertices[MAX_VERTICES+1];
	Vec2 central_point;
	float total_radius = 1.0f;
	bool inverted = false;
	int current_vert = 0;
};