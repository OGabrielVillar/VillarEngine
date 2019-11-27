#include "Command.h"

Command::Command(unsigned char key_in, unsigned int effect_id_in)
{
	key = key_in;
	effect_id = effect_id_in;
}

unsigned char Command::GetKey()
{
	return key;
}

unsigned int Command::GetEffectID()
{
	return effect_id;
}

bool Command::KeyIs(unsigned char key_in)
{
	return key_in == key;
}
