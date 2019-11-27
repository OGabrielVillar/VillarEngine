/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	world()
{
	defaultControl = world.GetControl();
	defaultControl->BindKeyboard(wnd.kbd);
	world.GetPCombatSystem()->BindKeyboard(wnd.kbd);
}

void Game::Go()
{
	gfx.BeginFrame();	
	Update();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::Update()
{
	world.Go();

	/*
	// process key messages while any remain
	while( !wnd.kbd.KeyIsEmpty() )
	{
		const auto e = wnd.kbd.ReadKey();
		// only interested in space bar presses
		if( e.IsPress() && e.GetCode() == VK_SPACE )
		{
			link.ActivateEffect();
			hit.Play();
			list.EraseBackElement();
		}
	}
	// process arrow keys state
	Vec2 dir = { 0.0f,0.0f };
	if( wnd.kbd.KeyIsPressed('W') )
	{
		dir.y -= 1.0f;
	}
	if( wnd.kbd.KeyIsPressed('S') )
	{
		dir.y += 1.0f;
	}
	if( wnd.kbd.KeyIsPressed('A') )
	{
		dir.x -= 1.0f;
	}
	if( wnd.kbd.KeyIsPressed('D') )
	{
		dir.x += 1.0f;
	}
	link.SetDirection( dir );
	// update character
	link.Update( ft.Mark() );
	*/
}

void Game::ComposeFrame()		
{
	char i = 0;
	Unit* pU;
	while (i < UNITSLIMIT)
	{
		pU = &world.GetUnit(i);
		if (!pU->GetName().empty())
		{
			gfx.DrawCircle(pU->GetPosition(), pU->GetRadius(), Colors::White);
		}
		i++;
	}
	i = 0;
	while (i < UNITSLIMIT)
	{
		pU = &world.GetUnit(i);
		if (!pU->GetName().empty())
		{
			gfx.DrawCircle(pU->rigidbody.GetTransformation().GetPosition(), pU->GetRadius(), Colors::Magenta);
		}
		i++;
	}

	gfx.DrawLine(world.GetUnit(0).rigidbody.GetTransformation().GetPosition(), world.GetUnit(1).rigidbody.GetTransformation().GetPosition(),Colors::Magenta);

	/*
	link.Draw( gfx );
	gfx.PutPixel(500, 500, Colors::Magenta);
	//font.DrawText( "Becky.\nLemme smash.",wnd.mouse.GetPos() - Vei2{ 50,150 },Colors::White,gfx );
	if (trigger >= 60)
	{
		string = std::string("\nFps: " + std::to_string(1 / ft.Get()) );
		list.PushElement(string);
		trigger = 0;
	}
	finalString = '0';
	for (int i = 0; i < list.capacity(); i++)
	{
		finalString += list[i];
	}
	font.DrawText(finalString, textPos, Colors::Yellow, gfx);
	for (size_t i = 0; i < 20000000; i++)
	{
		char a = 0;
		a = 1;
	}
	trigger ++;
	*/
}
