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
	ThereWasCollision = false;

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
			if (ThereWasCollision)
			{
				Vec2 _force = Punit->rigidbody.force;
				float _forceL = _force.Len();
				Vec2 _force_mod = Punit->rigidbody.force / 2;
				float _force_modL = _force_mod.Len();
				Vec2 _velocity = Punit->rigidbody.velocity;
				float _velocityL = _velocity.Len();
				Vec2 _final_velocity = _velocity + _force_mod;
				float _final_velocityL = _final_velocity.Len();

				log.push_back("Velocity: ");
				log.back() += std::to_string(_velocityL);
				log.back() += ";  Force: ";
				log.back() += std::to_string(_forceL);
				log.back() += ";  Force Modified: ";
				log.back() += std::to_string(_force_modL);
				log.back() += ";  Final Vel: ";
				log.back() += std::to_string(_final_velocityL);

				int x = 0;
			}

			//Punit->rigidbody.velocity += Vec2(0.0f, 100.0f*ft);	//GRAVITY
			Punit->rigidbody.velocity += Punit->rigidbody.force / (Punit->rigidbody.mass*(ft*ft));
			Punit->rigidbody.SetTransformation(Punit->rigidbody.GetTransformation() + Punit->rigidbody.GetVelocity()*ft);
			Punit->rigidbody.force.Set(0.0f, 0.0f);
		}
		Punit++;
	}
}

bool PhysicSystem::IsCollinding(RigidBody * rb_a, RigidBody * rb_b)
{
	if (rb_a->form.GetType() == Form::Type::Point)
	{
		if (rb_b->form.GetType() == Form::Type::Point)
		{

		}
	}
	return false;
}

bool PhysicSystem::PointPointCollisionTest(RigidBody& rb_a, RigidBody& rb_b)
{
	float radius_sum = rb_a.form.GetRadius() + rb_b.form.GetRadius();
	if (SqrdDistance(rb_a.GetVerticePos(0), rb_b.GetVerticePos(0)) <= radius_sum*radius_sum)
	{
		contact_point = rb_b.GetVerticePos(0);
		return true;
	}
	return false;
}

bool PhysicSystem::PointLineCollisionTest(RigidBody & rb_a, RigidBody & line_in)
{
	Vec2 c0 = rb_a.GetVerticePos(0);
	Vec2 p0 = line_in.GetVerticePos(0);
	Vec2 p1 = line_in.GetVerticePos(1);

	//Make an Matrix, inverted rotating the entire elements on the p0 axis
	Vec2 angleFromP0toP1 = line_in.GetVerticeOri(0);
	Vec2 c0_inMatrix = GetRotated( c0 - p0 , GetYInvertedAngle(angleFromP0toP1));
	Vec2 p1_inMatrix = GetRotated( p1 - p0, GetYInvertedAngle(angleFromP0toP1));
	
	float radius_sum = rb_a.form.GetRadius() + line_in.form.GetRadius();
	//RETURN IF THE CIRCLE ISN'T IN THE LINE:
	if (!(c0_inMatrix.y*c0_inMatrix.y <= radius_sum * radius_sum))
	{
		return false;
	}

	//CHECK IF CIRCLE IS IN THE LINE SECTION, RETURN IF IT DOESN'T:
	if (c0_inMatrix.x < 0.0f) //IF IS BEFORE THE SECTION
	{
		if (SqrdDistance(c0_inMatrix, Vec2()) <= radius_sum * radius_sum)
		{
			contact_point = p0;
			return true;
		}
		return false;
	}
	else if (c0_inMatrix.x > p1_inMatrix.x) //IF IS AFTER THE SECTION
	{
		if (SqrdDistance(c0_inMatrix, p1_inMatrix) <= radius_sum * radius_sum)
		{
			contact_point = p1;
			return true;
		}
		return false;
	}
	else		//TRANSFERS THE DATA BACK TO NON-MATRIX
	{

		contact_point = p0 + GetRotated(Vec2(c0_inMatrix.x, 0.0f), angleFromP0toP1);
		return true;
	}
}

float PhysicSystem::SqrdDistance(Vec2 vec2_a, Vec2 vec2_b)
{
	float xdist = vec2_a.x - vec2_b.x;
	float ydist = vec2_a.y - vec2_b.y;
	return xdist*xdist + ydist*ydist;
}

void PhysicSystem::Collision(RigidBody * rbP0, RigidBody * rbP1)
{
	//RETURN IF RIGID BODY 0 IS STOPPED
	if (rbP0->velocity.LenSqr() <= 0.0f) { return; }

	if (rbP0->form.IsCircle())
	{
		if (rbP1->form.IsCircle()) {
			if (!PointPointCollisionTest(*rbP0, *rbP1)) { return; }
		}
		if (rbP1->form.GetType() == Form::Type::Line) {
			if (!PointLineCollisionTest(*rbP0, *rbP1)) { return; }
		}
		//RETURN IF VELOCITY ISEN'T IN RB1 DIRECTION
		if (Dot(rbP0->velocity, contact_point - rbP0->GetVerticePos(0)) <= 0) { return; }

		float mass_factor = rbP1->mass / rbP0->mass;
		if (mass_factor > 1.0f)
		{
			mass_factor = 1.0f;
		}
		Vec2 velocity = rbP0->velocity*(rbP0->mass*(ft*ft));
		Vec2 force = GetReflectedForce(velocity, GetRotated90(rbP0->GetVerticePos(0) - contact_point));
		//How much of rb0.velocity is going to the rb1 direction.
		rbP0->AddForce(-force * mass_factor);
		//Remove that force from rb0.
		float velocityL = velocity.Len();
		float final_velL = (velocity - force).Len();
		//The rb0 velocity lenght after the collision.
		float factor = (velocityL - final_velL) / force.Len();
		//0.0 to 1.0, how much of force was transfered.
		rbP1->AddForce(force * factor * mass_factor);
		//Add the force that was transfered.
		ThereWasCollision = true;

		/*/TestPorposes

					Vec2 _vel[2];
					float _velL[2];
					Vec2 _vel_f[2];
					float _vel_fL[2];
					float _eficL[2];
					float _eficL2[2];
					float _forceL			= force.Len();				//Force lenght.
					float _force_transfL	= (force * factor).Len();	//Force * Transferation Factor lenght.
					_vel[0]			= velocity;							//RigidBody0 velocity.
					_velL[0]		= _vel[0].Len();					//RigidBody0 velocity lenght.
					_vel_f[0]		= (_vel[0] - force);				//RigidBody0 final velocity(after the collision).
					_vel_fL[0]		= _vel_f[0].Len();					//RigidBody0 final velocity lenght.
					_eficL[0]		= _vel_fL[0] / _velL[0];			//Rigidbody0 eficience(how much force has changed after the collision).
					_eficL2[0]		= (_velL[0] - _vel_fL[0])/_forceL;	//x
					_vel[1]			= rbP1->velocity;					//RigidBody1 velocity.
					_velL[1]		= _vel[1].Len();					//RigidBody1 velocity lenght.
					_vel_f[1]		= (_vel[1] + (force * factor));		//RigidBody1 final velocity.
					_vel_fL[1]		= _vel_f[1].Len();					//RigidBody1 final velocity lenght.
					_eficL[1]		= _vel_fL[1] / _velL[1];			//Rigidbody0 eficience(how much force has changed after the collision).
					_eficL2[1]		= (_velL[1] - _vel_fL[1])/_forceL;	//x
					float _energy_lost = _velL[0] - (_vel_fL[0] + _force_transfL);
					log.push_back("Lost Energy: ");
					log.back() += std::to_string(_energy_lost);
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

						log.back() += "  Factor = ";
						log.back() += std::to_string(_eficL2[i]);
						log.back() += ";";
					}
					log.push_back("Total Eficiente = ");
					log.back() += std::to_string(_energy_lost);
					log.back() += "; Force: ";
					log.back() += std::to_string(_forceL);
					log.back() += "; Force Transfered: ";
					log.back() += std::to_string(_force_transfL);
					log.back() += ";";
					if (_energy_lost!=0.0f)
					{
						int x = 0;
					}
					//TestEnd*/

	}
	if (rbP0->form.GetType() == Form::Type::Line)
	{
		if (rbP1->form.IsCircle()) {
			if (!PointLineCollisionTest(*rbP1, *rbP0)) { return; }
		}
		if (rbP1->form.GetType() == Form::Type::Line) {
			return;
		}
		//RETURN IF VELOCITY ISEN'T IN RB1 DIRECTION
		if (Dot(rbP0->velocity, rbP1->GetVerticePos(0) - contact_point) <= 0) { return; }

		float mass_factor = rbP1->mass / rbP0->mass;
		if (mass_factor > 1.0f)
		{
			mass_factor = 1.0f;
		}
		Vec2 velocity = rbP0->velocity*(rbP0->mass*(ft*ft));
		Vec2 force = GetReflectedForce(velocity, GetRotated90(contact_point - rbP1->GetVerticePos(0)));
		//How much of rb0.velocity is going to the rb1 direction.
		rbP0->AddForce(-force * mass_factor);
		//Remove that force from rb0.
		float velocityL = velocity.Len();
		float final_velL = (velocity - force).Len();
		//The rb0 velocity lenght after the collision.
		float factor = (velocityL - final_velL) / force.Len();
		//0.0 to 1.0, how much of force was transfered.
		rbP1->AddForce(force * factor * mass_factor);
		//Add the force that was transfered.
		ThereWasCollision = true;

		/*/TestPorposes

					Vec2 _vel[2];
					float _velL[2];
					Vec2 _vel_f[2];
					float _vel_fL[2];
					float _eficL[2];
					float _eficL2[2];
					float _forceL			= force.Len();				//Force lenght.
					float _force_transfL	= (force * factor).Len();	//Force * Transferation Factor lenght.
					_vel[0]			= velocity;							//RigidBody0 velocity.
					_velL[0]		= _vel[0].Len();					//RigidBody0 velocity lenght.
					_vel_f[0]		= (_vel[0] - force);				//RigidBody0 final velocity(after the collision).
					_vel_fL[0]		= _vel_f[0].Len();					//RigidBody0 final velocity lenght.
					_eficL[0]		= _vel_fL[0] / _velL[0];			//Rigidbody0 eficience(how much force has changed after the collision).
					_eficL2[0]		= (_velL[0] - _vel_fL[0])/_forceL;	//x
					_vel[1]			= rbP1->velocity;					//RigidBody1 velocity.
					_velL[1]		= _vel[1].Len();					//RigidBody1 velocity lenght.
					_vel_f[1]		= (_vel[1] + (force * factor));		//RigidBody1 final velocity.
					_vel_fL[1]		= _vel_f[1].Len();					//RigidBody1 final velocity lenght.
					_eficL[1]		= _vel_fL[1] / _velL[1];			//Rigidbody0 eficience(how much force has changed after the collision).
					_eficL2[1]		= (_velL[1] - _vel_fL[1])/_forceL;	//x
					float _energy_lost = _velL[0] - (_vel_fL[0] + _force_transfL);
					log.push_back("Lost Energy: ");
					log.back() += std::to_string(_energy_lost);
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

						log.back() += "  Factor = ";
						log.back() += std::to_string(_eficL2[i]);
						log.back() += ";";
					}
					log.push_back("Total Eficiente = ");
					log.back() += std::to_string(_energy_lost);
					log.back() += "; Force: ";
					log.back() += std::to_string(_forceL);
					log.back() += "; Force Transfered: ";
					log.back() += std::to_string(_force_transfL);
					log.back() += ";";
					if (_energy_lost!=0.0f)
					{
						int x = 0;
					}
					//TestEnd*/
	}
}

Vec2 PhysicSystem::GetReflectedForce(Vec2 v_in, Vec2 w_in)
{
	//v_in = velocity;
	//w_in = angle;

	//NORMALIZE THE ANGLE
	Vec2 wN = w_in.GetNormalized();

	//GET REFLECTED ANGLE FORMULA
	return v_in - Dot(v_in, wN)*wN;
}