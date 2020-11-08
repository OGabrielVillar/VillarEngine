#pragma once

#define NFORCESLIMIT 9
#define MASSFACTOR 1.0f

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
	void SetTransformation(const Transformation& transformation_in);
	void SetPosition(const Vec2& position_in);
	void SetVelocity(const Vec2& velocity_in);
	void SetForm(const Form& Form_in);
	void SetFormRadius(float radius_in);
	void SetDensity(float density_in);
	void UpdateMass();
	void UpdateTransformation();
	void MoveVerticeTo(int index, Vec2 position_in);
public: //GETTERS
	Transformation GetTransformation();
	Vec2 GetVerticePos(int vertice_index);
	Transformation GetVerticeTransf(int vertice_index);
	Vec2 GetVerticeOri(int vertice_index);
	Transformation GetVertice(int vertice_index) const;
	Vec2 GetVelocity();
	Vec2 GetPosition();
	Vec2 GetForce();
	Vec2 GetCOM();
public: //FUNCTIONS
	void AddForce(const Vec2 & force_in);
	void AddForce(const Vec2 & force_in, const Vec2 & contactpoint_in);
	void ApplyForces();
	void ClearForces();
	void SetOrientation(float radians);



public:
	Form form;
	Vec2 COM;


	Vec2 form_offset;
	bool uses_gravity;
public://PHYSICS
	Transformation transformation;


	// Set by shape
	float mass = 1.0f;			// Kilogram
	float inv_mass;				// inverse mass
	float inertia = 1.0f;		// moment of inertia
	float inv_inertia;			// inverse inertia
	float density = 9.97f;		// Gram per cm²

	Vec2 velocity = 0.0f;
	Vec2 force = 0.0f;

	float angularVelocity = 0.0f;
	float torque = 0.0f;

	float staticFriction = 0.4f;
	float dynamicFriction = 0.4f;
	float restitution = 0.6f;
	Material material;

	bool arecolliding = false;
	bool arebeinghit = false;

	bool is_inverted = false;
	bool is_immovable = false;

	int howmanyhits = 0;
private:

};

