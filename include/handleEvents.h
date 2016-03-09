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

#include "configuration.h"
#include "game.h"
#include "vectors.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

int deadZone;
bool bJoysticksInitialized;
SDL_Joystick* a_joysticks[8];


void FUR_initialiseJoysticks();
bool FUR_joysticksInitialised();
void FUR_handleEvents();
void FUR_cleanEvents();

#endif //  __handleEvents__
