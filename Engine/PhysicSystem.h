#pragma once


#include "Unit.h"
#include <string>
#include <sstream>

class PhysicSystem
{
public:
	PhysicSystem(Unit* unitgroup_in);
	void Go(float ft_in);
	void MoveBodys();
	bool IsCollinding(RigidBody* rb_a, RigidBody* rb_b);
	bool PointPointCollisionTest(RigidBody& rb_a, RigidBody& rb_b);
	bool PointLineCollisionTest(RigidBody& rb_a, RigidBody& rb_b);
	float SqrdDistance(Vec2 vec2_a, Vec2 vec2_b); 
	void Collision(RigidBody* rbP0, RigidBody* rbP1); 
	void ForceTransmission(RigidBody& rbP0, RigidBody& rbP1);
	void ForceTransmission2(RigidBody & rbP0, RigidBody & rbP1);
	Vec2 GetReflectedForce(Vec2 v_in, Vec2 w_in);
private:
	Unit* Punitgroup;
	float ft;
	bool ThereWasCollision = false;
	float amountOfEnergyInSystemN;
	std::vector<std::string> log;
public:
	Vec2 x_projection;
	Vec2 y_projection;
	Vec2 contact_point;
	Vec2 collision_points;
};