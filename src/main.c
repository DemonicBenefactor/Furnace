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

#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"
#include "handleEvents.h"

#define FPS 60
#define DELAY_TIME 1000/FPS


int main( int argc, char* argv[])
{
    Uint32 frameStart, frameTime;
	
	FUR_init("Furnace", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			512, 300, SDL_WINDOW_OPENGL /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/);
	
    while( gameRunning )
    {
	frameStart = SDL_GetTicks();

	FUR_handleEvents();
	FUR_update();
	FUR_render();

	frameTime = SDL_GetTicks() - frameStart;
	if ( frameTime < DELAY_TIME )
	{
		SDL_Delay( (int)( DELAY_TIME - frameTime ));
	}

    }

    FUR_clean();
    return 0;
}



