#ifndef __textureManager__
#define __textureManager__

#include <SDL2/SDL.h>
#include <stdio.h>

int FUR_textureLoad( const char* fileName, int id, SDL_Renderer* pRenderer );

void FUR_textureDraw( int id, int x, int y, int width, int height,
	       		SDL_Renderer* pRenderer, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/ );

void FUR_textureDrawFrame( int id, int x, int y, int width, int height, 
			int currentRow,	int currentFrame, SDL_Renderer* pRenderer,  
			SDL_RendererFlip flip /*= SDL_FLIP_NONE*/ );

SDL_Texture* a_TextureList[64];

#endif //__textureManager__
