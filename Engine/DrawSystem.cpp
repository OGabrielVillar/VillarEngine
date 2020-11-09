#include "DrawSystem.h"

DrawSystem::DrawSystem(Graphics& gfx_in, World& world_in)
{
	gfx = &gfx_in;
	world = &world_in;
	UIElement xx;
	screen.elements_inside = &xx;
}

void DrawSystem::Go(float ft_in)
{
	ft = ft_in;
	ComposeFrame();
}

void DrawSystem::ComposeFrame()
{
	Transformation* matrix = world->GetCamera()->GetTransformation();
	Vec2 center = Vec2(gfx->ScreenWidth / 2.0f, gfx->ScreenHeight / 2.0f);
	Color cx = Colors::White;
	//gfx->DrawLine((*matrix - Transformation(Vec2(0.0f, 0.0f))).GetPosition() + center, 
	//	(*matrix - Transformation(Vec2(gfx->ScreenWidth, 0.0f))).GetPosition() + center, Colors::Green);
	//gfx->DrawLine((*matrix - Transformation(Vec2(gfx->ScreenWidth, 0.0f))).GetPosition() + center,
	//	(*matrix - Transformation(Vec2(gfx->ScreenWidth, gfx->ScreenHeight))).GetPosition() + center, Colors::Green);
	//gfx->DrawLine((*matrix - Transformation(Vec2(gfx->ScreenWidth, gfx->ScreenHeight))).GetPosition() + center,
	//	(*matrix - Transformation(Vec2(0.0f, gfx->ScreenHeight))).GetPosition() + center, Colors::Green);
	//gfx->DrawLine((*matrix - Transformation(Vec2(0.0f, gfx->ScreenHeight))).GetPosition() + center,
	//	(*matrix - Transformation(Vec2(0.0f, 0.0f))).GetPosition() + center, Colors::Green);
	gfx->DrawCircle((*matrix - Transformation(center)).GetPosition() + center, center.Len() * matrix->GetScale(), Colors::White);

	Unit* pU;

	IdListReader<Unit> lr_pu(world->GetUnitIdList());

	while (!lr_pu.Ended())
	{
		pU = lr_pu.Get();
		if (!pU->GetName().empty())
		{
			Transformation puTransf = *matrix - pU->GetTransformation();
			float pu0Radius = pU->GetRadiusSqrd()*puTransf.GetScale();
			if (DistSqr(center) < DistSqr(puTransf.GetPosition()))
			{
				lr_pu.Next();
				continue;
			}


			cx = Colors::White;
			if (pU == world->userunit)
			{
				cx = Colors::Yellow;
			}
			//if (pU->rigidbody.arecolliding){cx = Colors::Red;}
			//if (pU->rigidbody.arebeinghit){cx = Colors::Blue;}
			if (pU->rigidbody.form.GetType() == Form::Type::Point) // DRAW CIRCLES
			{
				Transformation pu_v0Transf = *matrix - pU->rigidbody.GetVerticeTransf(0);
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
				Transformation pu_v0Transf = *matrix - pU->rigidbody.GetVerticeTransf(0);
				Vec2 pu_v0Position = pu_v0Transf.GetPosition() + center;
				float pu_v0Radius = pU->GetFormRadius()*pu_v0Transf.GetScale();
				Transformation pu_v1Transf = *matrix - pU->rigidbody.GetVerticeTransf(1);
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
}

