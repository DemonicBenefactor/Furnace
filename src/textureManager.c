#include <stdio.h>
#include <SDL2/SDL.h>

#include "stdbool.h"
#include "textureManager.h"
#include "SDL_image.h"


int FUR_textureLoad( const char* fileName, int id, SDL_Renderer* pRenderer )
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
		a_TextureList[id] = pTexture;
		return true;
	}

	return false;
}

void FUR_textureDrawFrame(int id, vector2D position, int width, int height,
			int currentRow, int currentFrame, double angle, int alpha, 
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

	SDL_SetTextureAlphaMod(a_TextureList[id], alpha);
	SDL_RenderCopyEx(pRenderer, a_TextureList[id], &srcRect, &destRect, angle, 0, flip);
}
