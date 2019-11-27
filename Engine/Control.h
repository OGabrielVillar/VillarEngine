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
private:
	Unit* selectedUnit = nullptr;
	Keyboard* kbd = nullptr;
	CombatSystem* Pcombatsystem;
};