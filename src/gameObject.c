
#include "gameObject.h"

int FUR_createObject( const char* fileName, int id, int x, int y, int width,
		int height, int currentRow, int currentFrame, double angle,
		int alpha, SDL_Renderer* pRenderer, SDL_RendererFlip flip, gameObject* object)
{
	int success;
	success = FUR_textureLoad( fileName, id, pRenderer );
	if ( success == 0 )
	{
		printf ("texture load failed");
		return 0;
	}
	object = malloc(sizeof(gameObject));
	object->textureID = id;
	object->x = x;
	object->y = y;
	object->width = width;
	object->height = height;
	object->currentRow = currentRow;
	object->currentFrame = currentFrame;
	object->angle = angle;
	object->alpha = alpha;
	object->flip = flip;
	
	a_gameObjects[id] = object;

	return 1;
}

void FUR_drawObject( SDL_Renderer *pRenderer, gameObject *pGameObject )
{
   FUR_textureDrawFrame( pGameObject->textureID, pGameObject->x, pGameObject->y,
		 pGameObject->width, pGameObject->height, pGameObject->currentRow,
		 pGameObject->currentFrame, pGameObject->angle, pGameObject->alpha,
		 pRenderer, pGameObject->flip);
}

void FUR_updateObject( gameObject *pGameObject )
{
	pGameObject->x += 1;
}

void FUR_cleanObject()
{

}

