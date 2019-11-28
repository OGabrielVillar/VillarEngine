#include "World.h"

World::World() :
	physicSystem(&units[0]),
	combatSystem(&units[0]),
	control(combatSystem)
{
	//testPorposes
	AddUnit(Unit("esfera", Vec2(300.0f, 300.0f)));
	GetCreatedUnit()->SetRadius(150.0f);
	control.SetSelectedUnit(*GetCreatedUnit());
	GetCreatedUnit()->rigidbody.form.transformation.orientation = PI / 2;

	Effect xeffect;
	xeffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	xeffect.SetFunctionTransformation(0,0,Transformation(Vec2(-7000.1f,0.0f)));
	AddCommand(GetCreatedUnit(), 'A', xeffect);

	Effect deffect;
	deffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	deffect.SetFunctionTransformation(0, 0, Transformation(Vec2(7000.1f, 0.0f)));
	AddCommand(GetCreatedUnit(), 'D', deffect);

	Effect weffect;
	weffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	weffect.SetFunctionTransformation(0, 0, Transformation(Vec2(0.0f, -7000.1f)));
	AddCommand(GetCreatedUnit(), 'W', weffect);

	Effect seffect;
	seffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	seffect.SetFunctionTransformation(0, 0, Transformation(Vec2(0.0f, 7000.1f)));
	AddCommand(GetCreatedUnit(), 'S', seffect);

	Effect qeffect;
	qeffect.SetFunction(0, Function::Type::AddRadiusOfUnit, Function::Unit::Source);
	qeffect.SetFunctionFloat(0, 0, 1.0);
	AddCommand(GetCreatedUnit(), 'Q', qeffect);

	Effect eeffect;
	eeffect.SetFunction(0, Function::Type::AddRadiusOfUnit, Function::Unit::Source);
	eeffect.SetFunctionFloat(0, 0, -1.0);
	AddCommand(GetCreatedUnit(), 'E', eeffect);

	AddUnit(Unit("bob",Vec2(600.0f,600.0f)));
	GetCreatedUnit()->SetRadius(100.0f);
	GetCreatedUnit()->rigidbody.form.transformation.orientation = PI/2;
	//testEnding/*/
}

void World::Go()
{
	combatSystem.Go(ft.Mark());
	physicSystem.Go(ft.Mark());
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
		return units[0];
	}
	return units[index];
}

Control* World::GetControl()
{
	return &control;
}
