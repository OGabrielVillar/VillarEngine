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

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Surface.h"
#include "Animation.h"
#include "FrameTimer.h"
#include "Character.h"
#include "Font.h"
#include "Sound.h"
#include "List.h"


#include "World.h"

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
private:
	MainWindow& wnd;
	Graphics gfx;
	World world;
	Control* defaultControl;
	/********************************/
	/*  User Variables              
	List<std::string> list;
	FrameTimer ft;
	Character link = Vec2(111,111);
	Font font = "Images\\Fixedsys16x28.bmp";
	Sound hit = L"Sounds\\hit.wav";
	Sound song = Sound(L"Sounds\\SonzinJogo01.wav",3.0f,60.0f);
	Vei2 textPos = Vei2(500,100);
	int trigger = 0;
	int stresstest = 1;
	std::string string = std::string("0");;
	std::string finalString = std::string("0");;
	Vec2 canvas0n0 = Vec2(0, 0);*/
	/********************************/
};