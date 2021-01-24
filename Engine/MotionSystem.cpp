#include "MotionSystem.h"

MotionSystem::MotionSystem():
	float_motion_list(),
	float_mlr(&float_motion_list)
{
}

void MotionSystem::Go(float ft_in)
{
	ft = ft_in;

	float_mlr.Reset();
	Motion<float>* element;
	while (!float_mlr.Ended()) {
		element = float_mlr.Get();
		if (element->IsActive())
		{
			element->Go(ft);
			float_mlr.Next();
		}
		else
		{
			float_mlr.Remove();
		}
	}
}

void MotionSystem::AddFloatMotion(Reference<float>* reference_in)
{
	float_motion_list.PushElement(new Motion<float>(reference_in));
	last_float_motion = float_motion_list.GetLastElement();
}

Motion<float>& MotionSystem::GetLastFloatMotion() const
{
	return *last_float_motion;
}
