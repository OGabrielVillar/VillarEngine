#pragma once

#include "Unit.h"

class PhysicSystem
{
public:
	PhysicSystem(Unit* units_in);
	void Go(float ft_in);
	void MoveBodys();
	bool IsCollinding(RigidBody* rb_a, RigidBody* rb_b);
	bool PointPointCollisionTest(RigidBody* rb_a, RigidBody* rb_b);
	float SqrdDistance(Vec2 vec2_a, Vec2 vec2_b);
private:
	Unit* Punit;
	float ft;
};