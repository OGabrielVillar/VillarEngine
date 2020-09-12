#pragma once

#define AIRDENSITY 1.2f
#define AIRRESISTENCE 0.99f
#define GCONSTPRE 0.0000001
#define GCONST 6.67408 * GCONSTPRE

#include "Unit.h"
#include <string>
#include <sstream>

class PhysicSystem
{
public:
	PhysicSystem(Unit* unitgroup_in);
	void Go(float ft_in);
	void MoveBodies();
	bool IsCollinding(RigidBody* rb0, RigidBody* rb1);
	bool PointToPointCollision(RigidBody& rb0, RigidBody& rb1);
	bool PointToLineCollision(RigidBody& rb0, RigidBody& rb1);
	bool LineToLineCollision(RigidBody& rb0, RigidBody& rb1);
	bool PointCurve3PCollisionTest(RigidBody & rb0, RigidBody & curve3p_in);
	float SqrdDistance(Vec2 vec2_a, Vec2 vec2_b);
	void Collision(RigidBody* rbP0, RigidBody* rbP1);
	void InvertedForceTransmission(RigidBody & rbP0, RigidBody & rbP1);
	void ForceTransmission(RigidBody & rbP0, RigidBody & rbP1);
	Vec2 GetReflectedForce(Vec2 v_in, Vec2 w_in);
private:
	Unit* Punitgroup;
	float ft;
	bool ThereWasCollision = false;
	float amountOfEnergyInSystemN;
	std::vector<std::string> log;
public:
	Unit* Sun;
	Vec2 x_projection;
	Vec2 y_projection;
	Vec2 contact_point;
	Vec2 collision_point;

	float penetration;     // Depth of penetration from collision
	Vec2 normal;          // From A to B
	Vec2 rb0contacts[2];     // Points of contact during collision
	Vec2 rb1contacts[2];     // Points of contact during collision
	int contact_count; // Number of contacts that occured during collision
	float e;               // Mixed restitution
	float df;              // Mixed dynamic friction
	float sf;              // Mixed static friction
};