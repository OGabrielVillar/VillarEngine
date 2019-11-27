#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float Mark();
	float Get();
private:
	float count = 0;
	std::chrono::steady_clock::time_point last;
};