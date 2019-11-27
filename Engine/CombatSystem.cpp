#include "CombatSystem.h"

CombatSystem::CombatSystem(Unit * unit_list_in)
{
	unit_list = unit_list_in;
}

void CombatSystem::Go()
{
	CheckForCommands();
	CheckForEffects();
}

void CombatSystem::CheckForCommands()
{
	for (size_t i = 0; i < UNITSLIMIT; i++)
	{
		for (char i = 0; i < COMMANDCARDLENGHT; i++)
		{
			if (kbd->KeyIsPressed(unit_list->GetCommand(i).GetKey()))
			{
				AddEffect(effects_templates[unit_list->GetCommand(i).GetEffectID()],
					unit_list);
			}
		}
		unit_list++;
	}
	unit_list -= UNITSLIMIT;
}

void CombatSystem::CheckForEffects()
{
	for (char i = 0; i < EFFECTLIMIT; i++)
	{
		if (effects[i].isActive())
		{
			effects[i].ApplyFunctions();
		}
	}
}

void CombatSystem::AddEffect(Effect effect_in, Unit* source_in)
{
	for (size_t i = 0; i < EFFECTLIMIT; i++)
	{
		if (!effects[i].isActive())
		{
			effects[i] = effect_in;
			effects[i].SetSourceUnit(source_in);
			effects[i].ActivateEffect();
			return;
		}
	}
}

unsigned int CombatSystem::AddEffectTemplate(Effect effect_in)
{
	for (size_t i = 0; i < EFFECTTEMPLATELIMIT; i++)
	{
		if (!effects_templates[i].isActive())
		{
			effects_templates[i] = effect_in;
			return (unsigned int)i;
		}
	}
}

void CombatSystem::BindKeyboard(Keyboard & kbd_in)
{
	kbd = &kbd_in;
}

