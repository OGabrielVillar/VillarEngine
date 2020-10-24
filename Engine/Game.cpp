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
	world(),
	drawSystem(gfx,world)
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
				t.position.x = gfx.ScreenWidth + (radius + 2.0f);
			}
			else if (t.GetPosition().x >= gfx.ScreenWidth + radius)
			{
				t.position.x = -(radius + 2.0f);
			}
			if (t.GetPosition().y <= -radius)
			{
				t.position.y = gfx.ScreenHeight + (radius + 2.0f);
			}
			else if (t.GetPosition().y >= gfx.ScreenHeight + radius)
			{
				t.position.y = -(radius+2.0f);
			}
			pU->SetTransformation(t);
			velocity_sum += pU->rigidbody.velocity.Len();
		}
		i++;
	}
	i = 0;
	
	if (wnd.mouse.LeftIsPressed()){	
		world.userunit->rigidbody.SetPosition(Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()));
	}

	if (wnd.kbd.KeyIsPressed((char)104))
	{
		world.GetCamera()->SetTransformation(*world.GetCamera()->GetTransformation()+Transformation(Vec2(0.0f,-500.0f*ft.Get())));
	}

	if (wnd.kbd.KeyIsPressed((char)98))
	{
		world.GetCamera()->SetTransformation(*world.GetCamera()->GetTransformation() + Transformation(Vec2(0.0f, 500.0f*ft.Get())));
	}


	if (wnd.kbd.KeyIsPressed((char)102))
	{
		world.GetCamera()->SetTransformation(*world.GetCamera()->GetTransformation() + Transformation(Vec2(500.0f*ft.Get(), 0.0f)));
	}

	if (wnd.kbd.KeyIsPressed((char)100))
	{
		world.GetCamera()->SetTransformation(*world.GetCamera()->GetTransformation() + Transformation(Vec2(-500.0f*ft.Get(), 0.0f)));
	}

	if (wnd.kbd.KeyIsPressed((char)105))
	{
		Transformation rotation;
		rotation.RotatesBy(GetSinCosOfDegrees(0.7f*ft.Get()));
		world.GetCamera()->SetTransformation(*world.GetCamera()->GetTransformation() + rotation);
	}
	if (wnd.kbd.KeyIsPressed((char)103))
	{
		Transformation reversed_rotation;
		reversed_rotation.RotatesBy(GetSinCosOfDegrees(-0.7f*ft.Get()));
		world.GetCamera()->SetTransformation(*world.GetCamera()->GetTransformation() + reversed_rotation);
	}

	if (wnd.kbd.KeyIsPressed((char)32))
	{
		world.GetCamera()->SetTransformation(Transformation(Vec2(gfx.ScreenWidth / 2.0f, gfx.ScreenHeight / 2.0f)));
	}

	if (wnd.kbd.KeyIsPressed((char)107))
	{
		Transformation scale;
		scale.ScalesBy(1.05263f);
		world.GetCamera()->SetTransformation(*world.GetCamera()->GetTransformation() + scale);
	}

	if (wnd.kbd.KeyIsPressed((char)109))
	{
		Transformation scale;
		scale.ScalesBy(0.95f);
		world.GetCamera()->SetTransformation(*world.GetCamera()->GetTransformation() + scale);
	}
}

void Game::ComposeFrame()		
{
	drawSystem.Go(ft.Get());
}
