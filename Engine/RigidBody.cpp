#include "RigidBody.h"

RigidBody::RigidBody()
{
}

RigidBody::RigidBody(Transformation transformation_in, float mass_in)
{
	SetTransformation(transformation_in);
	SetMass(mass_in);
}

RigidBody::RigidBody(Transformation transformation_in, float mass_in, Transformation& unitTransformation_in)
{
	units_transformation = &unitTransformation_in;
	SetTransformation(transformation_in);
	SetMass(mass_in);
}

void RigidBody::SetTransformation(Transformation transformation_in)
{
	if (unitAttached.GetUnitTransformationAttachment() != nullptr)
	{
		//unitAttached.SetUnitTransformation(transformation_in);
	}
	form.SetTransformation(transformation_in);
}

void RigidBody::SetMass(float mass_in)
{
	mass = mass_in;
}

void RigidBody::SetVelocity(Vec2 velocity_in)
{
	velocity = velocity_in;
}

void RigidBody::SetAcceleration(Vec2 acceleration_in)
{
	acceleration = acceleration_in;
}

void RigidBody::SetCircleForm(CircleForm circleform_in)
{
	form = circleform_in;
}

void RigidBody::SetUnitTransformationAttached(Transformation* unitTransformation_in)
{
	unitAttached.SetUnitTransformationAttachment(unitTransformation_in);
}

Transformation RigidBody::GetTransformation()
{
	return form.GetTransformation();
}

float RigidBody::GetMass()
{
	return mass;
}

Vec2 RigidBody::GetVelocity()
{
	return velocity;
}

Vec2 RigidBody::GetAcceleration()
{
	return acceleration;
}

Vec2 RigidBody::GetFinalForce()
{
	Vec2 sum;
	int i = 0;
	while (i <= NFORCESLIMIT)
	{
		sum += forces[i];
		i++;
	}
	return sum;
}

void RigidBody::AddForce(Vec2 force_in)
{
	for (int i = 0; i < NFORCESLIMIT; i++)
	{
		if (forces[i].x == 0 && forces[i].y == 0)
		{
			forces[i] = force_in;
			return;
		}
	}
}

void RigidBody::ApplyForces()
{
	velocity += GetFinalForce();
	ClearForces();
}

void RigidBody::ClearForces()
{
	for (int i = 0; i < NFORCESLIMIT; i++)
	{
		forces[i] *= 0;
	}
}
