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
	
	pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		a_TextureList[id] = pTexture;
		return true;
	}

	return false;
}

void FUR_textureDraw( int id, int x, int y, int width, int height,
			SDL_Renderer* pRenderer, SDL_RendererFlip flip )
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, a_TextureList[id], &srcRect, &destRect, 0, 0, flip);
}

void FUR_textureDrawFrame(int id, int x, int y, int width, int height,
			int currentRow, int currentFrame, SDL_Renderer* pRenderer,
			double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(a_TextureList[id], alpha);
	SDL_RenderCopyEx(pRenderer, a_TextureList[id], &srcRect, &destRect, angle, 0, flip);
}