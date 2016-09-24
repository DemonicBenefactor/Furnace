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

#include <stdio.h>
#include <SDL2/SDL.h>

#include "stdbool.h"
#include "textureManager.h"
#include "SDL_image.h"


int FUR_textureLoad( const char* fileName, int id, 
		SDL_Texture* textureSet[], SDL_Renderer* pRenderer )
{
	SDL_Surface* pTempSurface = IMG_Load(fileName);
	
	if ( pTempSurface == 0 )
	{
		printf( IMG_GetError() );
		return false;
	}
	
	pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		textureSet[id] = pTexture;
		return true;
	}

	return false;
}

void FUR_textureDrawFrame(int id, SDL_Texture* textureSet[], vector2D position, 
			int width, int height, int currentRow, int currentFrame,
			double angle, int alpha, 
			SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = position.x;
	destRect.y = position.y;

	SDL_SetTextureAlphaMod(textureSet[id], alpha);
	SDL_RenderCopyEx(pRenderer, textureSet[id], 
			&srcRect, &destRect, angle, 0, flip);
}
// This needs to be translated to no SDL library
