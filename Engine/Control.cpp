#include "Control.h"


Control::Control(CombatSystem & combatsys_in)
{
	Pcombatsystem = &combatsys_in;
}

void Control::CheckForKeys()
{
	if (selectedUnit != nullptr)
	{
		for (char i = 0; i < COMMANDCARDLENGHT; i++)
		{
			if (kbd->KeyIsPressed(selectedUnit->GetCommand(i).GetKey()))
			{
				int x = 0;
			}
		}
	}
}

void Control::SetSelectedUnit(Unit &unt)
{
	selectedUnit = &unt;
}

void Control::BindKeyboard(Keyboard & kbd_in)
{
	kbd = &kbd_in;
}
