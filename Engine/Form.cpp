#include "Form.h"

Form::Form(float radius_in)
	:
	radius(radius_in)
{
}

Form::Form(float radius_in, Type type_in)
	:
	radius(radius_in),
	type(type_in)
{
}

void Form::PushVertice(Transformation vertice_in)
{
	if (current_vert >= MAX_VERTICES)
	{
		return;
	}
	current_vert++;
	vertices[current_vert] = vertice_in;
	UpdateVertice(current_vert);
}

void Form::MoveVerticeTo(int index, Vec2 position_in)
{
	vertices[index].SetPosition(position_in);
	UpdateVertice(index);
}

void Form::SetRadius(float radius_in)
{
	radius = radius_in;
}

bool Form::IsCircle()
{
	return type == Type::Point;
}

float Form::GetRadius() const
{
	return radius;
}

Form::Type Form::GetType() const
{
	return type;
}

Transformation Form::GetVertice(int index) const
{
	return Transformation(vertices[index]);
}

void Form::UpdateVertice(int index)
{
	Transformation* next = nullptr;
	Transformation* previous = nullptr;
	if (index >= MAX_VERTICES)
	{
		next = &vertices[0];
	}
	else
	{
		next = &vertices[index+1];
	}
	if (index <= 0)
	{
		previous = &vertices[current_vert];
	}
	else
	{
		previous = &vertices[index-1];
	}
	Vec2 index_to_next = next->GetPosition() - vertices[index].GetPosition();
	Vec2 previous_to_index = vertices[index].GetPosition() - previous->GetPosition();
	vertices[index].SetOrientation(index_to_next.GetNormalized());
	previous->SetOrientation(previous_to_index.GetNormalized());
}
