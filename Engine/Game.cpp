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
	velocity_sum = 0.0f;
	Transformation t;
	float radius;
	char i = 0;
	Unit* pU;
	while (i < UNITSLIMIT)
	{
		pU = &world.GetUnit(i);
		if (!pU->GetName().empty())
		{
			pU = &world.GetUnit(i);
			radius = pU->GetRadius();
			t = pU->GetTransformation();
			if (t.GetPosition().x < -radius)
			{
				t.position.x = gfx.ScreenWidth + radius;
			}
			else if (t.GetPosition().x > gfx.ScreenWidth + radius)
			{
				t.position.x = -radius;
			}
			if (t.GetPosition().y < -radius)
			{
				t.position.y = gfx.ScreenHeight + radius;
			}
			else if (t.GetPosition().y > gfx.ScreenHeight + radius)
			{
				t.position.y = -radius;
			}
			pU->SetTransformation(t);
			velocity_sum += pU->rigidbody.velocity.Len();
		}
		i++;
	}
	i = 0;
}

void Game::ComposeFrame()		
{
	Color cx = Colors::Magenta;
	if (world.GetPPhysicsSystem()->PointPointCollisionTest(world.GetUnit(0).rigidbody.form, world.GetUnit(1).rigidbody.form))
	{
		cx = Colors::Red;
	}
	char i = 0;
	Unit* pU;
	while (i < UNITSLIMIT)
	{
		pU = &world.GetUnit(i);
		if (!pU->GetName().empty())
		{
			gfx.DrawCircle(pU->GetTransformation().GetPosition(), pU->GetRadius(), cx);
			gfx.DrawLine(pU->GetTransformation().GetPosition(), 
				pU->GetTransformation().GetPosition() + 
				Vec2(pU->GetRadius()*std::cos(pU->rigidbody.form.transformation.orientation),
					pU->GetRadius()*std::sin(pU->rigidbody.form.transformation.orientation)),cx);
		}
		i++;
	}
	i = 0;
	while (i < UNITSLIMIT)
	{
		pU = &world.GetUnit(i);
		if (!pU->GetName().empty())
		{
			gfx.DrawCircle(pU->rigidbody.GetTransformation().GetPosition(), pU->GetRadius(), cx);
		}
		i++;
	}
	Vec2 lineLink0 = world.GetUnit(0).rigidbody.GetTransformation().GetPosition();
	Vec2 lineLink1 = world.GetUnit(1).rigidbody.GetTransformation().GetPosition();
	gfx.DrawLine(lineLink0, lineLink1, cx);

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
