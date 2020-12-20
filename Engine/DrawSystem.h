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
	Texture tatuzin = Texture("tatuzin.bmp");
public:
};