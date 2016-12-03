/*
    Furnace
    Copyright (C) 2015-2016 Demonic Benefactor <demonic@tutanota.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef __handleEvents__
#define __handleEvents__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "vectors.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

struct {
	//Transition storage to pass to the player state
	//All direction inputs dump into these integers
	int P1_UPDOWN;
	int P1_LEFTRIGHT;
	int P2_UPDOWN;
	int P2_LEFTRIGHT;
	//Player One Keyboard
	Sint32 P1K_UP;
	Sint32 P1K_DOWN;
	Sint32 P1K_LEFT;
	Sint32 P1K_RIGHT;
	Sint32 P1K_LIGHTPUNCH;
	Sint32 P1K_MEDIUMPUNCH;
	Sint32 P1K_HARDPUNCH;
	Sint32 P1K_LIGHTKICK;
	Sint32 P1K_MEDIUMKICK;
	Sint32 P1K_HARDKICK;
	//Player One Controller
	SDL_JoystickID P1_Controller;
	Uint8 P1C_LIGHTPUNCH;
	Uint8 P1C_MEDIUMPUNCH;
	Uint8 P1C_HARDPUNCH;
	Uint8 P1C_LIGHTKICK;
	Uint8 P1C_MEDIUMKICK;
	Uint8 P1C_HARDKICK;
	Uint8 P1C_START;
	Uint8 P1C_SELECT;
	//Player Two Keyboard
	Sint32 P2K_UP;
	Sint32 P2K_DOWN;
	Sint32 P2K_LEFT;
	Sint32 P2K_RIGHT;
	Sint32 P2K_LIGHTPUNCH;
	Sint32 P2K_MEDIUMPUNCH;
	Sint32 P2K_HARDPUNCH;
	Sint32 P2K_LIGHTKICK;
	Sint32 P2K_MEDIUMKICK;
	Sint32 P2K_HARDKICK;
	//Player Two Controller
	SDL_JoystickID P2_Controller;
	Uint8 P2C_LIGHTPUNCH;
	Uint8 P2C_MEDIUMPUNCH;
	Uint8 P2C_HARDPUNCH;
	Uint8 P2C_LIGHTKICK;
	Uint8 P2C_MEDIUMKICK;
	Uint8 P2C_HARDKICK;
	Uint8 P2C_START;
	Uint8 P2C_SELECT;
} playerInput;

void FUR_initPlayerInput();

int deadZone;
bool bJoysticksInitialized;
SDL_Joystick* a_joysticks[8];


void FUR_initialiseJoysticks();
bool FUR_joysticksInitialised();
void FUR_handleEvents();
void FUR_cleanEvents();

#endif //  __handleEvents__
