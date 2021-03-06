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
	UpdateCentralPoint(vertice_in.GetPosition() - central_point);
}

void Form::SetVerticePosition(int index, Vec2 position_in)
{
	UpdateCentralPoint(position_in - vertices[index].GetPosition());
	vertices[index].SetPosition(position_in);
	UpdateVertice(index);
}

void Form::MoveVerticeTo(int index, Vec2 position_in)
{
	SetVerticePosition(index, position_in);
}

void Form::UpdateCentralPoint()
{
	central_point = 0.0f;
	for (size_t i = 0; i <= current_vert; i++)
	{
		central_point += vertices[i].GetPosition();
	}
	central_point /= (float)(current_vert+1);
}

void Form::UpdateCentralPoint(Vec2 const vertice_movement)
{
	central_point += vertice_movement/(float)(current_vert + 1);
}

float Form::GetRadiusFromCenterSqrd() const
{
	float radiusSqrd = Sqr(radius);
	if (current_vert == 0)
	{
		return radiusSqrd;
	}
	float furthest_point = 0.0f;
	for (size_t i = 0; i <= current_vert; i++)
	{
		float iDist = (DistSqr(vertices[i].GetPosition(),central_point));
		if (iDist > furthest_point)
		{
			furthest_point = iDist;
		};
	}
	return furthest_point+radiusSqrd;

}

Vec2 Form::GetCentralPoint() const
{
	return central_point;
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

float Form::GetPerimeter() const
{
	if (type==Type::Point)
	{
		return	PI * radius * 2.0f;
	}
	else if (type == Type::Line)
	{
		return	PI * radius * 2.0f + Vec2(vertices[0].GetPosition() - vertices[1].GetPosition()).Len() * 2.0f;
	}
	return 0.0f;
}

Form::Type Form::GetType() const
{
	return type;
}

Transformation Form::GetVertice(int index) const
{
	return Transformation(vertices[index]);
}

int Form::GetNumberOfVertices() const
{
	return current_vert+1;
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
