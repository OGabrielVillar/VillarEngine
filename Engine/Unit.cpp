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

void Unit::SetRadius(float radius_in)
{
	rigidbody.SetFormRadius(radius_in);
}

void Unit::SetDensity(float density_in)
{
	rigidbody.SetDensity(density_in);
}

void Unit::SetTransformation(Transformation transformation_in)
{
	transformation = transformation_in;
	rigidbody.SetTransformation(transformation_in);
}

void Unit::SetPosition(Vec2 & position_in)
{
	transformation.position = position_in;
	rigidbody.transformation.position = position_in;
}

void Unit::SetRigidBody(RigidBody rigidbody_in)
{
	rigidbody = rigidbody_in;
}

void Unit::SetRigidBodyForm(Form form_in)
{
	rigidbody.form = form_in;
}

Command & Unit::GetCommand(char index)
{
	if (index > COMMANDCARDLENGHT)
	{
		return commandCard[0];
	}
	return commandCard[index];
}

std::string & Unit::GetName()
{
	return name;
}

float Unit::GetRadiusSqrd() const
{
	return rigidbody.form.GetRadiusFromCenterSqrd();
}

float Unit::GetFormRadius() const
{
	return rigidbody.form.GetRadius();
}

Transformation Unit::GetTransformation()
{
	return rigidbody.GetTransformation();
}

void Unit::CreateDefaultRigidBody()
{
	rigidbody = RigidBody(transformation);
	rigidbody.SetForm(Form(radius));
	isDefautBody = 1;
}
