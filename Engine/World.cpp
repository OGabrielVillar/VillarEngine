#include "World.h"

World::World() :
	physicSystem(&units[0]),
	combatSystem(&units[0]),
	control(combatSystem)
{
	float velocity = 800.0f;
	//testPorposes
	AddUnit(Unit("esfera", Vec2(300.0f, 300.0f)));
	GetCreatedUnit()->SetRadius(50.0f);
	control.SetSelectedUnit(*GetCreatedUnit());
	GetCreatedUnit()->rigidbody.form.transformation.orientation = PI / 2;

	Effect xeffect;
	xeffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	xeffect.SetFunctionTransformation(0,0,Transformation(Vec2(-velocity,0.0f)));
	AddCommand(GetCreatedUnit(), 'A', xeffect);

	Effect deffect;
	deffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	deffect.SetFunctionTransformation(0, 0, Transformation(Vec2(velocity, 0.0f)));
	AddCommand(GetCreatedUnit(), 'D', deffect);

	Effect weffect;
	weffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	weffect.SetFunctionTransformation(0, 0, Transformation(Vec2(0.0f, -velocity)));
	AddCommand(GetCreatedUnit(), 'W', weffect);

	Effect seffect;
	seffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	seffect.SetFunctionTransformation(0, 0, Transformation(Vec2(0.0f, velocity)));
	AddCommand(GetCreatedUnit(), 'S', seffect);

	Effect veffect;
	veffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	veffect.SetFunctionTransformation(0, 0, Transformation(Vec2(velocity, velocity)));
	AddCommand(GetCreatedUnit(), 'V', veffect);

	Effect qeffect;
	qeffect.SetFunction(0, Function::Type::AddUnitRadius, Function::Unit::Source);
	qeffect.SetFunctionFloat(0, 0, 1.0);
	AddCommand(GetCreatedUnit(), 'Q', qeffect);

	Effect eeffect;
	eeffect.SetFunction(0, Function::Type::AddUnitRadius, Function::Unit::Source);
	eeffect.SetFunctionFloat(0, 0, -1.0);
	AddCommand(GetCreatedUnit(), 'E', eeffect);

	Effect spaceeffect;
	spaceeffect.SetFunction(0, Function::Type::SetUnitPosition, Function::Unit::Source);
	spaceeffect.SetFunctionVec2(0, 0, Vec2(300.0f,300.0f));
	AddCommand(GetCreatedUnit(), (char)32, spaceeffect);

	AddUnit(Unit("bob",Vec2(600.0f,600.0f)));
	GetCreatedUnit()->SetRadius(50.0f);
	GetCreatedUnit()->rigidbody.form.transformation.orientation = PI/2;

	Effect spaceeffect2;
	spaceeffect2.SetFunction(0, Function::Type::SetUnitPosition, Function::Unit::Source);
	spaceeffect2.SetFunctionVec2(0, 0, Vec2(300.0f, 600.0f));
	AddCommand(GetCreatedUnit(), (char)32, spaceeffect2);
	/*
	for (size_t i = 1; i < 6; i++)
	{
		for (size_t j = 1; j < 6; j++)
		{
			AddUnit(Unit("Steve", Vec2(120.0f * (float)i, 120.0f * (float)j)));
			GetCreatedUnit()->SetRadius(50.0f);
			GetCreatedUnit()->rigidbody.form.transformation.orientation = PI / 2;
			Effect spaceeffectx;
			spaceeffectx.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
			spaceeffectx.SetFunctionTransformation(0, 0, Transformation(Vec2(0.0f, velocity)));
			AddCommand(GetCreatedUnit(), 'X', spaceeffectx);
		}
	}
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
