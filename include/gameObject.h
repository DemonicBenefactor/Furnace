#ifndef __gameObject__
#define __gameObject__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "textureManager.h"

void FUR_drawObject();
void FUR_updateObject();
void FUR_cleanObject();

typedef struct {
	int x;
	int y;
} gameObject;

#endif //  __gameObject__