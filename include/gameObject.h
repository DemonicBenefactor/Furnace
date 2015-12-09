#ifndef __gameObject__
#define __gameObject__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "textureManager.h"

void FUR_drawObject(SDL_Renderer *pRenderer, gameObject *pGameObject);
void FUR_updateObject(gameObject *pGameObject);
void FUR_cleanObject();

typedef struct {
	int textureID;	
	int currentRow;
	int currentFrame;
	int width;
	int height;
	int x;
	int y;
} gameObject;

#endif //  __gameObject__