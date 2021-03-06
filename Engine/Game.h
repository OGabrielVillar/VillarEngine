/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "MainWindow.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Texture.h"
#include "Animation.h"
#include "FrameTimer.h"
#include "Character.h"
#include "List.h"
#include "FileStream.h"
#include "MemoryManager.h"

#include "MotionSystem.h"
#include "DrawSystem.h"
#include "World.h"
#include "IdList.h"
#include <string>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void Update();
	/********************************/
	/*  User Functions              */
	/********************************/
	void Controls();
	WPosition GetMouseWorldPosition();
	WPosition GetScreenWorldPosition(const Vec2& screen_pos);
	void DoTheBoundThing();
private:
	FileStream fs;

	MainWindow& wnd;
	Graphics gfx;
	World world;
	MotionSystem motionSystem;
	MemoryManager memoryManager;
	DrawSystem drawSystem;
	Control* defaultControl;
	FrameTimer ft;
	float velocity_sum;
	Transformation CamDefaultTransf;


	bool bound_active = true;
	/********************************/
	//  User Variables              
	//Font font = "Images\\Fixedsys16x28.bmp";
	bool lefthasbeenpressed = false;
	WPosition left_clickPos;
	WPosition left_camInitialPos;
	WPosition left_clickLastPos;
	//List<std::string> list;
	////Character link = Vec2(111,111);
	//Sound hit = L"Sounds\\hit.wav";
	//Sound song = Sound(L"Sounds\\SonzinJogo01.wav",0.0f,(60.0f*4.0f)+27.0f);
	//Vei2 textPos = Vei2(1200,100);
	//int trigger = 0;
	//int stresstest = 1;
	//std::string string = std::string("0");;
	//std::string finalString = std::string("0");;
	//Vec2 canvas0n0 = Vec2(0, 0);
	/********************************/
};