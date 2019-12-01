#include "PhysicSystem.h"

PhysicSystem::PhysicSystem(Unit * unitgroup_in)
{
	Punitgroup = unitgroup_in;
}

void PhysicSystem::Go(float ft_in)
{
	ft = ft_in;
	MoveBodys();
}

void PhysicSystem::MoveBodys()
{
	Unit* Punit;
	Punit = Punitgroup;

	while (Punit != Punitgroup + UNITSLIMIT - 1)
	{
		if (!Punit->GetName().empty())
		{

			Unit* PunitInteration;
			PunitInteration = Punit+1;
			while (PunitInteration != Punitgroup + UNITSLIMIT - 1)
			{
				if (!PunitInteration->GetName().empty())
				{
					Collision(&Punit->rigidbody,&PunitInteration->rigidbody);
					Collision(&PunitInteration->rigidbody, &Punit->rigidbody);
				}
				PunitInteration++;
			}
		}
		Punit++;
	}
	Punit = Punitgroup;
	while (Punit != Punitgroup + UNITSLIMIT - 1)
	{
		if (!Punit->GetName().empty())
		{
			Punit->rigidbody.velocity += Punit->rigidbody.force/Punit->rigidbody.mass;//divided by the mass
			Punit->rigidbody.SetTransformation(Punit->rigidbody.GetTransformation() + Punit->rigidbody.GetVelocity()*ft);
			Punit->rigidbody.force.Set(0.0f, 0.0f);
		}
		Punit++;
	}
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

bool PhysicSystem::PointPointCollisionTest(Form& form_a, Form& form_b)
{
	float radius_sum = form_a.radius + form_b.radius;
	if (SqrdDistance(form_a.GetPosition(), form_b.GetPosition()) <= radius_sum*radius_sum)
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

void PhysicSystem::Collision(RigidBody * rbP0, RigidBody * rbP1)
{
	if (Dot(rbP0->velocity, rbP1->form.GetPosition() - rbP0->form.GetPosition()) <= 0)
	{ return; }
	if (rbP0->velocity.LenSqr() <= 0.0f)
	{ return; }

	if (rbP0->form.IsCircle()) {
		if (rbP1->form.IsCircle()) {
			if (PointPointCollisionTest(rbP0->form, rbP1->form)) {
				Vec2 force = GetReflectedForce(rbP0->velocity, GetRotated90(rbP0->form.GetPosition() - rbP1->form.GetPosition()));
				rbP0->AddForce(-force);
				Vec2 final_velocity = rbP0->velocity - force;
				float factor = 1.0f - (final_velocity.LenSqr() / rbP0->velocity.LenSqr());
				Vec2 force_transf = force * factor;
				rbP1->AddForce(force_transf);
			}
		}
	}
}

Vec2 PhysicSystem::GetReflectedForce(Vec2 v_in, Vec2 w_in)
{
	Vec2 wN = w_in.GetNormalized();
	return v_in - Dot(v_in, wN)*wN;
}