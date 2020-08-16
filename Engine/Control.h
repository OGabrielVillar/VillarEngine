#pragma once

#include "CombatSystem.h"
#include "Keyboard.h"

class Control
{
public:
	Control(CombatSystem& combatsys_in);
	void CheckForKeys();
	void SetSelectedUnit(Unit &unt);
	void BindKeyboard(Keyboard& kbd_in);
	Keyboard* kbd = nullptr;
private:
	Unit* selectedUnit = nullptr;
	CombatSystem* Pcombatsystem;
};