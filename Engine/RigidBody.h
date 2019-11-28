#pragma once

#define NFORCESLIMIT 9

#include "Form.h"
#include "UnitToBodyAttachment.h"

class RigidBody
{
public:
	RigidBody();
	RigidBody(Transformation transformation_in);
	RigidBody(Form *form_in, unsigned int x, unsigned int y);
public: //SETTERS
	void SetTransformation(Transformation transformation_in);
	void SetVelocity(Vec2 velocity_in);
	void SetForm(Form Form_in);
	void SetFormRadius(float float_in);
public: //GETTERS
	Transformation GetTransformation();
	Vec2 GetVelocity();
	Vec2 GetForce();
public: //FUNCTIONS
	void AddForce(Vec2 force_in);
	void ApplyForces();
	void ClearForces();
	void ApplyImpulse(const Vec2& impulse, const Vec2& contactVector);
	void SetStatic(void);
	void SetOrientation(float radians);



public:
	Form form;
	bool uses_gravity;
public://PHYSICS
	Vec2 velocity;
	float angularVelocity;
	float torque;
	float orient; // radians

	Vec2 force;
	Vec2 acceleration;

	// Set by shape
	float I;  // moment of inertia
	float iI; // inverse inertia
	float m;  // mass
	float im; // inverse masee

	// http://gamedev.tutsplus.com/tutorials/implementation/how-to-create-a-custom-2d-physics-engine-friction-scene-and-jump-table/
	float staticFriction;
	float dynamicFriction;
	float restitution;
};

