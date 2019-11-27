#include "PhysicSystem.h"

PhysicSystem::PhysicSystem(Unit * units_in)
{
	Punit = units_in;
}

void PhysicSystem::Go()
{
	MoveBodys();
}

void PhysicSystem::MoveBodys()
{
	for (int i = 0; i < UNITSLIMIT; i++)
	{
		if (!Punit->GetName().empty())
		{
			Punit->rigidbody.ApplyForces();
			Punit->rigidbody.SetTransformation(Punit->rigidbody.GetTransformation() + Punit->rigidbody.GetVelocity());
		}
		Punit++;
	}
	Punit -= UNITSLIMIT;
}
