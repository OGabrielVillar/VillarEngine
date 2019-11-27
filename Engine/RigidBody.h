#pragma once

#define NFORCESLIMIT 9

#include "CircleForm.h"
#include "UnitToBodyAttachment.h"

class RigidBody
{
public:
	RigidBody();
	RigidBody(Transformation transformation_in, float mass_in);
	RigidBody(Transformation transformation_in, float mass_in, Transformation& unitTransformation_in);
public: //SETTERS
	void SetTransformation(Transformation transformation_in);
	void SetMass(float mass_in);
	void SetUnitTransformationAttached(Transformation* unitTransformation_in);
	void SetVelocity(Vec2 velocity_in);
	void SetAcceleration(Vec2 acceleration_in);
	void SetCircleForm(CircleForm circleform_in);
public: //GETTERS
	Transformation GetTransformation();
	float GetMass();
	Vec2 GetVelocity();
	Vec2 GetAcceleration();
	Vec2 GetFinalForce();
public: //FUNCTIONS
	void AddForce(Vec2 force_in);
	void ApplyForces();
	void ClearForces();
private:
	float mass = 1;
	Vec2 velocity;
	Vec2 acceleration;
	CircleForm form;
	UnitToBodyAttachment unitAttached;
	bool uses_gravity;
	Vec2 forces[NFORCESLIMIT];
	Vec2 final_force;
public:
	Transformation* units_transformation;
};