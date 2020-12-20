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
	drawSystem(gfx,world),
	CamDefaultTransf(*world.GetCamera()->GetTransformation())
{
	defaultControl = world.GetControl();
	defaultControl->BindKeyboard(wnd.kbd);
	world.GetPCombatSystem()->BindKeyboard(wnd.kbd);

	fs.OpenFile("test\test.txt");
	char xtest = fs.Read<char>();
	char ytest = fs.Read<char>();
	fs.Write<char>((char)40,"gugu");
	char ztest = fs.Read<char>();
	char wtest = fs.Read<char>();
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
	Vec2 Bound = Vec2(25.0f, 25.0f);
	Vec2 center = Bound / 2.0f;
	Unit* pU;

	IdListReader<Unit> lr_pu(world.GetUnitIdList());

	while (!lr_pu.Ended())
	{
		if (!bound_active) { break; }
		pU = lr_pu.Get();
		if (pU->GetName().empty()) { lr_pu.Next(); continue; }

		Vec2 pu_position = pU->GetTransformation().GetPosition();
		if (DistSqr(pu_position) > DistSqr(center))
		{
			Vec2 rotation_matrix = pU->GetTransformation().GetPosition().GetNormalized();
			Vec2 velocity_in_matrix = GetRotated(pU->rigidbody.GetVelocity(), (GetInvertedAngle(rotation_matrix)));
			pU->rigidbody.SetVelocity(GetRotated(Vec2(velocity_in_matrix.x, -velocity_in_matrix.y), rotation_matrix));
			pU->SetPosition(-(rotation_matrix*(center.Len() - 1.0f)));
		}

		lr_pu.Next();
	}
	Controls();

	world.Go(ft.Mark());




}

void Game::Controls()
{
	if (true)
	{

	}

	float camera_velocity = (1.0f / (world.GetCamera()->GetTransformation()->GetScale() * world.GetCamera()->zoom)) * ft.Get();

	if (wnd.kbd.KeyIsPressed((char)104))
	{
		world.GetCamera()->GetTransformation()->MovesBy(Vec2(0.0f, -camera_velocity));
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
		world.GetCamera()->SetTransformation(CamDefaultTransf);
	}

	if (wnd.kbd.KeyIsPressed((char)107))
	{
		world.GetCamera()->zoom *= 1.05263f;
	}

	if (wnd.kbd.KeyIsPressed((char)109))
	{
		world.GetCamera()->zoom *= 0.95f;
	}

	if (wnd.kbd.KeyIsPressed((char)112))
	{
		bound_active = !bound_active;
	}
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
	WPosition a;
	WPosition b;

	WPosition userunit_position(world.userunit->GetTransformation().GetWPosition());
	font.DrawText(
		"User Position\nx: " + std::to_string(userunit_position.x) + "(" + std::to_string(userunit_position.x_chunk)
		+ ")\ny: " + std::to_string(userunit_position.y) + "(" + std::to_string(userunit_position.y_chunk)
		+ ")"
		, Vei2(gfx.ScreenHeight-40, 40), Colors::Yellow, gfx);


	WPosition mousewp(GetMouseWorldPosition());
	font.DrawText(	"Mouse Position\nx: "	+ std::to_string(mousewp.x)	+ "(" + std::to_string(mousewp.x_chunk)
	+				")\ny: " + std::to_string(mousewp.y) + "(" + std::to_string(mousewp.y_chunk)
	+				")\nx: "	+ std::to_string(mousewp.GetPosition().x)
	+				")\ny: " + std::to_string(mousewp.GetPosition().y)
	+				")"
	, Vei2(40, 40), Colors::Yellow, gfx);
	if (wnd.mouse.LeftIsPressed())
	{
		if (!lefthasbeenpressed)
		{
			left_clickLastPos.Reset();
			left_clickPos = mousewp;
			left_camInitialPos = world.GetCamera()->GetTransformation()->GetWPosition();
			lefthasbeenpressed = true;
		}
		WPosition offset = (mousewp - left_clickPos) + left_clickLastPos;
		left_clickLastPos = offset;
		world.GetCamera()->GetTransformation()->MoveTo(left_camInitialPos - offset);

		//font.DrawText(
		//	"Mouse Position\nx: " + std::to_string(offset.x) + "(" + std::to_string(offset.x_chunk)
		//	+ ")\ny: " + std::to_string(offset.y) + "(" + std::to_string(offset.y_chunk)
		//	+ ")"
		//	, Vei2(40, 180), Colors::Yellow, gfx);
	}
	else
	{
		lefthasbeenpressed = false;
	}
}

WPosition Game::GetMouseWorldPosition()
{
	Vec2 center(gfx.ScreenWidth / 2.0f, gfx.ScreenHeight / 2.0f);
	Transformation  matrix(*world.GetCamera()->GetTransformation());
	float zoom(world.GetCamera()->zoom);
	matrix.ScalesBy(zoom);
	Transformation screen_position(Vec2(((float)wnd.mouse.GetPosX() - center.x)/zoom, ((float)wnd.mouse.GetPosY() - center.y)/zoom));
	
	return WPosition((matrix + Transformation(screen_position)).GetWPosition());
}

WPosition Game::GetScreenWorldPosition(const Vec2& screen_pos)
{
	Vec2 center(gfx.ScreenWidth / 2.0f, gfx.ScreenHeight / 2.0f);
	Transformation  matrix(*world.GetCamera()->GetTransformation());
	float zoom(world.GetCamera()->zoom * center.Len());
	matrix.ScalesBy(zoom);
	Transformation screen_position(Vec2((screen_pos.x - center.x) / zoom, (screen_pos.y - center.y) / zoom));

	return WPosition((matrix + Transformation(screen_position)).GetWPosition());
}

void Game::ComposeFrame()		
{
	drawSystem.Go(ft.Get());
	if (!bound_active)
	{
		gfx.DrawCircle(Vec2(5.0f), 4.0f, Colors::Green);
	}
	else
	{
		gfx.DrawCircle(Vec2(5.0f), 4.0f, Colors::Red);
	}
}
