#include "Effect.h"

Effect::Effect(Unit & source_in)
{
	source = &source_in;
}

Effect::Effect(Unit & source_in, Unit & target_in)
{
	source = &source_in;
	target = &target_in;
}

bool Effect::isActive()
{
	return active;
}

void Effect::SetSourceUnit(Unit * Punit_in)
{
	source = Punit_in;
}

void Effect::ActivateEffect()
{
	active = true;
}

void Effect::SetFunction(int index_in, Function::Type type_in, Function::Unit unit_in)
{
	functionslist[index_in].type = type_in;
	functionslist[index_in].unit = unit_in;
}

void Effect::SetFunctionFloat(int index_in, int float_index_in, float float_in)
{
	functionslist[index_in].f[float_index_in] = float_in;
}

void Effect::SetFunctionTransformation(int index_in, int transf_index_in, Transformation transf_in)
{
	functionslist[index_in].t[transf_index_in] = transf_in;
}

void Effect::ApplyFunctions()
{
	Function* pFuncion = &functionslist[0];
	while (pFuncion != &functionslist[FUNCTIONSLIMIT])
	{
		Unit* pTarget = source;

		switch (pFuncion->unit) {
		case Function::Unit::Target:
			pTarget = target;break;
		default:break;}

		switch (pFuncion->type){
		case Function::Type::AddForce:
			AddForce(pTarget,pFuncion->t[0]);break;
		case Function::Type::AddRadiusOfUnit:
			AddRadiusOfUnit(pTarget,pFuncion->f[0]);break;
		default:break;}

		pFuncion++;

	}
	active = false;
}

void Effect::AddForce(Unit* Punit, Transformation transformation_in)
{
	Punit->rigidbody.AddForce(transformation_in.position);
}

void Effect::AddRadiusOfUnit(Unit* Punit, float float_in)
{
	Punit->SetRadius(Punit->GetRadius() + float_in);
}
