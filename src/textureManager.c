#include <stdio.h>
#include <SDL2/SDL.h>

#include "stdbool.h"
#include "TextureManager.h"
#include "SDL_image.h"


int FUR_textureLoad( const char* fileName, int id, SDL_Renderer* pRenderer )
{
	SDL_Surface* pTempSurface = IMG_Load(fileName);
	
	if ( pTempSurface == 0 )
	{
		printf( IMG_GetError() );
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		a_TextureList[id] = pTexture;
		return true;
	}

	return false;
}