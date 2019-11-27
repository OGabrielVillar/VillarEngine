#pragma once

#define UNITSLIMIT 9
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
	void SetRadiusTo(float radius_in);
	void SetTransformation(Transformation transformation_in);
	void SetRigidBody(RigidBody rigidbody_in);
public: //GETTERS
	Vec2 GetPosition();
	Command& GetCommand(char index);
	std::string& GetName();
	float GetRadius();
	Transformation& GetTransformation();

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