#pragma once

#include "UIElement.h"
#include "Graphics.h"
#include "World.h"

class DrawSystem
{
public:
	DrawSystem(Graphics& const gfx_in, World& const world_in);
public:
	void Go(float ft_in);
	void ComposeFrame();
private:
	Graphics* gfx;
	World* world;
	UIElement screen;
	float ft;
};