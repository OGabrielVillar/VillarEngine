#pragma once


#include "CombatSystem.h"
#include "PhysicSystem.h"
#include "Control.h"
#include "AI.h"
#include "FrameTimer.h"

class World
{
public:
	World();
	void Go(float ft_in);
public:
	void AddUnit(Unit unt_in);
	void AddCommand(Unit* unit_in, unsigned char key_in, Effect effect_in);
	void AddCommand(Unit* unit_in, unsigned char key_in, unsigned int effect_id_in);
public: //GETTERS
	Unit& GetUnit(int index);
	Control* GetControl();
	Unit* GetCreatedUnit();
	PhysicSystem* GetPPhysicsSystem();
	CombatSystem* GetPCombatSystem();
	Unit* userunit = nullptr;
	Unit* linhagrande = nullptr;
	Unit* curva = nullptr;
private:
	Unit units[UNITSLIMIT];
	CombatSystem combatSystem;
	PhysicSystem physicSystem;
	Control control;
	Unit* newUnit = nullptr;
	float ft;
};