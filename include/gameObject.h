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

int FUR_createObject( const char* fileName, int id, int x, int y, int width,
		int height, int currentRow, int currentFrame, double angle,
		int alpha, SDL_Renderer* pRenderer, SDL_RendererFlip flip );

void FUR_drawObject( SDL_Renderer *pRenderer, gameObject *pGameObject );
void FUR_updateObject( gameObject *pGameObject );
void FUR_cleanObject();

gameObject* a_gameObjects[64];

#endif //  __gameObject__
