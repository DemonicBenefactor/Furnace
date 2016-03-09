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

#ifndef __gameObject__
#define __gameObject__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "textureManager.h"
#include "vectors.h"

typedef struct {
	int textureID;
	int width;
	int height;
	int currentRow;
	int currentFrame;
	double angle;
	int alpha;
	vector2D position;
	SDL_RendererFlip flip;
} gameObject;

int FUR_createObject( const char* fileName, int id, SDL_Texture* textureList[], 
		int x, int y, int width,
		int height, int currentRow, int currentFrame, double angle,
		int alpha, SDL_Renderer* pRenderer, SDL_RendererFlip flip );

void FUR_drawObject( SDL_Renderer *pRenderer, gameObject *pGameObject );
void FUR_updateObject( gameObject *pGameObject );
void FUR_cleanObject();

gameObject* a_gameObjects[64];

#endif //  __gameObject__
