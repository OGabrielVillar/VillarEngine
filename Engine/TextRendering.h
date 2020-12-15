#pragma once
#include <stdio.h>
#include <chrono>
#include <thread>

//#define TTF_FONT_PARSER_IMPLEMENTATION
//#include "ttfParser.h"
//#include "Graphics.h"


class TextReader
{
public:
	TextReader() = default;
	~TextReader() = default;
	void font_parsed(void * args, void * _font_data, int error);
	void Go();
private:

};