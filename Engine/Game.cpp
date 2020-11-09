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
	world.GetCamera()->SetTransformation(Transformation(Vec2(gfx.ScreenWidth / 2.0f, gfx.ScreenHeight / 2.0f)));

	fs.OpenFile("test\test.txt");
	char xtest = fs.Read<char>();
	char ytest = fs.Read<char>();
	fs.Write<char>((char)40,"gugu");
	char ztest = fs.Read<char>();
	char wtest = fs.Read<char>();
	IdList<Vec2> lago;
	lago.PushElement(Vec2(1.0f));
	lago.PushElement(Vec2(3.0f));
	lago.PushElement(Vec2(5.0f));
	lago.PushElement(Vec2(5.0f));
	lago.PushElement(Vec2(5.0f));
	lago.PushElement(Vec2(5.0f));
	lago.PushElement(Vec2(5.0f));
	lago.PushElement(Vec2(5.0f));
	lago.PushElement(Vec2(5.0f));
	lago.PushElement(Vec2(8.0f));
	lago.PushElement(Vec2(5.0f));
	Vec2 testA = *lago[5];
	Vec2 testB = *lago[9];
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
	Vec2 rectBound = Vec2(gfx.ScreenWidth, gfx.ScreenHeight);
	Vec2 center = rectBound / 2.0f;
	Unit* pU;

	IdListReader<Unit> lr_pu(world.GetUnitIdList());

	while (!lr_pu.Ended())
	{
		pU = lr_pu.Get();
		if (pU->GetName().empty()){lr_pu.Next();continue;}

		Vec2 pu_position = pU->GetTransformation().GetPosition();
		if (DistSqr(pu_position, center) > DistSqr(center))
		{
			Vec2 rotation_matrix = (pU->GetTransformation().GetPosition() - center).GetNormalized();
			Vec2 velocity_in_matrix = GetRotated(pU->rigidbody.GetVelocity(),(GetInvertedAngle(rotation_matrix)));
			pU->rigidbody.SetVelocity(GetRotated(Vec2(velocity_in_matrix.x, -velocity_in_matrix.y), rotation_matrix));
			pU->SetPosition(center + (center - pU->GetTransformation().GetPosition()) + (rotation_matrix/10.0f));
		}

		lr_pu.Next();
	}

	if (wnd.mouse.LeftIsPressed()){	
		world.userunit->rigidbody.SetPosition(Vec2((float)wnd.mouse.GetPosX(), (float)wnd.mouse.GetPosY()));
	}
	float camera_velocity = (750.0f / world.GetCamera()->GetTransformation()->GetScale())*ft.Get();

	if (wnd.kbd.KeyIsPressed((char)104))
	{
		world.GetCamera()->GetTransformation()->MovesBy(Vec2(0.0f,-camera_velocity ));
	}

	if (wnd.kbd.KeyIsPressed((char)98))
	{
		world.GetCamera()->GetTransformation()->MovesBy(Vec2(0.0f, camera_velocity));
	}


	if (wnd.kbd.KeyIsPressed((char)102))
	{
		world.GetCamera()->GetTransformation()->MovesBy(Vec2(camera_velocity, 0.0f));
	}

	if (wnd.kbd.KeyIsPressed((char)100))
	{
		world.GetCamera()->GetTransformation()->MovesBy(Vec2(-camera_velocity, 0.0f));
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
		world.GetCamera()->GetTransformation()->ScalesBy(1.05263f);
	}

	if (wnd.kbd.KeyIsPressed((char)109))
	{
		world.GetCamera()->GetTransformation()->ScalesBy(0.95f);
	}
}

void Game::ComposeFrame()		
{
	drawSystem.Go(ft.Get());
}
