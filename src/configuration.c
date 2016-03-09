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

#include "configuration.h"

void FUR_initPlayerInput()
{
	playerInput.P1_UPDOWN = 0;
	playerInput.P1_LEFTRIGHT = 0;
	playerInput.P2_UPDOWN = 0;
	playerInput.P2_LEFTRIGHT = 0;
	
	playerInput.P1_Controller = 1;
	playerInput.P1K_UP = SDLK_UP;
	playerInput.P1K_DOWN = SDLK_DOWN;
	playerInput.P1K_LEFT = SDLK_LEFT;
	playerInput.P1K_RIGHT = SDLK_RIGHT;
	playerInput.P1K_LIGHTPUNCH = SDLK_u;
	playerInput.P1K_MEDIUMPUNCH = SDLK_i;
	playerInput.P1K_HARDPUNCH = SDLK_o;
	playerInput.P1K_LIGHTKICK = SDLK_j;
	playerInput.P1K_MEDIUMKICK = SDLK_k;
	playerInput.P1K_HARDKICK = SDLK_l;

	playerInput.P2_Controller = 2;
	playerInput.P2K_UP = SDLK_w;
	playerInput.P2K_DOWN = SDLK_s;
	playerInput.P2K_LEFT = SDLK_a;
	playerInput.P2K_RIGHT = SDLK_d;
	playerInput.P2K_LIGHTPUNCH = SDLK_r;
	playerInput.P2K_MEDIUMPUNCH = SDLK_t;
	playerInput.P2K_HARDPUNCH = SDLK_y;
	playerInput.P2K_LIGHTKICK = SDLK_f;
	playerInput.P2K_MEDIUMKICK = SDLK_g;
	playerInput.P2K_HARDKICK = SDLK_h;
}
