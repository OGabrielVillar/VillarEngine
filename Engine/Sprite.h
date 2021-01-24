#pragma once

#include "Texture.h"

class SpriteFrame
{
public:
	SpriteFrame(int loaded_texture_id_in, int crop_start_x, int crop_start_y, int crop_end_x, int crop_end_y);
	SpriteFrame(int loaded_texture_id_in);
	SpriteFrame(const SpriteFrame& copy);
	int loaded_texture_id;
	int crop_start_x;
	int crop_start_y;
	int crop_end_x;
	int crop_end_y;
};

class Sprite
{
public:
	Sprite(int textures_size, int frames_size, SpriteFrame* frames_to_copy);
	//~Sprite();
private:
	int* textures_ids;
	int textures_amount;
	SpriteFrame* frames;
	int frames_amount;
};