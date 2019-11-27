#pragma once

#include "Unit.h"

class Function
{
public:
	enum class Type
	{
		Non,
		AddForce,
	};
	enum class Unit
	{
		Non,
		Target,
		Source,
	};
	Type type;
	Unit unit;
	float f[1];
	Transformation t[1];
};