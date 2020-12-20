#pragma once

#include "Colors.h"
#include <string>
#include "RectI.h"

class Texture
{
public:
	Texture( const std::string& filename );
	Texture( int width,int height );
	Texture( const Texture& );
	~Texture();
	Texture& operator=( const Texture& );
	void PutPixel( int x,int y,Color c );
	Color GetPixel( int x,int y ) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};