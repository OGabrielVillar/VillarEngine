#pragma once

#include "PixelFont.h"
#include "Texture.h"

inline PixelFont ConvertBMPinPixelFont(Texture& txr_in,unsigned char chars_height,unsigned char start_at_char)
{
	const unsigned int trx_x_size(txr_in.GetWidth());
	const unsigned int trx_y_size(txr_in.GetHeight());
	const int many_chars(trx_y_size/chars_height);

	unsigned int buffer_maximum_size = trx_x_size * chars_height;
	PixelFontChar* chars(new PixelFontChar[many_chars]);

	for (size_t char_id = 0; char_id < many_chars; char_id++)
	{
		unsigned int y_start(char_id*chars_height);
		unsigned char char_x_size(trx_x_size);
		unsigned char char_y_size(chars_height);
		unsigned char char_y_space(0);
		bool* buffer(new bool[buffer_maximum_size]);
		unsigned int pixel_count(0);


		for (size_t y = y_start; y < y_start + char_y_size; y++)
		{
			Color pixel(txr_in.GetPixel(0, y));


			if (pixel == Colors::Magenta)
			{
				if ((y-y_start)-char_y_space == 0)
				{
					char_y_space++;
					continue;
				}
				else
				{
					char_y_size = y-y_start;
					break;
				}
			} else if (pixel == Colors::White)
			{
				buffer[pixel_count] = true;
				pixel_count++;
			}
			else 
			{
				buffer[pixel_count] = false;
				pixel_count++;
			}

			for (size_t x = 1; x < char_x_size; x++)
			{
				pixel = txr_in.GetPixel(x, y);
				if (pixel == Colors::White)
				{
					buffer[pixel_count] = true;
					pixel_count++;
				}
				else if (pixel == Colors::Magenta)
				{
					char_x_size = x;
					break;
				}
				else
				{
					buffer[pixel_count] = false;
					pixel_count++;
				}
			}
		}


		bool* end_txr(new bool[pixel_count]);
		for (size_t i = 0; i < pixel_count; i++)
		{
			end_txr[i] = buffer[i];
		}
		chars[char_id] = PixelFontChar(end_txr, pixel_count, char_x_size, char_y_size, char_y_space);
		delete[] buffer;
	}

	return PixelFont(start_at_char, start_at_char + many_chars, many_chars, chars);
}