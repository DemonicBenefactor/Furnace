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

#ifndef __game__
#define __game__

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "textureManager.h"
#include "gameObject.h"
#include "player.h"
#include "input.h"

int currentFrame;
bool gameRunning;

bool FUR_init(const char* title, int xpos, int ypos, 
		int width, int height, bool fullscreen);

void FUR_render();
void FUR_update();
void FUR_clean();
void FUR_testMessage(const char* text);

SDL_Window* pWindow;
SDL_Renderer* pRenderer;
SDL_GLContext MainContext;

#endif
