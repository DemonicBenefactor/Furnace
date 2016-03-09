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

#ifndef __textureManager__
#define __textureManager__

#include <SDL2/SDL.h>
#include <stdio.h>

#include "vectors.h"

int FUR_textureLoad( const char* fileName, int id, 
			SDL_Texture* textureSet[], SDL_Renderer* pRenderer );

void FUR_textureDrawFrame( int id, SDL_Texture* textureSet[],
			vector2D position, int width, int height,
			int currentRow, int currentFrame, 
			double angle, int alpha, 
			SDL_Renderer* pRenderer, SDL_RendererFlip flip );

SDL_Texture* pTexture;
SDL_Texture* a_TextureList[64];

#endif //__textureManager__
