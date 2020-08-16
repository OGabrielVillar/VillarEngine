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

	Unit* Punitb;
	Punitb = Punitgroup;
	while (Punitb != Punitgroup + UNITSLIMIT - 1)
	{
		if (!Punitb->GetName().empty()){
			Punitb->rigidbody.arecolliding = false;
			Punitb->rigidbody.arebeinghit = false;
			Punitb->rigidbody.howmanyhits = 0;
		}
		Punitb++;
	}
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

	bool _ithappens = false;
	float _totalenergybefore = 0.0f;
	float _totalenergyafter = 0.0f;
	while (Punit != Punitgroup + UNITSLIMIT - 1)
	{
		if (!Punit->GetName().empty())
		{
			_totalenergybefore += Punit->rigidbody.velocity.Len()*Punit->rigidbody.mass;

			//Punit->rigidbody.velocity += Vec2(0.0f, 100.0f*ft);	//GRAVITY
			//Punit->rigidbody.velocity += Punit->rigidbody.force / (Punit->rigidbody.mass*(ft*ft));
			Punit->rigidbody.velocity += Punit->rigidbody.force;
			Punit->rigidbody.SetTransformation(Transformation(Punit->rigidbody.GetVelocity()*ft) + Punit->rigidbody.GetTransformation());
			Punit->rigidbody.force.Set(0.0f, 0.0f);

			_totalenergyafter += Punit->rigidbody.velocity.Len()*Punit->rigidbody.mass;
			if (Punit->rigidbody.howmanyhits >= 1)
			{
				_ithappens = true;
			}
		}
		Punit++;
	}
	if (_ithappens)
	{
		int i = 0 + 1;
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

bool PhysicSystem::PointPointCollisionTest(RigidBody& rb0, RigidBody& rb1)
{
	float radius_sum = rb0.form.GetRadius() + rb1.form.GetRadius();
	if (SqrdDistance(rb0.GetVerticePos(0), rb1.GetVerticePos(0)) <= radius_sum*radius_sum)
	{
		contact_point = rb0.GetVerticePos(0);
		collision_point = rb1.GetVerticePos(0);
		return true;
	}
	return false;
}

bool PhysicSystem::PointLineCollisionTest(RigidBody & rb_a, RigidBody & rb_b)
{
	RigidBody* point_in;
	RigidBody* line_in;
	if (rb_a.form.GetType() == Form::Type::Point)
	{
		point_in = &rb_a;
		line_in = &rb_b;
		if (rb_b.form.GetType() != Form::Type::Line)
		{
			//ERROR PointLineCollision with non line circle rbs
			return false;
		}
	} else if (rb_a.form.GetType() == Form::Type::Line)
	{
		point_in = &rb_b;
		line_in = &rb_a;
		if (rb_b.form.GetType() != Form::Type::Point)
		{
			//ERROR PointLineCollision with non line circle rbs
			return false;
		}
	}
	else
	{
		//ERROR PointLineCollision with non line circle rbs
		return false;
	}


	Vec2 c0 = point_in->GetVerticePos(0);
	Vec2 p0 = line_in->GetVerticePos(0);
	Vec2 p1 = line_in->GetVerticePos(1);
	Vec2 angleFromP0toP1 = line_in->GetVerticeOri(0);
	float radius_sum_sqrd = point_in->form.GetRadius() + line_in->form.GetRadius();
	radius_sum_sqrd *= radius_sum_sqrd;

	//Make an Matrix, inverted rotating the entire elements on the p0 axis
	Vec2 c0_inMatrix = GetRotated( c0 - p0 , GetInvertedAngle(angleFromP0toP1));
	Vec2 p1_inMatrix = GetRotated( p1 - p0, GetInvertedAngle(angleFromP0toP1));
	
	//RETURN IF THE CIRCLE ISN'T IN THE LINE:
	if (!(c0_inMatrix.y*c0_inMatrix.y <= radius_sum_sqrd))
	{
		return false;
	}
	Vec2 line_final_point;
	Vec2 point_final_point = c0;
	//CHECK IF CIRCLE IS IN THE LINE SECTION, RETURN IF IT DOESN'T:
	if (c0_inMatrix.x < 0.0f) //IF IS BEFORE THE SECTION
	{
		line_final_point = p0;
	}
	else if (c0_inMatrix.x > p1_inMatrix.x) //IF IS AFTER THE SECTION
	{
		line_final_point = p1;
	}
	else		//TRANSFERS THE DATA BACK TO NON-MATRIX
	{

		line_final_point = p0 + GetRotated(Vec2(c0_inMatrix.x, 0.0f), angleFromP0toP1);
	}
	if (SqrdDistance(point_final_point, line_final_point) <= radius_sum_sqrd)
	{
		if (point_in == &rb_a)
		{
			contact_point = point_final_point;
			collision_point = line_final_point;
			return true;
		}
		else
		{
			contact_point = line_final_point;
			collision_point = point_final_point;
			return true;
		}
	}
	return false;
}

bool PhysicSystem::PointCurve3PCollisionTest(RigidBody & rb_a, RigidBody & curve3p_in)
{
	float radius_sum = rb_a.form.GetRadius() + curve3p_in.form.GetRadius();
	Vec2 p0 = curve3p_in.GetVerticePos(0);
	Vec2 p1 = curve3p_in.GetVerticePos(1);
	Vec2 p2 = curve3p_in.GetVerticePos(2);
	int number_of_trys = 6;
	float t0 = 0.0f;					//0.0f~1.0f run paramiter
	float t1 = 0.0f;					//0.0f~1.0f run paramiter
	Vec2 p0_to_p1 = p1 - p0;
	Vec2 p1_to_p2 = p2 - p1;
	Vec2 ip0;						//p0_to_p1 interpollation point
	Vec2 ip1;						//p1_to_p2 interpollation point
	Vec2 ip0_to_ip1;
	Vec2 final;
	Vec2 finalt0;
	Vec2 finalt1;
	if (SqrdDistance(rb_a.GetVerticePos(0), curve3p_in.GetVerticePos(0)) < SqrdDistance(rb_a.GetVerticePos(0), curve3p_in.GetVerticePos(2)))
	{
		t0 = 0.0f;
		t1 = 0.5f;
	}
	else
	{
		t0 = 0.5f;
		t1 = 1.0f;
	}
	for (int i = 0; i < number_of_trys; i++)
	{
		ip0 = p0_to_p1 * t0;
		ip1 = p1_to_p2 * t0;
		ip0_to_ip1 = (ip1 + p1) - (ip0 + p0);
		finalt0 = (ip0_to_ip1 * t0) + ip0 + p0;

		ip0 = p0_to_p1 * t1;
		ip1 = p1_to_p2 * t1;
		ip0_to_ip1 = (ip1 + p1) - (ip0 + p0);
		finalt1 = (ip0_to_ip1 * t1) + ip0 + p0;

		float t = (t0 + t1) / 2.0f;
		if (SqrdDistance(rb_a.GetVerticePos(0), finalt0) < SqrdDistance(rb_a.GetVerticePos(0), finalt1))
		{
			t1 = t;
		}
		else
		{
			t0 = t;
		}
	}
	float t = (t0 + t1) / 2.0f;
	ip0 = p0_to_p1 * t;
	ip1 = p1_to_p2 * t;
	ip0_to_ip1 = (ip1 + p1) - (ip0 + p0);
	final = (ip0_to_ip1 * t) + ip0 + p0;
	if (SqrdDistance(rb_a.GetVerticePos(0), final) <= radius_sum * radius_sum)
	{
		return true;
		collision_point = final;
	}
	return false;
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
		if (rbP1->form.GetType() == Form::Type::Curve3P)
		{
			return;
			if (!PointCurve3PCollisionTest(*rbP0, *rbP1)) { return; }
		}
		//RETURN IF VELOCITY ISEN'T IN RB1 DIRECTION
		if (Dot(rbP0->velocity, collision_point - contact_point) <= 0) { return; }

	}
	if (rbP0->form.GetType() == Form::Type::Line)
	{
		if (rbP1->form.IsCircle()) {
			if (!PointLineCollisionTest(*rbP0, *rbP1)) { return; }
		}
		if (rbP1->form.GetType() == Form::Type::Line) {
			return;
		}
		if (rbP1->form.GetType() == Form::Type::Curve3P)
		{
			return;
		}
		//RETURN IF VELOCITY ISEN'T IN RB1 DIRECTION
		if (Dot(rbP0->velocity, collision_point - contact_point) <= 0) { return; }
	}
	if (rbP0->form.GetType() == Form::Type::Curve3P)
	{
		return;
		if (rbP1->form.IsCircle()) {
			if (!PointCurve3PCollisionTest(*rbP1, *rbP0)) { return; }
		}
		if (rbP1->form.GetType() == Form::Type::Line) {
			return;
		}
		if (rbP1->form.GetType() == Form::Type::Curve3P)
		{
			return;
		}
		//RETURN IF VELOCITY ISEN'T IN RB1 DIRECTION
		if (Dot(rbP0->velocity, collision_point - contact_point) <= 0) { return; }
	}
	ForceTransmission(*rbP0, *rbP1);
}

void PhysicSystem::InvertedForceTransmission(RigidBody & rbP0, RigidBody & rbP1)
{
	float energy_transference = rbP1.mass / rbP0.mass;
	if (energy_transference > 1.0f)
	{
		energy_transference = 1.0f;
	}
	Vec2 force;
	Vec2 velocity = rbP0.velocity*(rbP0.mass*(ft*ft));
	if (rbP0.form.GetType() == Form::Type::Point) {
		force = GetReflectedForce(velocity, GetRotated90(rbP0.GetVerticePos(0) - collision_point));
	}
	else
	{
		force = GetReflectedForce(velocity, GetRotated90(collision_point - rbP1.GetVerticePos(0)));
	}
	//How much of rb0.velocity is going to the rb1 direction.
	rbP0.AddForce(force * energy_transference);
	//Remove that force from rb0.
	float velocityL = velocity.Len();
	float final_velL = (velocity - force).Len();
	//The rb0 velocity lenght after the collision.
	float factor = (velocityL - final_velL) / force.Len();
	//0.0 to 1.0, how much of force was transfered.
	rbP1.AddForce(force * factor * energy_transference);
	//Add the force that was transfered.
	ThereWasCollision = true;
}

void PhysicSystem::ForceTransmission(RigidBody & rbP0, RigidBody & rbP1)
{
	if (rbP0.howmanyhits > 0 ||	rbP1.howmanyhits > 0)
	{
		return;
	}
	/*float energy_transference = rbP1.mass / rbP0.mass;
	//float energy_reflection = 0.0f;
	if (energy_transference > 1.0f)
	{
		energy_reflection = 1.0f - rbP0.mass / rbP1.mass;
		energy_transference = 1.0f;
	}
	if (rbP1.is_immovable == true)
	{
		energy_transference = 1.0f;
		energy_reflection = 1.0f;
	}*/
	//Vec2 velocity = rbP0.velocity*(rbP0.mass*(ft*ft));
	//Vec2 p0_to_p1 = collision_point - contact_point;
	Vec2 p0_to_p1 =  contact_point - collision_point;
	Vec2 normal_angle = p0_to_p1.GetNormalized();
	Vec2 tangent_angle = GetRotated90(normal_angle);
	//Vec2 force_in_matrix = GetRotated(rbP0.velocity, GetInvertedAngle(normal_angle));
	//float force_in_matrix_x = force_in_matrix.x*(rbP0.mass);
	//Vec2 force = GetRotated(force_in_matrix_x, normal_angle);
	//rbP0.AddForce(-(force * energy_transference) - (force * energy_reflection));
	//rbP1.AddForce(force * energy_transference - (force * energy_reflection));

	float dpTan1 = Dot(rbP0.velocity, tangent_angle);
	float dpNorm1 = Dot(rbP0.velocity, normal_angle);
	float m1 = (rbP0.mass - rbP1.mass) / (rbP0.mass + rbP1.mass)*dpNorm1;
	float m2 = (2.0f*rbP0.mass) / (rbP0.mass + rbP1.mass)*dpNorm1;

	Vec2 final_force0 = tangent_angle * dpTan1 + normal_angle * m1;
	Vec2 final_force1 = normal_angle * m2;

	//rbP0.velocity = final_force0;
	//rbP1.velocity = final_force1;

	rbP0.AddForce(final_force0 - rbP0.velocity);
	rbP1.AddForce(final_force1);

	float inicialvelocity0 = rbP0.velocity.Len()*rbP0.mass;
	float inicialvelocity1 = rbP1.velocity.Len()*rbP1.mass;

	float finalvelocity0 = final_force0.Len()*rbP0.mass;
	float finalvelocity1 = final_force1.Len()*rbP1.mass;

	rbP0.arecolliding = true;
	rbP1.arebeinghit = true;

	rbP0.howmanyhits++;
	rbP1.howmanyhits++;
	ThereWasCollision = true;

	/*/ TestPorposes

				Vec2 _vel[2];
				float _velL[2];
				Vec2 _vel_f[2];
				float _vel_fL[2];
				float _eficL[2];
				float _eficL2[2];
				Vec2 _force				= force/rbP0.mass;
				float _forceL			= _force.Len();				//Force lenght.
				float _force_transfL	= (_force * energy_transference).Len();	//Force * Transferation Factor lenght.
				_vel[0]			= rbP0.velocity;					//RigidBody0 velocity.
				_velL[0]		= _vel[0].Len();					//RigidBody0 velocity lenght.
				_vel_f[0]		= (_vel[0] - _force * energy_transference);				//RigidBody0 final velocity(after the collision).
				_vel_fL[0]		= _vel_f[0].Len();					//RigidBody0 final velocity lenght.
				_eficL[0]		= _vel_fL[0] / _velL[0];			//Rigidbody0 eficience(how much force has changed after the collision).
				_eficL2[0]		= (_velL[0] - _vel_fL[0])/_forceL;	//x
				_vel[1]			= rbP1.velocity;					//RigidBody1 velocity.
				_velL[1]		= _vel[1].Len();					//RigidBody1 velocity lenght.
				_vel_f[1]		= (_vel[1] + (_force * energy_transference));		//RigidBody1 final velocity.
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
				if (_energy_lost>=0.1f)
				{
					int x = 0;
				}
				//TestEnd*/
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


float PhysicSystem::SqrdDistance(Vec2 vec2_a, Vec2 vec2_b)
{
	float xdist = vec2_a.x - vec2_b.x;
	float ydist = vec2_a.y - vec2_b.y;
	return xdist * xdist + ydist * ydist;
}