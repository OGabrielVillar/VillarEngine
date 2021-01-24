#pragma once

#include "Motion.h"
#include "IdList.h"

class MotionSystem
{
public:
	MotionSystem();
	//~MotionSystem(); to do
	void Go(float ft_in);
	void AddFloatMotion(Reference<float>* reference_in);
	Motion<float>& GetLastFloatMotion() const;

private:
	float ft = 0.0f;
	IdList<Motion<float>> float_motion_list;
	IdListReader<Motion<float>> float_mlr;//motion_list_reader
	Motion<float>* last_float_motion = nullptr;
};