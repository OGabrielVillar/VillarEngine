/*/#include "TextRendering.h"

void TextReader::font_parsed(void * args, void * _font_data, int error)
{
	if (error) {
		*(uint8_t*)args = error;
		printf("Unable to parse font\n");
	}
	else {
		TTFFontParser::FontData* font_data = (TTFFontParser::FontData*)_font_data;
		printf("Font %s parsed\n", font_data->full_font_name.c_str());
		printf("Number of glyphs: %d\n", font_data->glyphs.size());
		*(uint8_t*)args = 1;
	}
}

void TextReader::Go()
{
	uint8_t condition_variable = 0;

	TTFFontParser::FontData font_data;
	int8_t error = TTFFontParser::parse_file("test/fonts/cm-unicode/cmunrm.ttf", &font_data, font_parsed, &condition_variable);

	while (!condition_variable) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	getchar();
}

*/