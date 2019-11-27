#pragma once

#include "Unit.h"

class PhysicSystem
{
public:
	PhysicSystem(Unit* units_in);
	void Go();
	void MoveBodys();
private:
	Unit* Punit;
};