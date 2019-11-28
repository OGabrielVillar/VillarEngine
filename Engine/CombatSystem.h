#pragma once
#define	EFFECTTEMPLATELIMIT 99
#define	EFFECTLIMIT 9
#define	COMMANDLIMIT 25

#include "Effect.h"
#include "Keyboard.h"

class CombatSystem
{
public:
	CombatSystem(Unit* unit_list_in);
	void Go(float ft);

	void CheckForCommands();
	void CheckForEffects();

	void AddEffect(Effect effect_in, Unit* source_in);
	unsigned int AddEffectTemplate(Effect effect_in);

	void BindKeyboard(Keyboard& kbd_in);
private:
	Effect effects[EFFECTLIMIT];
	Effect effects_templates[EFFECTTEMPLATELIMIT];
	Unit* unit_list;
	Keyboard* kbd = nullptr;
	float ft;
};