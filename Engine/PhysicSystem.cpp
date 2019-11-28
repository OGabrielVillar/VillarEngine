#include "PhysicSystem.h"

PhysicSystem::PhysicSystem(Unit * units_in)
{
	Punit = units_in;
}

void PhysicSystem::Go(float ft_in)
{
	ft = ft_in;
	MoveBodys();
}

void PhysicSystem::MoveBodys()
{
	for (int i = 0; i < UNITSLIMIT; i++)
	{
		if (!Punit->GetName().empty())
		{
			Punit->rigidbody.acceleration = Punit->rigidbody.force*ft;
			Punit->rigidbody.velocity += Punit->rigidbody.acceleration;
			Punit->rigidbody.SetTransformation(Punit->rigidbody.GetTransformation() + Punit->rigidbody.GetVelocity());
			Punit->rigidbody.force.Set(0.0f, 0.0f);
		}
		Punit++;
	}
	Punit -= UNITSLIMIT;
}

bool PhysicSystem::IsCollinding(RigidBody * rb_a, RigidBody * rb_b)
{
	if (rb_a->form.type == Form::Type::Point)
	{
		if (rb_b->form.type == Form::Type::Point)
		{

		}
	}
	return false;
}

bool PhysicSystem::PointPointCollisionTest(RigidBody * rb_a, RigidBody * rb_b)
{
	float radius_sum = rb_a->form.radius + rb_b->form.radius;
	if (SqrdDistance(rb_a->form.transformation.GetPosition(),rb_b->form.transformation.GetPosition()) < radius_sum*radius_sum)
	{
		return true;
	}
	return false;
}

float PhysicSystem::SqrdDistance(Vec2 vec2_a, Vec2 vec2_b)
{
	float xdist = vec2_a.x - vec2_b.x;
	float ydist = vec2_a.y - vec2_b.y;
	return xdist*xdist + ydist*ydist;
}
