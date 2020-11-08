#pragma once


#include "CombatSystem.h"
#include "PhysicSystem.h"
#include "Control.h"
#include "AI.h"
#include "FrameTimer.h"
#include "Camera.h"
#include "IdList.h"

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
	Control* GetControl();
	Unit* GetCreatedUnit();
	Camera* GetCamera();
	IdList<Unit>* GetUnitIdList();
	PhysicSystem* GetPPhysicsSystem();
	CombatSystem* GetPCombatSystem();
	Unit* userunit = nullptr;
	Unit* linhagrande = nullptr;
	Unit* curva = nullptr;
	Unit* sun = nullptr;
private:
	IdList<Unit> _unitsx;
	CombatSystem combatSystem;
	PhysicSystem physicSystem;
	Control control;
	Unit* newUnit = nullptr;
	Camera camera;
	float ft;
};