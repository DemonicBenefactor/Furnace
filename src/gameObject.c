
#include "gameObject.h"

int FUR_createObject( const char* fileName, int id, int x, int y, int width,
		int height, int currentRow, int currentFrame, double angle,
		int alpha, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	int success;
	success = FUR_textureLoad( fileName, id, pRenderer );
	if ( success == 0 )
	{
		printf ("texture load failed");
		return 0;
	}
	pGameObject->textureID = id;
	pGameObject->x = x;
	pGameObject->y = y;
	pGameObject->width = width;
	pGameObject->height = height;
	pGameObject->currentRow = currentRow;
	pGameObject->currentFrame = currentFrame;
	pGameObject->angle = angle;
	pGameObject->alpha = alpha;
	pGameObject->flip = flip;
	
	a_gameObjects[id] = pGameObject;

	return 1;
}

void FUR_drawObject( SDL_Renderer *pRenderer, gameObject *pGameObject )
{
   FUR_textureDrawFrame( pGameObject->textureID, pGameObject->x, pGameObject->y,
		 pGameObject->width, pGameObject->height, pGameObject->currentRow,
		 pGameObject->currentFrame, pGameObject->angle, pGameObject->alpha,
		 pRenderer, SDL_FLIP_NONE);
}

void FUR_updateObject( gameObject *pGameObject )
{
	pGameObject->x += 1;
}

void FUR_cleanObject()
{

}

