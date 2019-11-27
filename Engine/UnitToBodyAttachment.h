#pragma once

#include "Transformation.h"

class UnitToBodyAttachment
{
public:
	UnitToBodyAttachment() = default;
public: //SETTERS
	void SetOffset(Transformation offset_in);
	void SetUnitTransformation(Transformation transformation_in);
	void SetUnitTransformationAttachment(Transformation* transformation_in);
	void AddUnitTransformation(Transformation transformation_in);
public: //GETTERS
	Transformation GetOffset();
	Transformation GetUnitTransformation();
	Transformation* GetUnitTransformationAttachment();
private:
	Transformation offset;
	Transformation* unit_transformation = nullptr;
};