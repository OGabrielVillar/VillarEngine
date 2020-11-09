#pragma once

//#define UNITSLIMIT 99
#define COMMANDCARDLENGHT 9

#include "Transformation.h"
#include "Command.h"
#include "RigidBody.h"
#include <iostream>

class Unit
{
public:
	Unit();
	Unit(std::string name_in, Transformation transf_in);
	void AddCommand(Command cmd);
public: //SETTERS
	void SetRadius(float radius_in);
	void SetDensity(float density_in);
	void SetTransformation(Transformation transformation_in);
	void SetPosition(Vec2& position_in);
	void SetRigidBody(RigidBody rigidbody_in);
	void SetRigidBodyForm(Form form_in);
public: //GETTERS
	Command& GetCommand(char index);
	std::string& GetName();
	float GetRadiusSqrd() const;
	float GetFormRadius() const;
	Transformation GetTransformation();

	RigidBody rigidbody;
private:
	std::string name;
	Transformation transformation;
	float radius;
	Command commandCard[COMMANDCARDLENGHT] = { Command(0,0) };
private:
	void CreateDefaultRigidBody();
	bool isDefautBody = 0;
};