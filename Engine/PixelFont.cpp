#include "PixelFont.h"

PixelFontChar::PixelFontChar() :
	texture(nullptr),
	txr_size(0),
	x_size(0),
	y_size(0),
	y_space(0)
{
}

PixelFontChar::PixelFontChar(bool* txr_in, unsigned int txr_size_in, unsigned char x_size_in, unsigned char y_size_in, unsigned char y_space_in) :
	texture(txr_in),
	txr_size(txr_size_in),
	x_size(x_size_in),
	y_size(y_size_in),
	y_space(y_space_in)
{
}

PixelFontChar::~PixelFontChar()
{
	delete[] texture;
}

PixelFontChar::PixelFontChar(PixelFontChar & const pixelfc_in) :
	texture(new bool[pixelfc_in.txr_size]),
	txr_size(pixelfc_in.txr_size),
	x_size(pixelfc_in.x_size),
	y_size(pixelfc_in.x_size),
	y_space(pixelfc_in.x_size)
{
	for (size_t i = 0; i < txr_size; i++)
	{
		texture[i] = pixelfc_in.texture[i];
	}
}

PixelFontChar & PixelFontChar::operator=(const PixelFontChar & rhs)
{
	txr_size = rhs.txr_size;
	x_size = rhs.x_size;
	y_size = rhs.y_size;
	y_space = rhs.y_space;

	delete[] texture;
	texture = new bool[txr_size];
	for (size_t i = 0; i < txr_size; i++)
	{
		texture[i] = rhs.texture[i];
	}
	return *this;
}

bool PixelFontChar::GetPixel(unsigned char x, unsigned char y) const
{
	return texture[x+((y-y_space)*x_size)];
}

PixelFont::PixelFont(unsigned char from_char_in, unsigned char to_char_in, unsigned char many_char_in, PixelFontChar* chars_in):
from_char(from_char_in),
to_char(to_char_in),
many_char(many_char_in),
chars(chars_in)
{
}

PixelFont::PixelFont(PixelFont & rhs) :
	from_char(rhs.from_char),
	to_char(rhs.to_char),
	many_char(rhs.many_char),
	chars(new PixelFontChar[rhs.many_char])
{
	for (size_t i = 0; i < many_char; i++)
	{
		chars[i] = rhs.chars[i];
	}
}

PixelFont::~PixelFont()
{
	delete[] chars;
}

PixelFontChar & PixelFont::GetCharGlyph(unsigned char char_in)
{
	return chars[int(char_in-from_char)];
}
