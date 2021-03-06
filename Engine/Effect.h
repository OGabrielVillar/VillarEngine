#pragma once

#define FUNCTIONSLIMIT 3
#include "Unit.h"
#include "Function.h"

class Effect
{
public://CONSTRUCTORS AND CLASSES.
	Effect() = default;
	Effect(Unit& source_in);
	Effect(Unit& source_in, Unit& target_in);
	enum class Type
	{
		Non,
		Timer,
		Constant,
		Instant,
	};

public://GETTERS
	bool isActive();
public://SETTERS
	void SetSourceUnit(Unit* Punit_in);
	void ActivateEffect();

public://FUNCTIONS SETTING
	void SetFunction(int index_in, Function::Type type_in, Function::Unit unit_in);
	void SetFunctionFloat(int index_in, int float_index_in, float float_in);
	void SetFunctionTransformation(int index_in, int transf_index_in, Transformation transf_in);
	void SetFunctionVec2(int index_in, int transf_index_in, Vec2 vec2_in);

public://FUNCTIONS EFFECTS
	void ApplyFunctions(float ft_in);
	void AddForce(Unit* Punit, Transformation transformation_in, float ft_in);
	void AddForce_CMperS(Unit* Punit, Transformation transformation_in, float ft_in);
	void AddUnitRadius(Unit * Punit, float float_in);
	void SetUnitPosition(Unit * Punit, Vec2 position_in);
	void RotatesByRad(Transformation * Ptransformation, float rad_in, float ft_in);

private://VARIABLES
	Type type = Type::Non;
	bool active = false;
	Unit* target;
	Unit* source;
	Function functionslist[FUNCTIONSLIMIT];
};