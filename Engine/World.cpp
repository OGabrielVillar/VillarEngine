#include "World.h"

World::World() :
	physicSystem(&units[0]),
	combatSystem(&units[0]),
	control(combatSystem)
{
	//testPorposes
	AddUnit(Unit("esfera", Vec2(300.0f, 300.0f)));
	Transformation* oi = &GetCreatedUnit()->GetTransformation();
	GetCreatedUnit()->SetRadiusTo(150.0f);
	GetCreatedUnit()->SetTransformation(Transformation(GetCreatedUnit()->GetPosition()*1.1f));
	control.SetSelectedUnit(*GetCreatedUnit());
	Effect xeffect;
	xeffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	xeffect.SetFunctionTransformation(0,0,Transformation(Vec2(-1.0f,0.0f)));
	AddCommand(GetCreatedUnit(), 'A', xeffect);
	AddUnit(Unit("bob",Vec2(600.0f,600.0f)));
	GetCreatedUnit()->SetRadiusTo(80.0f);
	//testEnding/*/
}

void World::Go()
{
	combatSystem.Go();
	physicSystem.Go();
}

void World::AddUnit(Unit unt_in)
{
	{
		char i = 0;
		while (i < UNITSLIMIT)
		{
			if (units[i].GetName().empty())
			{
				units[i] = unt_in;
				newUnit = &units[i];
				return;
			}
			i++;
		}
	}
}

void World::AddCommand(Unit * unit_in, unsigned char key_in, Effect effect_in)
{
	unit_in->AddCommand(Command(key_in, combatSystem.AddEffectTemplate(effect_in)));
}

void World::AddCommand(Unit * unit_in, unsigned char key_in, unsigned int effect_id_in)
{
	unit_in->AddCommand(Command(key_in, effect_id_in));
}

Unit * World::GetCreatedUnit()
{
	return newUnit;
}

PhysicSystem * World::GetPPhysicsSystem()
{
	return &physicSystem;
}

CombatSystem * World::GetPCombatSystem()
{
	return &combatSystem;
}

Unit & World::GetUnit(int index)
{
	if (index > UNITSLIMIT)
	{
		return Unit();
	}
	return units[index];
}

Control* World::GetControl()
{
	return &control;
}
