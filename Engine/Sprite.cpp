#include "Sprite.h"

Sprite::Sprite(int textures_size, int frames_size, SpriteFrame* frames_to_copy):
textures_amount(textures_size),
frames_amount(frames_size),
textures_ids(new int[textures_size]),
frames(new SpriteFrame[frames_size] { *frames_to_copy })
{
}

SpriteFrame::SpriteFrame(int loaded_texture_id_in, int crop_start_x_in, int crop_start_y_in, int crop_end_x_in, int crop_end_y_in):
loaded_texture_id(loaded_texture_id_in),
crop_start_x(crop_start_x_in),
crop_start_y(crop_start_y_in),
crop_end_x(crop_end_x_in),
crop_end_y(crop_end_y_in)
{
}

SpriteFrame::SpriteFrame(int loaded_texture_id_in) :
	loaded_texture_id(loaded_texture_id_in),
	crop_start_x(0),
	crop_start_y(0),
	crop_end_x(0),
	crop_end_y(0)
{
}

SpriteFrame::SpriteFrame(const SpriteFrame&  copy) :
	loaded_texture_id(copy.loaded_texture_id),
	crop_start_x(copy.crop_start_x),
	crop_start_y(copy.crop_start_y),
	crop_end_x(copy.crop_end_x),
	crop_end_y(copy.crop_end_y)
{
}
