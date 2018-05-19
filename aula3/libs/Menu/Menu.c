/*
 * Menu.c
 *
 *  Created on: May 19, 2018
 *      Author: fcgeh
 */

#include "Menu.h"

void _Menu_EnterPosition(uint8_t pos);

void Menu_Init()
{

}

void Menu_SetPosition(uint8_t pos, MenuItem *item)
{
	Menu.Items[pos] = item;
}

void _Menu_EnterPosition(uint8_t pos)
{
	Menu.Current = Menu.Items[pos];
	Menu.Current->Enter();
	Menu.NeedsRedraw = 1;
}

void Menu_Next()
{
	Menu.Index++;

	Menu.Current->Exit();
	if (Menu.Index >= MENU_ITEMS_COUNT)
		Menu.Index = 0;

	_Menu_EnterPosition(Menu.Index);
}

void Menu_Prev()
{
	Menu.Current->Exit();
	if (Menu.Index > 0)
		Menu.Index--;

	_Menu_EnterPosition(Menu.Index);
}

void Menu_SetKey(uint8_t key)
{
	Menu.Current->KeyPressed(key);
}

void Menu_Draw()
{
	Menu.NeedsRedraw = 1;
}

void Menu_Reset()
{
	Menu.Current->Exit();
	Menu.Index = 0;
	_Menu_EnterPosition(Menu.Index);
}

void Menu_Runtime()
{
	if (Menu.NeedsRedraw)
	{
		Menu.NeedsRedraw = 0;
		if (Menu.Current)
		{
			Menu.Current->Render();
		}
	}
}
