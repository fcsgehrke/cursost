/*
 * Menu.h
 *
 *  Created on: May 19, 2018
 *      Author: fcgeh
 */

#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>

#define MENU_ITEMS_COUNT 4

typedef void (*OnEnter)();
typedef void (*OnRender)();
typedef void (*OnKey)(char key);
typedef void (*OnExit)();

typedef struct _MenuItem
{
	OnEnter Enter;
	OnRender Render;
	OnKey KeyPressed;
	OnExit Exit;
} MenuItem;

struct _Menu
{
	uint8_t NeedsRedraw;
	uint8_t Index;
	MenuItem* Current;
	MenuItem* Items[MENU_ITEMS_COUNT];
} Menu;

void Menu_Init();
void Menu_SetPosition(uint8_t pos, MenuItem *item);
void Menu_Next();
void Menu_Prev();
void Menu_Reset();
void Menu_Runtime();
void Menu_SetKey(uint8_t key);
// Required execution rate = 50hz;
void Menu_Draw();

#endif /* MENU_H_ */
