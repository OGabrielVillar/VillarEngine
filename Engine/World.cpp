#include "World.h"

World::World() :
	physicSystem(&_unitsx),
	combatSystem(&_unitsx),
	control(combatSystem)
{
	float radius = 24.0f;		        //cm
	//testPorposes
	/*/ */ /*

	AddUnit(Unit("curva", Vec2(900.0f, 300.0f)));
	GetCreatedUnit()->SetRadius(radius);
	GetCreatedUnit()->SetRigidBodyForm(Form(radius*1.0f, Form::Type::Curve3P));
	GetCreatedUnit()->rigidbody.form.PushVertice(Vec2(-200.0f, 300.0f));
	GetCreatedUnit()->rigidbody.form.PushVertice(Vec2(0.0f, 600.0f));
	GetCreatedUnit()->rigidbody.UpdateMass();
	control.SetSelectedUnit(*GetCreatedUnit());
	GetCreatedUnit()->rigidbody.transformation.SetOrientationRad(PI / 3.8f);
	curva = GetCreatedUnit();
	// */
	//
	//AddUnit(Unit("sol", Vec2(600.0f, 250.0f)));
	//GetCreatedUnit()->SetRadius(105.0f);
	//GetCreatedUnit()->rigidbody.is_immovable = false;
	//GetCreatedUnit()->rigidbody.density = 10000.0f;
	//GetCreatedUnit()->rigidbody.UpdateMass();
	//physicSystem.Sun = GetCreatedUnit();
	//sun = GetCreatedUnit();

	AddUnit(Unit("linhamedia", Vec2(500.0f, 300.0f)));
	GetCreatedUnit()->SetRadius(radius*2.5f);
	GetCreatedUnit()->SetRigidBodyForm(Form(radius*4.0f, Form::Type::Line));
	GetCreatedUnit()->rigidbody.form.PushVertice(Vec2(200.0f, 0.0f));
	GetCreatedUnit()->rigidbody.is_immovable = true;
	GetCreatedUnit()->rigidbody.UpdateMass();
	
	AddUnit(Unit("linhamedia", Vec2(1000.0f, 300.0f)));
	GetCreatedUnit()->SetRadius(radius*2.5f);
	GetCreatedUnit()->SetRigidBodyForm(Form(radius*1.0f, Form::Type::Line));
	GetCreatedUnit()->rigidbody.form.PushVertice(Vec2(50.0f, 0.0f));
	GetCreatedUnit()->rigidbody.is_immovable = true;
	GetCreatedUnit()->rigidbody.UpdateMass();
	
	AddUnit(Unit("linhamediaVertical", Vec2(800.0f, 300.0f)));
	GetCreatedUnit()->SetRadius(radius*2.5f);
	GetCreatedUnit()->SetRigidBodyForm(Form(radius*4.0f, Form::Type::Line));
	GetCreatedUnit()->rigidbody.form.PushVertice(Vec2(350.0f, 0.0f));
	GetCreatedUnit()->rigidbody.is_immovable = true;
	GetCreatedUnit()->rigidbody.UpdateMass();
	linhagrande = GetCreatedUnit();
	
	//AddUnit(Unit("linhagrande", Vec2(500.0f, 660.0f)));
	//GetCreatedUnit()->SetRadius(radius*6.5f);
	//GetCreatedUnit()->SetRigidBodyForm(Form(radius*4.0f, Form::Type::Line));
	//GetCreatedUnit()->rigidbody.form.PushVertice(Vec2(2300.0f, 0.0f));
	//GetCreatedUnit()->rigidbody.is_immovable = true;
	//GetCreatedUnit()->rigidbody.UpdateMass();
	
	AddUnit(Unit("linha", Vec2(500.0f, 160.0f)));
	GetCreatedUnit()->SetRadius(radius);
	GetCreatedUnit()->SetRigidBodyForm(Form(radius*0.8f, Form::Type::Line));
	GetCreatedUnit()->rigidbody.form.PushVertice(Vec2(radius * 5.0f, 0.0f));
	GetCreatedUnit()->rigidbody.UpdateMass();

	AddUnit(Unit("esfera", Vec2(100, 200.0f)));
	GetCreatedUnit()->SetRadius(radius);
	control.SetSelectedUnit(*GetCreatedUnit());
	GetCreatedUnit()->rigidbody.transformation.SetOrientationInRadians(PI / 3.8f);
	userunit = GetCreatedUnit();

	float force = 1100.0f;			//cm per second

	Effect aeffect;
	aeffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	aeffect.SetFunctionTransformation(0,0,Transformation(Vec2(-force,0.0f)));
	AddCommand(userunit, 'A', aeffect);

	Effect deffect;
	deffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	deffect.SetFunctionTransformation(0, 0, Transformation(Vec2(force, 0.0f)));
	AddCommand(userunit, 'D', deffect);

	Effect weffect;
	weffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	weffect.SetFunctionTransformation(0, 0, Transformation(Vec2(0.0f, -force)));
	AddCommand(userunit, 'W', weffect);

	Effect seffect;
	seffect.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
	seffect.SetFunctionTransformation(0, 0, Transformation(Vec2(0.0f, force)));
	AddCommand(userunit, 'S', seffect);

	Effect qeffect;
	qeffect.SetFunction(0, Function::Type::AddUnitRadius, Function::Unit::Source);
	qeffect.SetFunctionFloat(0, 0, 1.0);
	AddCommand(userunit, 'Q', qeffect);

	Effect eeffect;
	eeffect.SetFunction(0, Function::Type::AddUnitRadius, Function::Unit::Source);
	eeffect.SetFunctionFloat(0, 0, -1.0);
	AddCommand(userunit, 'E', eeffect);

	Effect spaceeffect;
	spaceeffect.SetFunction(0, Function::Type::SetUnitPosition, Function::Unit::Source);
	spaceeffect.SetFunctionVec2(0, 0, Vec2(300.0f,300.0f));
	AddCommand(userunit, (char)32, spaceeffect);

	Effect righteffect;
	righteffect.SetFunction(0, Function::Type::RotatesByRad, Function::Unit::Source);
	righteffect.SetFunctionFloat(0, 0, 0.8f);
	AddCommand(linhagrande, (char)39, righteffect);
	
	Effect lefteffect;
	lefteffect.SetFunction(0, Function::Type::RotatesByRad, Function::Unit::Source);
	lefteffect.SetFunctionFloat(0, 0, -0.8f);
	AddCommand(linhagrande, (char)37, lefteffect);

	// 25 UNIT SPAWN
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10 ; j++)
		{
			AddUnit(Unit("Steve", Vec2(2.2f * radius * (float)i + 300.0f, 2.2f * radius * (float)j + 500.0f)));
			GetCreatedUnit()->SetRadius(radius);
			GetCreatedUnit()->rigidbody.transformation.SetOrientationInRadians(PI / 2);
			Effect spaceeffectx;
			spaceeffectx.SetFunction(0, Function::Type::AddForce, Function::Unit::Source);
			spaceeffectx.SetFunctionTransformation(0, 0, Transformation(Vec2(0.0f, force)));
			AddCommand(GetCreatedUnit(), 'X', spaceeffectx);
		}
	}
	//Line3/*/
	//

	//Line2/*/
	/*/
	AddUnit(Unit("linha", Vec2(600.0f, 600.0f)));
	GetCreatedUnit()->SetRadius(radius*2.5f);
	GetCreatedUnit()->SetRigidBodyForm(Form(1.5f, Form::Type::Line));
	GetCreatedUnit()->rigidbody.form.GetVertice(1) = Vec2(-20.0f, 100.0f);
	GetCreatedUnit()->rigidbody.UpdateMass();
	GetCreatedUnit()->rigidbody.transformation.SetOrientationRad(PI / 2);

	//Line/*/
	/*/
	AddUnit(Unit("linha", Vec2(300.0f, 600.0f)));
	GetCreatedUnit()->SetRadius(radius*2.5f);
	GetCreatedUnit()->SetRigidBodyForm(Form(radius*1.5f, Form::Type::Line));
	GetCreatedUnit()->rigidbody.form.PushVertice(Vec2(200.0f, 200.0f));
	GetCreatedUnit()->rigidbody.UpdateMass();
	GetCreatedUnit()->rigidbody.transformation.SetOrientationRad(PI / 2);

	spaceeffect.SetFunctionVec2(0, 0, Vec2(600.0f, 300.0f));
	AddCommand(GetCreatedUnit(), (char)32, spaceeffect);
	//testEnding/*/
}

void World::Go(float ft_in)
{
	ft = ft_in;
	combatSystem.Go(ft_in);
	physicSystem.Go(ft_in);
}

void World::AddUnit(Unit unt_in)
{
	_unitsx.PushElement(unt_in);
	newUnit = _unitsx.GetLastElement();
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

Camera * World::GetCamera()
{
	return &camera;
}

IdList<Unit>* World::GetUnitIdList()
{
	return &_unitsx;
}

PhysicSystem * World::GetPPhysicsSystem()
{
	return &physicSystem;
}

CombatSystem * World::GetPCombatSystem()
{
	return &combatSystem;
}

Control* World::GetControl()
{
	return &control;
}
