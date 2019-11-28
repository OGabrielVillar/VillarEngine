#pragma once
class Material
{
public:
	Material();
	~Material();

public:
	float density;
	float restitution;
};

Material::Material()
{
}

Material::~Material()
{
}