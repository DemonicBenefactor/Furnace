#ifndef __gameObject__
#define __gameObject__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "textureManager.h"

typedef struct {
	int textureID;	
	int x;
	int y;
	int width;
	int height;
	int currentRow;
	int currentFrame;
	double angle;
	int alpha;
	SDL_RendererFlip flip;
} gameObject;

int FUR_createObject( const char* fileName, int id, int x, int y, int width,
		int height, int currentRow, int currentFrame, double angle,
		int alpha, SDL_Renderer* pRenderer, SDL_RendererFlip flip, gameObject* object);

void FUR_drawObject( SDL_Renderer *pRenderer, gameObject *pGameObject );
void FUR_updateObject( gameObject *pGameObject );
void FUR_cleanObject();

gameObject* pGameObject;
gameObject* a_gameObjects[64];

#endif //  __gameObject__
