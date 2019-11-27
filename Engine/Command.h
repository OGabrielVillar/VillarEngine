#pragma once


class Command
{
public:
	Command() = default;
	Command(unsigned char key_in, unsigned int effect_id_in);
	unsigned char GetKey();
	unsigned int GetEffectID();
	bool KeyIs(unsigned char key_in);
private:
	unsigned char key;
	unsigned int effect_id;
};