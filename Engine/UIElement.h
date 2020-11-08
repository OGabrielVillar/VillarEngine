#pragma once

#include "Transformation.h"
#include <iostream>

class UIElement
{
public:
	enum Type
	{
		Field,
		Image,
		Button,
		Tick,
		ScrollField,
		TextBox,
		RenderField,
		Mask
	};
	enum Side
	{
		TopLeft,
		Top,
		TopRight,
		Right,
		BottonRight,
		Botton,
		BottonLeft,
		Left,
		Center,
		Edge,
		OppositeEdge
	};
	UIElement();

public:
	Transformation trasformation;
	bool orientationlocked = true;
	Vei2 dimensions;
	Side attached_at;
	Side init_side;
	Side parent_attachment;
	UIElement* elements_inside = nullptr;
	UIElement* parent_element = nullptr;
};

class Field: public UIElement
{
	Field();
	Field(Type type_in, Side attached_at_in, Side init_side_in, const Vec2& dimensions);
};

class Image : public UIElement
{
};

class Button : public UIElement
{
};

class Tick : public UIElement
{
};

class ScrollField : public Field
{
};

class TextBox : public Field
{
};

class RenderField : public Field
{
};