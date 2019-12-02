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

void Unit::SetRigidBody(RigidBody rigidbody_in)
{
	rigidbody = rigidbody_in;
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

float Unit::GetRadius()
{
	return rigidbody.form.radius;
}

Transformation Unit::GetTransformation()
{
	return rigidbody.GetTransformation();
}

void Unit::CreateDefaultRigidBody()
{
	rigidbody = RigidBody(transformation);
	rigidbody.SetForm(Form(transformation, radius));
	isDefautBody = 1;
}
