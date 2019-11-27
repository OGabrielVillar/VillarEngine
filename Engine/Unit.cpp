#include "Unit.h"

Unit::Unit()
{
}

Unit::Unit(std::string name_in, Transformation transf_in)
{
	name = name_in;
	transformation = transf_in;
	radius = 10.0f;
	CreateDefaultRigidBody();
}

Vec2 Unit::GetPosition()
{
	return transformation.GetPosition();
}

void Unit::AddCommand(Command cmd)
{
	char i = 0;
	while (i < COMMANDCARDLENGHT)
	{
		if (commandCard[i].GetKey() == 0)
		{
			commandCard[i] = cmd;
			return;
		}
		i++;
	}
}

void Unit::SetRadiusTo(float radius_in)
{
	radius = radius_in;
	if (isDefautBody)
	{
		rigidbody.SetCircleFormRadius(radius_in);
	}
}

void Unit::SetTransformation(Transformation transformation_in)
{
	transformation = transformation_in;
}

void Unit::SetRigidBody(RigidBody rigidbody_in)
{
	rigidbody = rigidbody_in;
	rigidbody.SetUnitTransformationAttached(&transformation);
}

Command & Unit::GetCommand(char index)
{
	if (index > COMMANDCARDLENGHT)
	{
		return Command();
	}
	return commandCard[index];
}

std::string & Unit::GetName()
{
	return name;
}

float Unit::GetRadius()
{
	return radius;
}

Transformation & Unit::GetTransformation()
{
	return transformation;
}

void Unit::CreateDefaultRigidBody()
{
	rigidbody = RigidBody(transformation, 10.0f, transformation);
	rigidbody.units_transformation = &transformation;
	rigidbody.SetCircleForm(CircleForm(transformation, radius));
	isDefautBody = 1;
}
