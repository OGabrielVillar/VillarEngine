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
	while (pFuncion != &functionslist[FUNCTIONSLIMIT+1])
	{
		switch (pFuncion->type)
		{
		case Function::Type::AddForce:
			switch (pFuncion->unit)
			{
			case Function::Unit::Source:
				AddForce(source,pFuncion->t[0]);
				break;
			case Function::Unit::Target:
				AddForce(target, pFuncion->t[0]);
				break;
			case Function::Unit::Non:
				break;
			default:
				break;
			}
			break;

		case Function::Type::Non:
			break;

		default:
			break;
		}

		pFuncion++;

	}
}

void Effect::AddForce(Unit* Punit, Transformation transformation_in)
{
	Punit->rigidbody.AddForce(transformation_in.position);
}
