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
						//How much of rb0.velocity is going to the rb1 direction.
				rbP0->AddForce(-force);

				double velocityL = rbP0->velocity.Len();
						//Remove that force from rb0.
				double final_velocityL = (rbP0->velocity - force).Len();
						//The velocity of rb0 after the collision.
				double factor = (velocityL-final_velocityL) / force.Len();
						//0.0 to 1.0, how much of force was transfered.
				Vec2 force_transf = (force * factor);
				rbP1->AddForce(force_transf);
						//Add the force that was transfered.


				/*TestPorposes*/
				Vec2 _vel[2];
				float _velL[2];
				Vec2 _vel_f[2];
				float _vel_fL[2];
				float _eficL[2];
				float _forceL			= force.Len();			//Force lenght.
				float _force_transfL	= force_transf.Len();	//Force * Transferation Factor lenght.
				_vel[0]			= rbP0->velocity;				//RigidBody0 velocity.
				_velL[0]		= _vel[0].Len();				//RigidBody0 velocity lenght.
				_vel_f[0]		= (_vel[0] - force);			//RigidBody0 final velocity(after the collision).
				_vel_fL[0]		= _vel_f[0].Len();				//RigidBody0 final velocity lenght.
				_eficL[0]		= _vel_fL[0] / _velL[0];		//Rigidbody0 eficience(how much force has changed after the collision).
				_vel[1]			= rbP1->velocity;				//RigidBody1 velocity.
				_velL[1]		= _vel[1].Len();				//RigidBody1 velocity lenght.
				_vel_f[1]		= (_vel[1] + force_transf);		//RigidBody1 final velocity.
				_vel_fL[1]		= _vel_f[1].Len();				//RigidBody1 final velocity lenght.
				_eficL[1]		= _vel_fL[1] / _velL[1];		//Rigidbody0 eficience(how much force has changed after the collision).
				float _total_eficienceL =  (_vel_fL[0] + _vel_fL[1]) / (_velL[0] + _velL[1]);
				//Store in Log
				for (size_t i = 0; i <= 1; i++)
				{
					log.push_back("    [");
					log.back() += std::to_string(i);
					log.back() += "]Initial Velocity = ";
					log.back() += std::to_string(_vel[i].x);
					log.back() += ", ";
					log.back() += std::to_string(_vel[i].y);
					log.back() += "(";
					log.back() += std::to_string(_velL[i]);
					log.back() += "); ";

					log.push_back("    Final Velocity = ");
					log.back() += std::to_string(_vel_f[i].x);
					log.back() += ", ";
					log.back() += std::to_string(_vel_f[i].y);
					log.back() += "(";
					log.back() += std::to_string(_vel_fL[i]);
					log.back() += "); ";

					log.back() += "  Eficience = ";
					log.back() += std::to_string(_eficL[i]);
					log.back() += ";";
				}
				log.push_back("Total Eficiente = ");
				log.back() += std::to_string(_total_eficienceL);
				log.back() += "; Force: ";
				log.back() += std::to_string(_forceL);
				log.back() += "; Force Transfered: ";
				log.back() += std::to_string(_force_transfL);
				log.back() += ";";

				char x = 0;
				//TestEnd*/
			}
		}
	}
}

Vec2 PhysicSystem::GetReflectedForce(Vec2 v_in, Vec2 w_in)
{
	Vec2 wN = w_in.GetNormalized();
	return v_in - Dot(v_in, wN)*wN;
}