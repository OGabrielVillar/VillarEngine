#pragma once
class PixelFontChar
{
public:
	PixelFontChar();
	PixelFontChar(bool* txr_in, unsigned int txr_size_in, unsigned char x_size, unsigned char y_size, unsigned char y_space);
	~PixelFontChar();
	PixelFontChar(PixelFontChar & const pixelfc_in);
	PixelFontChar& operator=(const PixelFontChar& rhs);

	bool GetPixel(unsigned char x, unsigned char y) const;
	

public:
	bool* texture;
	unsigned int txr_size;
	unsigned char x_size;
	unsigned char y_size;
	unsigned char y_space;
};

class PixelFont
{
public:
	PixelFont(unsigned char from_char, unsigned char to_char, unsigned char many_char, PixelFontChar* chars_in);
	PixelFont(PixelFont& rhs);
	~PixelFont();
	PixelFontChar& GetCharGlyph(unsigned char char_in);
	const unsigned char from_char;
	const unsigned char to_char;
private:
	const unsigned char many_char;
	PixelFontChar* chars = nullptr;
};