#include "DrawSystem.h"

DrawSystem::DrawSystem(Graphics& const gfx_in, World& const world_in)
{
	gfx = &gfx_in;
	world = &world_in;
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
	int i = 0;
	Unit* pU;
	gfx->DrawLine((*matrix - Transformation(Vec2(0.0f, 0.0f))).GetPosition() + center, 
		(*matrix - Transformation(Vec2(gfx->ScreenWidth, 0.0f))).GetPosition() + center, Colors::Green);
	gfx->DrawLine((*matrix - Transformation(Vec2(gfx->ScreenWidth, 0.0f))).GetPosition() + center,
		(*matrix - Transformation(Vec2(gfx->ScreenWidth, gfx->ScreenHeight))).GetPosition() + center, Colors::Green);
	gfx->DrawLine((*matrix - Transformation(Vec2(gfx->ScreenWidth, gfx->ScreenHeight))).GetPosition() + center,
		(*matrix - Transformation(Vec2(0.0f, gfx->ScreenHeight))).GetPosition() + center, Colors::Green);
	gfx->DrawLine((*matrix - Transformation(Vec2(0.0f, gfx->ScreenHeight))).GetPosition() + center,
		(*matrix - Transformation(Vec2(0.0f, 0.0f))).GetPosition() + center, Colors::Green);
	while (i < UNITSLIMIT)
	{
		pU = &world->GetUnit(i);
		if (!pU->GetName().empty())
		{
			cx = Colors::White;
			if (pU == world->userunit)
			{
				cx = Colors::Yellow;
			}
			//if (pU->rigidbody.arecolliding){cx = Colors::Red;}
			//if (pU->rigidbody.arebeinghit){cx = Colors::Blue;}
			if (pU->rigidbody.form.GetType() == Form::Type::Point) // DRAW CIRCLES
			{
				Transformation puTransf = *matrix - pU->rigidbody.GetVerticeTransf(0);
				Vec2 puPosition = puTransf.GetPosition() + center;
				float puRadius = pU->GetRadius()*puTransf.GetScale();
				gfx->DrawCircle(puPosition, puRadius, cx);
				gfx->DrawLine(puPosition, puPosition + GetRotated(puRadius, puTransf.GetOrientation()), cx);

				//gfx->DrawLine(pU->rigidbody.GetVerticePos(0), world.GetPPhysicsSystem()->x_projection, cx);
				//gfx->DrawLine(pU->rigidbody.GetVerticePos(0), world.GetPPhysicsSystem()->y_projection, cx);
				//gfx->DrawLine(world.GetPPhysicsSystem()->contact_point, world.GetPPhysicsSystem()->collision_point, cx);
				//gfx->DrawLine(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(0)+(-pU->rigidbody.velocity * ft.Get()), Colors::Cyan);
				//gfx->DrawCircle(world.GetPPhysicsSystem()->x_projection, 12.0f, cx);
			}
			else if (pU->rigidbody.form.GetType() == Form::Type::Line) // DRAW LINES
			{
				Transformation pu0Transf = *matrix - pU->rigidbody.GetVerticeTransf(0);
				Vec2 pu0Position = pu0Transf.GetPosition() + center;
				float pu0Radius = pU->GetRadius()*pu0Transf.GetScale();
				Transformation pu1Transf = *matrix - pU->rigidbody.GetVerticeTransf(1);
				Vec2 pu1Position = pu1Transf.GetPosition() + center;
				float pu1Radius = pU->GetRadius()*pu1Transf.GetScale();
				gfx->DrawCircleLine(pu0Position, pu1Position, pu0Radius, cx);
				gfx->DrawLine(pu0Position,
					pu0Position + GetRotated(pu0Radius, pu0Transf.GetOrientation()), cx);
				gfx->DrawLine(pu1Position,
					pu1Position + GetRotated(pu1Radius, pu1Transf.GetOrientation()), cx);
			}
			else if (pU->rigidbody.form.GetType() == Form::Type::Curve3P) // DRAW CURVES3P
			{
				//gfx->DrawCurve3Ptestes(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(1), pU->rigidbody.GetVerticePos(2), pU->GetRadius(), Colors::Blue);
				//gfx->DrawCircleCurve3P(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(1), pU->rigidbody.GetVerticePos(2), pU->GetRadius(), cx);
				//gfx->DrawCurve3P(pU->rigidbody.GetVerticePos(0), pU->rigidbody.GetVerticePos(1), pU->rigidbody.GetVerticePos(2), cx);
			}
			//gfx->DrawCircle(world.GetPPhysicsSystem()->contacts[0],10.0f,Colors::Red);
		}
		i++;
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

