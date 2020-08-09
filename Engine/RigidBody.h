#pragma once

#define NFORCESLIMIT 9

#include "Form.h"
#include "Material.h"
#include "UnitToBodyAttachment.h"

class RigidBody
{
public:
	RigidBody();
	RigidBody(Transformation transformation_in);
	RigidBody(Transformation transformation_in, Form form_in);
	RigidBody(Form *form_in, unsigned int x, unsigned int y);
public: //SETTERS
	void SetTransformation(Transformation transformation_in);
	void SetPosition(Transformation transformation_in);
	void SetVelocity(Vec2 velocity_in);
	void SetForm(Form Form_in);
	void SetFormRadius(float radius_in);
	void SetDensity(float density_in);
	void UpdateMass();
	void UpdateTransformation();
	void MoveVerticeTo(int index, Vec2 position_in);
public: //GETTERS
	Transformation GetTransformation();
	Vec2 GetVerticePos(int vertice_index);
	Vec2 GetVerticeOri(int vertice_index);
	Transformation GetVertice(int vertice_index) const;
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
	Vec2 form_offset;
	bool uses_gravity;
public://PHYSICS
	Transformation transformation;
	Vec2 velocity;
	float angularVelocity;
	float torque;

	Vec2 force;
	Vec2 acceleration;

	float mass = 1.0f;			// Gram
	float density = 9.97f;		// Gram per cm²
	// Set by shape
	float I;  // moment of inertia
	float iI; // inverse inertia
	float m;  // mass
	float im; // inverse masee

	float staticFriction;
	float dynamicFriction;
	Material material;

	bool arecolliding = false;
	bool arebeinghit = false;
private:

};

