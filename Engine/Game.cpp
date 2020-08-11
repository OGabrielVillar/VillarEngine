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
	world.Go(ft.Mark());

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
	int i = 0;
	Unit* pU;
	while (i < UNITSLIMIT)
	{
		pU = &world.GetUnit(i);
		if (!pU->GetName().empty())
		{
			pU = &world.GetUnit(i);
			radius = pU->GetRadius();
			t = pU->GetTransformation();
			if (t.GetPosition().x <= -radius)
			{
				t.position.x = gfx.ScreenWidth + (radius + 1.0f);
			}
			else if (t.GetPosition().x > gfx.ScreenWidth + radius)
			{
				t.position.x = -(radius + 1.0f);
			}
			if (t.GetPosition().y <= -radius)
			{
				t.position.y = gfx.ScreenHeight + (radius + 1.0f);
			}
			else if (t.GetPosition().y > gfx.ScreenHeight + radius)
			{
				t.position.y = -(radius+1.0f);
			}
			pU->SetTransformation(t);
			velocity_sum += pU->rigidbody.velocity.Len();
		}
		i++;
	}
	i = 0;

	if (mouse)
	{

	}
}

void Game::ComposeFrame()		
{
	Color cx = Colors::Magenta;
	int i = 0;
	Unit* pU;
	while (i < UNITSLIMIT)
	{
		pU = &world.GetUnit(i);
		if (!pU->GetName().empty())
		{
			cx = Colors::Magenta;
			if (pU == world.bolinha)
			{
				cx = Colors::Yellow;
			}
			if (pU->rigidbody.arecolliding)
			{
				cx = Colors::Red;
			}
			if (pU->rigidbody.arebeinghit)
			{
				cx = Colors::Blue;
			}
			if (pU->rigidbody.form.GetType() == Form::Type::Point) // DRAW CIRCLES
			{
				gfx.DrawCircle(pU->rigidbody.GetVerticePos(0), pU->GetRadius(), cx);
				gfx.DrawLine(pU->rigidbody.GetVerticePos(0),
					pU->rigidbody.GetVerticePos(0) + GetRotated(pU->rigidbody.form.GetRadius(), pU->rigidbody.GetVerticeOri(0)), cx);
				//gfx.DrawLine(pU->rigidbody.GetVerticePos(0), world.GetPPhysicsSystem()->x_projection, cx);
				//gfx.DrawLine(pU->rigidbody.GetVerticePos(0), world.GetPPhysicsSystem()->y_projection, cx);
				//gfx.DrawLine(pU->rigidbody.GetVerticePos(0), world.GetPPhysicsSystem()->contact_point, cx);
				//gfx.DrawCircle(world.GetPPhysicsSystem()->x_projection, 12.0f, cx);
			}
			if (pU->rigidbody.form.GetType() == Form::Type::Line) // DRAW LINES
			{
				gfx.DrawCircleLine(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(1), pU->GetRadius(), cx);
				gfx.DrawLine(pU->rigidbody.GetVerticePos(0),
					pU->rigidbody.GetVerticePos(0) + GetRotated(pU->rigidbody.form.GetRadius(), pU->rigidbody.GetVerticeOri(0)), cx);
				gfx.DrawLine(pU->rigidbody.GetVerticePos(1),
					pU->rigidbody.GetVerticePos(1) + GetRotated(pU->rigidbody.form.GetRadius(), pU->rigidbody.GetVerticeOri(1)), cx);
			}
			if (pU->rigidbody.form.GetType() == Form::Type::Curve3P) // DRAW CURVES3P
			{
				gfx.DrawCircleCurve3P(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(1), pU->rigidbody.GetVerticePos(2), pU->GetRadius(), cx);
			}
		}
		i++;
	}
	gfx.DrawCurve3P(Vec2(0.0f, 0.0f), Vec2(500.0f, 0.0f), Vec2(1000.0f, 0.0f), cx);
	//gfx.DrawCurve3P(world.bolinha->rigidbody.GetVerticePos(0), world.linhagrande->rigidbody.GetVerticePos(0), world.linhagrande->rigidbody.GetVerticePos(1), cx);
	//gfx.DrawCurve3P(Vec2(0.0f), world.linhagrande->rigidbody.GetVerticePos(0), world.linhagrande->rigidbody.GetVerticePos(1), cx);
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
