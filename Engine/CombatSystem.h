#pragma once
#define	EFFECTTEMPLATELIMIT 99
#define	EFFECTLIMIT 99
#define	COMMANDLIMIT 25

#include "Effect.h"
#include "Keyboard.h"
#include "IdList.h"

class CombatSystem
{
public:
	CombatSystem(IdList<Unit>* unit_list_in);
	void Go(float ft);

	void CheckForCommands();
	void CheckForEffects();

	void AddEffect(Effect effect_in, Unit* source_in);
	unsigned int AddEffectTemplate(Effect effect_in);

	void BindKeyboard(Keyboard& kbd_in);
private:
	Effect effects[EFFECTLIMIT];
	Effect effects_templates[EFFECTTEMPLATELIMIT];
	IdList<Unit>* il_units;
	Keyboard* kbd = nullptr;
	float ft;
};