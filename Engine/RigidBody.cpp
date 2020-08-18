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

void RigidBody::SetTransformation(const Transformation& transformation_in)
{
	transformation = transformation_in;
}

void RigidBody::SetPosition(const Vec2& position_in)
{
	transformation.SetPosition(position_in);
}


void RigidBody::SetVelocity(const Vec2& velocity_in)
{
	velocity = velocity_in;
}

void RigidBody::SetForm(const Form& Form_in)
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
	if (form.GetType() == Form::Type::Line)
	{
		mass = ((PI * form.GetRadius() * form.GetRadius() * density) + form.GetRadius() * form.GetVertice(1).GetPosition().Len()) * MASSFACTOR;
		inertia = ((PI * mass * form.GetRadius() * form.GetRadius()) + form.GetRadius() * form.GetVertice(1).GetPosition().Len()) * MASSFACTOR;
	}
	else if (true)
	{
		mass = PI * (form.GetRadius()) * (form.GetRadius()) * density * MASSFACTOR;
		inertia = mass * form.GetRadius() * form.GetRadius() * MASSFACTOR;
	}
	inv_mass = 1.0f / mass;
	inv_inertia = 1.0f / inertia;
	if (is_immovable)
	{
		inv_mass = 0.0f / mass;
		inv_inertia = 0.0f / inertia;
	}
}

void RigidBody::UpdateTransformation()
{

}

void RigidBody::MoveVerticeTo(int index, Vec2 position_in)
{
	form.MoveVerticeTo(index, (transformation - Transformation(position_in)).GetPosition() + form.GetCentralPoint());
}

Transformation RigidBody::GetTransformation()
{
	return transformation;
}

Vec2 RigidBody::GetVerticePos(int vertice_index)
{
	return (transformation + (form.GetVertice(vertice_index)-form.GetCentralPoint())).GetPosition();
}

Vec2 RigidBody::GetVerticeOri(int vertice_index)
{
	return GetRotated(form.GetVertice(vertice_index).GetOrientation(),transformation.GetOrientation());
}

Transformation RigidBody::GetVertice(int vertice_index) const
{
	return form.GetVertice(vertice_index);
}

Vec2 RigidBody::GetVelocity()
{
	return velocity;
}

Vec2 RigidBody::GetPosition()
{
	return transformation.GetPosition();
}

Vec2 RigidBody::GetForce()
{
	return force;
}

Vec2 RigidBody::GetCOM()
{
	return GetTransformation().GetPosition();
}

void RigidBody::AddForce(Vec2 & const force_in)
{
	force += force_in;
}

void RigidBody::AddForce(Vec2& const force_in, Vec2& const contactpoint_in)
{
	velocity += inv_mass * force_in;
	angularVelocity += inv_inertia * Cross(contactpoint_in, force_in);
}

void RigidBody::ApplyForces()
{
	ClearForces();
}

void RigidBody::ClearForces()
{
	force.Set(0.0f,0.0f);
}

void RigidBody::SetOrientation(float radians)
{
}
