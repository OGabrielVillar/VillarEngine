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

			if (!Punit->rigidbody.is_immovable)
			{
				Punit->rigidbody.velocity += Vec2(0.0f, 1000.0f*ft);	//GRAVITY
				Punit->rigidbody.velocity += Punit->rigidbody.force;
				Punit->rigidbody.angularVelocity += Punit->rigidbody.torque;
				Punit->rigidbody.velocity *= AIRRESISTENCE;				//DRAG
				Transformation movement = Transformation(Punit->rigidbody.velocity*ft);
				Vec2 rotation = (Vec2(std::cos(Punit->rigidbody.angularVelocity*ft), std::sin(Punit->rigidbody.angularVelocity*ft)));
				Punit->rigidbody.SetTransformation(movement + Punit->rigidbody.GetTransformation());
				Punit->rigidbody.transformation.orientation = GetRotated(Punit->rigidbody.transformation.orientation, rotation);
				Punit->rigidbody.force.Set(0.0f, 0.0f);
			}

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
		rb0contacts[0] = (contact_point - collision_point).Normalize()*rb1.form.GetRadius( )+ collision_point;
		rb1contacts[0] = (collision_point - contact_point).Normalize()*rb0.form.GetRadius() + contact_point;
		contact_count = 1;
		return true;
	}
	return false;
}

bool PhysicSystem::PointLineCollisionTest(RigidBody & rb0, RigidBody & rb1)
{
	RigidBody* point_in;
	RigidBody* line_in;
	if (rb0.form.GetType() == Form::Type::Point)
	{
		point_in = &rb0;
		line_in = &rb1;
		if (rb1.form.GetType() != Form::Type::Line)
		{
			//ERROR PointLineCollision with non line circle rbs
			return false;
		}
	} else if (rb0.form.GetType() == Form::Type::Line)
	{
		point_in = &rb1;
		line_in = &rb0;
		if (rb1.form.GetType() != Form::Type::Point)
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
		if (point_in == &rb0)
		{
			contact_point = point_final_point;
			collision_point = line_final_point;

			rb0contacts[0] = (contact_point - collision_point).Normalize()*rb1.form.GetRadius() + collision_point;
			rb1contacts[0] = (collision_point - contact_point).Normalize()*rb0.form.GetRadius() + contact_point;
			contact_count = 1;
			return true;
		}
		else
		{
			contact_point = line_final_point;
			collision_point = point_final_point;

			rb0contacts[0] = (contact_point - collision_point).Normalize()*rb1.form.GetRadius() + collision_point;
			rb1contacts[0] = (collision_point - contact_point).Normalize()*rb0.form.GetRadius() + contact_point;
			contact_count = 1;
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

void PhysicSystem::Collision(RigidBody * rb0, RigidBody * rb1)
{

	contact_count = 0;

	//RETURN IF RIGID BODY 0 IS STOPPED
	if (rb0->velocity.LenSqr() <= 0.0f) { return; }

	if (rb0->form.IsCircle())
	{
		if (rb1->form.IsCircle()) {
			if (!PointPointCollisionTest(*rb0, *rb1)) { return; }
		}
		if (rb1->form.GetType() == Form::Type::Line) {
			if (!PointLineCollisionTest(*rb0, *rb1)) { return; }
		}
		if (rb1->form.GetType() == Form::Type::Curve3P)
		{
			return;
			if (!PointCurve3PCollisionTest(*rb0, *rb1)) { return; }
		}

	}
	if (rb0->form.GetType() == Form::Type::Line)
	{
		if (rb1->form.IsCircle()) {
			if (!PointLineCollisionTest(*rb0, *rb1)) { return; }
		}
		if (rb1->form.GetType() == Form::Type::Line) {
			return;
		}
		if (rb1->form.GetType() == Form::Type::Curve3P)
		{
			return;
		}
	}
	if (rb0->form.GetType() == Form::Type::Curve3P)
	{
		return;
		if (rb1->form.IsCircle()) {
			if (!PointCurve3PCollisionTest(*rb1, *rb0)) { return; }
		}
		if (rb1->form.GetType() == Form::Type::Line) {
			return;
		}
		if (rb1->form.GetType() == Form::Type::Curve3P)
		{
			return;
		}
	}
	//RETURN IF VELOCITY ISEN'T IN RB1 DIRECTION
	if (Dot(rb0->velocity, collision_point - contact_point) <= 0) { return; }

	ForceTransmission(*rb0, *rb1);
}

void PhysicSystem::InvertedForceTransmission(RigidBody & rb0, RigidBody & rb1)
{
	float energy_transference = rb1.mass / rb0.mass;
	if (energy_transference > 1.0f)
	{
		energy_transference = 1.0f;
	}
	Vec2 force;
	Vec2 velocity = rb0.velocity*(rb0.mass*(ft*ft));
	if (rb0.form.GetType() == Form::Type::Point) {
		force = GetReflectedForce(velocity, GetRotated90(rb0.GetVerticePos(0) - collision_point));
	}
	else
	{
		force = GetReflectedForce(velocity, GetRotated90(collision_point - rb1.GetVerticePos(0)));
	}
	//How much of rb0.velocity is going to the rb1 direction.
	rb0.AddForce(force * energy_transference);
	//Remove that force from rb0.
	float velocityL = velocity.Len();
	float final_velL = (velocity - force).Len();
	//The rb0 velocity lenght after the collision.
	float factor = (velocityL - final_velL) / force.Len();
	//0.0 to 1.0, how much of force was transfered.
	rb1.AddForce(force * factor * energy_transference);
	//Add the force that was transfered.
	ThereWasCollision = true;
}

void PhysicSystem::ForceTransmission(RigidBody & rb0, RigidBody & rb1)
{
	//Corrects the penetration
	Vec2 position_slope = (rb0contacts[0] - rb1contacts[0]);
	rb0.SetPosition(rb0.GetPosition() + position_slope);

	Vec2 p0_to_p1 = collision_point - contact_point;
	Vec2 normal_angle = p0_to_p1.GetNormalized();
	Vec2 tangent_angle = GetRotated90(normal_angle);
	
	// Calculate average restitution
	e = std::fmin(rb0.restitution, rb1.restitution);

	// Calculate static and dynamic friction
	sf = std::sqrt(rb0.staticFriction * rb0.staticFriction);
	df = std::sqrt(rb0.dynamicFriction * rb0.dynamicFriction);


	for (int i = 0; i < contact_count; i++)
	{
		// Calculate radii from COM to contact
		Vec2 ra = rb0contacts[i] - rb0.GetCOM();
		Vec2 rb = rb0contacts[i] - rb1.GetCOM();

		// Relative velocity
		Vec2 rv = rb1.velocity + Cross(rb1.angularVelocity, rb) -
			rb0.velocity - Cross(rb0.angularVelocity, ra);

		// Relative velocity along the normal_angle
		float contactVel = Dot(rv, normal_angle);

		// Do not resolve if velocities are separating
		if (contactVel > 0)
			return;

		float raCrossN = Cross(ra, normal_angle);
		float rbCrossN = Cross(rb, normal_angle);
		float invMassSum = rb0.inv_mass + rb1.inv_mass + Sqr(raCrossN) * rb0.inv_inertia + Sqr(rbCrossN) * rb1.inv_inertia;

		// Calculate impulse scalar
		float j = -(1.0f + e) * contactVel;
		j /= invMassSum;
		j /= (float)contact_count;

		// Apply impulse
		Vec2 impulse = normal_angle * j;
		rb0.AddForce(-impulse, ra);
		rb1.AddForce(impulse, rb);

		// Friction impulse
		rv = rb1.velocity + Cross(rb1.angularVelocity, rb) -
			rb0.velocity - Cross(rb0.angularVelocity, ra);

		Vec2 t = rv - (normal_angle * Dot(rv, normal_angle));
		t.Normalize();

		// j tangent magnitude
		float jt = -Dot(rv, t);
		jt /= invMassSum;
		jt /= (float)contact_count;

		// Don't apply tiny friction impulses
		if (jt == 0.0f)
			return;

		// Coulumb's law
		Vec2 tangentImpulse;
		if (std::abs(jt) < j * sf)
			tangentImpulse = t * jt;
		else
			tangentImpulse = t * -j * df;

		// Apply friction impulse
		rb0.AddForce(-tangentImpulse, ra);
		rb1.AddForce(tangentImpulse, rb);
	}

	rb0.arecolliding = true;
	rb1.arebeinghit = true;

	rb0.howmanyhits++;
	rb1.howmanyhits++;
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