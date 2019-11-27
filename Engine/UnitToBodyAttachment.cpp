#include "UnitToBodyAttachment.h"

void UnitToBodyAttachment::SetOffset(Transformation offset_in)
{
	offset = offset_in;
}

void UnitToBodyAttachment::SetUnitTransformation(Transformation transformation_in)
{
	if (unit_transformation != nullptr)
	{
		*unit_transformation = transformation_in + offset;
	}
}

void UnitToBodyAttachment::SetUnitTransformationAttachment(Transformation* transformation_in)
{
	unit_transformation = transformation_in;
}

void UnitToBodyAttachment::AddUnitTransformation(Transformation transformation_in)
{
	*unit_transformation += transformation_in;
}

Transformation UnitToBodyAttachment::GetOffset()
{
	return offset;
}

Transformation UnitToBodyAttachment::GetUnitTransformation()
{
	return *unit_transformation;
}

Transformation * UnitToBodyAttachment::GetUnitTransformationAttachment()
{
	return unit_transformation;
}
