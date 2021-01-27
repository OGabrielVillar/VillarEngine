#include "DrawSystem.h"

DrawSystem::DrawSystem(Graphics& gfx_in, World& world_in, MotionSystem& motionSystem_in, MemoryManager& memoryManager_in) :
	gfx(&gfx_in),
	world(&world_in),
	motionSystem(&motionSystem_in),
	memoryManager(&memoryManager_in),
	arial(ConvertBMPinPixelFont(Texture("PF_arial.bmp"), 10, 33))
{
	UIElement xx;
	screen.elements_inside = &xx;

	memoryManager->InitTextureBlock(5);
	memoryManager->LoadTexture(0, "stevie.bmp");
	memoryManager->LoadTexture(1, "tatuzin00.bmp");
	memoryManager->LoadTexture(2, "tatuzin01.bmp");
	memoryManager->LoadTexture(3, "tatuzin02.bmp");
	memoryManager->LoadTexture(4, "tatuzin03.bmp");


	motionSystem->AddFloatMotion(new Reference<float>(&_animation_test));
	const unsigned int test_array_size(8);
	float test_array_times[test_array_size] = { 5.0f,0.03f,0.20f,3.5f,1.0f,0.5f,0.5f,0.03f };
	float test_array_values[test_array_size] = { 1.0f,2.0f,3.0f,4.0f,3.0f,2.0f,3.0f,2.0f };
	motionSystem->GetLastFloatMotion().SetUpKeys(test_array_times, test_array_values, test_array_size);
}

void DrawSystem::Go(float ft_in)
{
	ft = ft_in;
	mouse_in_world = GetMouseWorldPosition();
	ComposeFrame();
}

void DrawSystem::ComposeFrame()
{

	Vec2 center = Vec2(gfx->ScreenWidth / 2.0f, gfx->ScreenHeight / 2.0f);

	Transformation matrix = *world->GetCamera()->GetTransformation();
	matrix.ScalesBy(world->GetCamera()->zoom);


	gfx->DrawCircleFilled((matrix - Transformation(Vec2(0.0f))).GetPosition() + center, 12.5f * matrix.GetScale(), Color(43, 15, 13));

	//gfx->DrawLine((*matrix - Transformation(Vec2(0.0f, 0.0f))).GetPosition() + center, 
	//	(*matrix - Transformation(Vec2(gfx->ScreenWidth, 0.0f))).GetPosition() + center, Colors::Green);
	//gfx->DrawLine((*matrix - Transformation(Vec2(gfx->ScreenWidth, 0.0f))).GetPosition() + center,
	//	(*matrix - Transformation(Vec2(gfx->ScreenWidth, gfx->ScreenHeight))).GetPosition() + center, Colors::Green);
	//gfx->DrawLine((*matrix - Transformation(Vec2(gfx->ScreenWidth, gfx->ScreenHeight))).GetPosition() + center,
	//	(*matrix - Transformation(Vec2(0.0f, gfx->ScreenHeight))).GetPosition() + center, Colors::Green);
	//gfx->DrawLine((*matrix - Transformation(Vec2(0.0f, gfx->ScreenHeight))).GetPosition() + center,
	//	(*matrix - Transformation(Vec2(0.0f, 0.0f))).GetPosition() + center, Colors::Green);


	GridRender();

	gfx->DrawCircle((matrix - Transformation(Vec2(0.0f))).GetPosition() + center, 12.5f * matrix.GetScale(), Color(22, 31, 28));

	gfx->DrawTexture(memoryManager->GetTexture(0), (matrix - Transformation(Vec2(18.0f,0.0f))).GetPosition() + center, Vec2(19.5f, 18.0f), 1.0f / 200.0f * matrix.GetScale(), GetInvertedAngle(matrix.GetOrientation()));

	Unit* pU;

	IdListReader<Unit> lr_pu(world->GetUnitIdList());

	Color cx = Colors::White;
	while (!lr_pu.Ended())
	{
		pU = lr_pu.Get();
		if (!pU->GetName().empty())
		{
			Transformation puTransf = matrix - pU->GetTransformation();
			float pu0Radius = pU->GetRadiusSqrd()*puTransf.GetScale();
			//if (DistSqr(center) < DistSqr(puTransf.GetPosition()))
			//{
			//	lr_pu.Next();
			//	continue;
			//}
			//

			cx = Colors::White;
			if (pU == world->userunit)
			{
				cx = Colors::Yellow;
				Transformation pu_v0Transf = matrix - pU->rigidbody.GetVerticeTransf(0);
				Vec2 pu_v0Position = pu_v0Transf.GetPosition() + center;
				Transformation pu_v0Transftest = matrix - Transformation(pU->rigidbody.GetCOM());
				Vec2 pu_v0Positiontest = pu_v0Transftest.GetPosition() + center;
				float pu_v0Radius = pU->GetFormRadius()*pu_v0Transf.GetScale();
				gfx->DrawTexture(memoryManager->GetTexture((int)_animation_test), pu_v0Position, Vec2(19.5f,18.0f), pu_v0Radius/20.0f, pu_v0Transf.GetOrientation());
				
				lr_pu.Next();
				continue;
			}
			//if (pU->rigidbody.arecolliding){cx = Colors::Red;}
			//if (pU->rigidbody.arebeinghit){cx = Colors::Blue;}
			if (pU->rigidbody.form.GetType() == Form::Type::Point) // DRAW CIRCLES
			{
				Transformation pu_v0Transf = matrix - pU->rigidbody.GetVerticeTransf(0);
				Vec2 pu_v0Position = pu_v0Transf.GetPosition() + center;
				float pu_v0Radius = pU->GetFormRadius()*pu_v0Transf.GetScale();
				gfx->DrawCircle(pu_v0Position, pu_v0Radius, cx);
				gfx->DrawLine(pu_v0Position, pu_v0Position + GetRotated(pu_v0Radius, pu_v0Transf.GetOrientation()), cx);

				//gfx->DrawLine(pU->rigidbody.GetVerticePos(0), world.GetPPhysicsSystem()->x_projection, cx);
				//gfx->DrawLine(pU->rigidbody.GetVerticePos(0), world.GetPPhysicsSystem()->y_projection, cx);
				//gfx->DrawLine(world.GetPPhysicsSystem()->contact_point, world.GetPPhysicsSystem()->collision_point, cx);
				//gfx->DrawLine(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(0)+(-pU->rigidbody.velocity * ft.Get()), Colors::Cyan);
				//gfx->DrawCircle(world.GetPPhysicsSystem()->x_projection, 12.0f, cx);
			}
			else if (pU->rigidbody.form.GetType() == Form::Type::Line) // DRAW LINES
			{
				Transformation pu_v0Transf = matrix - pU->rigidbody.GetVerticeTransf(0);
				Vec2 pu_v0Position = pu_v0Transf.GetPosition() + center;
				float pu_v0Radius = pU->GetFormRadius()*pu_v0Transf.GetScale();
				Transformation pu_v1Transf = matrix - pU->rigidbody.GetVerticeTransf(1);
				Vec2 pu_v1Position = pu_v1Transf.GetPosition() + center;
				float pu_v1Radius = pU->GetFormRadius()*pu_v1Transf.GetScale();
				gfx->DrawCircleLine(pu_v0Position, pu_v1Position, pu_v0Radius, cx);
				gfx->DrawLine(pu_v0Position,
					pu_v0Position + GetRotated(pu_v0Radius, pu_v0Transf.GetOrientation()), cx);
				gfx->DrawLine(pu_v1Position,
					pu_v1Position + GetRotated(pu_v1Radius, pu_v1Transf.GetOrientation()), cx);
			}
			else if (pU->rigidbody.form.GetType() == Form::Type::Curve3P) // DRAW CURVES3P
			{
				//gfx->DrawCurve3Ptestes(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(1), pU->rigidbody.GetVerticePos(2), pU->GetRadius(), Colors::Blue);
				//gfx->DrawCircleCurve3P(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(1), pU->rigidbody.GetVerticePos(2), pU->GetRadius(), cx);
				//gfx->DrawCurve3P(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(1), pU->rigidbody.GetVerticePos(2), cx);
			}
			//gfx->DrawCircle(world.GetPPhysicsSystem()->contacts[0],10.0f,Colors::Red);
		}
		lr_pu.Next();
	}



	//curves
	 
	//gfx->DrawCurve3P(Vec2(0.0f, 0.0f), Vec2(500.0f, 0.0f), Vec2(1000.0f, 0.0f), cx);
	////gfx->DrawCurve3P(world.bolinha->rigidbody.GetVerticePos(0), world.linhagrande->rigidbody.GetVerticePos(0), world.linhagrande->rigidbody.GetVerticePos(1), cx);
	////gfx->DrawCurve3P(Vec2(0.0f), world.linhagrande->rigidbody.GetVerticePos(0), world.linhagrande->rigidbody.GetVerticePos(1), cx);
	//
	//
	////link.Draw( gfx );
	//gfx->PutPixel(500, 500, Colors::Magenta);
	////font.DrawText( "Becky.\nLemme smash.",wnd.mouse.GetPos() - Vei2{ 50,150 },Colors::White,gfx );
	//if (trigger >= 60)
	//{
	//	string = std::string("\nFps: " + std::to_string(1 / ft.Get()) );
	//	list.PushElement(string);
	//	trigger = 0;
	//}
	//finalString = '0';
	//for (int i = 0; i < list.capacity(); i++)
	//{
	//	finalString += list[i];
	//}
	//font.DrawText(finalString, textPos, Colors::Yellow, gfx);
	//for (size_t i = 0; i < 20000000; i++)
	//{
	//	char a = 0;
	//	a = 1;
	//}
	//trigger ++;



	gfx->DrawString("Mouse Position\nx: " + std::to_string(mouse_in_world.x) + "(" + std::to_string(mouse_in_world.x_chunk)
		+ ")\ny: " + std::to_string(mouse_in_world.y) + "(" + std::to_string(mouse_in_world.y_chunk)
		+ ")"
		, arial, 40, 40, Colors::White);
}

void DrawSystem::BindControls(Keyboard & kbd_in, Mouse & mse_in)
{
	kbd = &kbd_in;
	mse = &mse_in;
}

WPosition DrawSystem::GetMouseWorldPosition()
{
		Vec2 center(gfx->ScreenWidth / 2.0f, gfx->ScreenHeight / 2.0f);
		Transformation  matrix(*world->GetCamera()->GetTransformation());
		float zoom(world->GetCamera()->zoom);
		matrix.ScalesBy(zoom);
		Transformation screen_position(Vec2(((float)mse->GetPosX() - center.x) / zoom, ((float)mse->GetPosY() - center.y) / zoom));

		return WPosition((matrix + Transformation(screen_position)).GetWPosition());
}

void DrawSystem::GridRender()
{
	//GRID RENDERING:
	Vec2 center = Vec2(gfx->ScreenWidth / 2.0f, gfx->ScreenHeight / 2.0f);
	Transformation matrix = *world->GetCamera()->GetTransformation();
	float cam_scale = 1.0f * world->GetCamera()->zoom;
	matrix.ScalesBy(cam_scale);

	float threshold = 0.028f / cam_scale;
	if (threshold < 1.0f)
	{
		Vec2 cam_orientation(matrix.GetOrientation());
		Vec2 cam_position(matrix.GetPosition());
		Vec2 a_corner(GetRotated(-center, cam_orientation) / cam_scale);
		Vec2 b_corner(GetRotated(Vec2(-center.x, center.y), cam_orientation) / cam_scale);
		float initial_x = std::abs(a_corner.x);
		float initial_y = std::abs(a_corner.y);
		if (initial_x < std::abs(b_corner.x))
		{
			initial_x = std::abs(b_corner.x);
		}
		if (initial_y < std::abs(b_corner.y))
		{
			initial_y = std::abs(b_corner.y);
		}
		float endin_x = cam_position.x + initial_x;
		float endin_y = cam_position.y + initial_y;
		float start_x = cam_position.x - initial_x;
		float start_y = cam_position.y - initial_y;
		for (float x = (float)((int)start_x - ((int)start_x % 256) - 128);
			x <= endin_x; x += 256.0f)
		{
			gfx->DrawLine((matrix - Transformation(Vec2(x, start_y))).GetPosition() + center, (matrix - Transformation(Vec2(x, endin_y))).GetPosition() + center
				, Color((unsigned char)(32.0f - (threshold* threshold * 32.0f)), (unsigned char)(32.0f - (threshold * threshold * 32.0f)), (unsigned char)(64.0f - (threshold * 64.0f))));
		}
		for (float y = (float)((int)start_y - ((int)start_y % 256) - 128);
			y <= endin_y; y += 256.0f)
		{
			gfx->DrawLine((matrix - Transformation(Vec2(start_x, y))).GetPosition() + center, (matrix - Transformation(Vec2(endin_x, y))).GetPosition() + center
				, Color((unsigned char)(32.0f - (threshold* threshold * 32.0f)), (unsigned char)(32.0f - (threshold * threshold * 32.0f)), (unsigned char)(64.0f - (threshold * 64.0f))));
		}
	}
}

