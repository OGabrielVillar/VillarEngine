#pragma once

#include "UIElement.h"
#include "Graphics.h"
#include "World.h"

class DrawSystem
{
public:
	DrawSystem(Graphics& gfx_in, World& world_in);
public:
	void Go(float ft_in);
	void ComposeFrame();
private:
	void GridRender();
private:
	Graphics* gfx;
	World* world;
	UIElement screen;
	float ft;
public:
	int xbar1;
	int xbar2;
	int xbar3;
	float threshold;
	float digjoy[3];
	float digjoy_wheel = 0.0f;
	bool digjoy_wheel_dir = 0;
};