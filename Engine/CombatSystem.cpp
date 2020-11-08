#include "CombatSystem.h"

CombatSystem::CombatSystem(IdList<Unit>* unit_list_in)
{
	il_units = unit_list_in;
}

void CombatSystem::Go(float ft_in)
{
	ft = ft_in;

	CheckForCommands();
	CheckForEffects();
}

void CombatSystem::CheckForCommands()
{
	IdListReader<Unit> lr_Punit(il_units);

	for (size_t i = 0; i < il_units->ManyElements(); i++)
	{
		for (char i = 0; i < COMMANDCARDLENGHT; i++)
		{
			if (kbd->KeyIsPressed(lr_Punit.Get()->GetCommand(i).GetKey()))
			{
				AddEffect(effects_templates[lr_Punit.Get()->GetCommand(i).GetEffectID()],
					lr_Punit.Get());
			}
		}
		lr_Punit.Next();
	}
	lr_Punit.Reset();
}

void CombatSystem::CheckForEffects()
{
	for (char i = 0; i < EFFECTLIMIT; i++)
	{
		if (effects[i].isActive())
		{
			effects[i].ApplyFunctions(ft);
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
			effects_templates[i].ActivateEffect();
			return (unsigned int)i;
		}
	}
	return 0;
}

void CombatSystem::BindKeyboard(Keyboard & kbd_in)
{
	kbd = &kbd_in;
}

