#include "RigidBody.h"

RigidBody::RigidBody()
{
}

RigidBody::RigidBody(Transformation transformation_in)
{
	SetTransformation(transformation_in);
}

RigidBody::RigidBody(Transformation transformation_in, Form form_in)
	:
	form(form_in)
{
	SetTransformation(transformation_in);
}

RigidBody::RigidBody(Form * form_in, unsigned int x, unsigned int y)
//: form(form_in->Clone())
{
	//form->rigidbody = this;
	SetTransformation(Vec2((float)x, (float)y));
	velocity.Set(0, 0);
	angularVelocity = 0;
	torque = 0;
	//orient = Random(-PI, PI);
	force.Set(0, 0);
	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	//form->Initialize();
}

void RigidBody::SetTransformation(Transformation transformation_in)
{
	transformation = transformation_in;
}


void RigidBody::SetVelocity(Vec2 velocity_in)
{
	velocity = velocity_in;
}

void RigidBody::SetForm(Form Form_in)
{
	form = Form_in;
}

void RigidBody::SetFormRadius(float float_in)
{
	if (float_in < 0.1)
	{
		return;
	}
	form.SetRadius(float_in);
	UpdateMass();
}

void RigidBody::SetDensity(float density_in)
{
	density = density_in;
	UpdateMass();
}

void RigidBody::UpdateMass()
{
	if (form.type == Form::Type::Line)
	{
		mass = (PI * (form.radius) * (form.radius) * density) + form.radius * form.vertices[0].Len();
		return;
	}
	mass = PI * (form.radius) * (form.radius) * density;
}

Transformation RigidBody::GetTransformation()
{
	return transformation;
}

Vec2 RigidBody::GetVerticePos(int vertice_index)
{
	return form.vertices[vertice_index] + transformation.GetPosition();
}


Vec2 RigidBody::GetVelocity()
{
	return velocity;
}

Vec2 RigidBody::GetForce()
{
	return force;
}

void RigidBody::AddForce(Vec2 force_in)
{
	force += force_in;
}

void RigidBody::ApplyForces()
{
	ClearForces();
}

void RigidBody::ClearForces()
{
	force.Set(0.0f,0.0f);
}

void RigidBody::ApplyImpulse(const Vec2 & impulse, const Vec2 & contactVector)
{
	velocity += im * impulse;
	angularVelocity += iI * Cross(contactVector, impulse);
}

void RigidBody::SetStatic(void)
{
	I = 0.0f;
	iI = 0.0f;
	m = 0.0f;
	im = 0.0f;
}

void RigidBody::SetOrientation(float radians)
{
	orient = radians;
	//form.SetOrientation(radians);
}
