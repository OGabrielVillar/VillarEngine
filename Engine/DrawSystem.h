#pragma once

#include "MainWindow.h"
#include "ConvertionTool.h"
#include "MotionSystem.h"
#include "MemoryManager.h"
#include "UIElement.h"
#include "Graphics.h"
#include "World.h"

class DrawSystem
{
public:
	DrawSystem(Graphics& gfx_in, World& world_in, MotionSystem& motionSystem_in, MemoryManager& memoryManager_in);
public:
	void Go(float ft_in);
	void ComposeFrame();
	void BindControls(Keyboard& kbd_in, Mouse& mse_in);
	WPosition GetMouseWorldPosition();
private:
	void GridRender();

private:
	Graphics* gfx;
	World* world;
	MotionSystem* motionSystem;
	MemoryManager* memoryManager;
	UIElement screen;
	PixelFont arial;
	float ft;

	Keyboard* kbd = nullptr;
	Mouse*  mse = nullptr;

	WPosition mouse_in_world;


	//tests
	float _animation_test = 1.0f;
public:
};