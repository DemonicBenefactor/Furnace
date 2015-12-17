
#include "gameObject.h"

int FUR_createObject( const char* fileName, int id, float x, float y, int width,
		int height, int currentRow, int currentFrame, double angle,
		int alpha, SDL_Renderer* pRenderer, SDL_RendererFlip flip )
{
	gameObject* object;
	int success;
	success = FUR_textureLoad( fileName, id, pRenderer );
	if ( success == 0 )
	{
		printf ("texture load failed");
		return 0;
	}
	object = malloc(sizeof(gameObject));
	object->textureID = id;
	object->position.x = x;
	object->position.y = y;
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
   FUR_textureDrawFrame( pGameObject->textureID, pGameObject->position,
		 pGameObject->width, pGameObject->height, pGameObject->currentRow,
		 pGameObject->currentFrame, pGameObject->angle, pGameObject->alpha,
		 pRenderer, pGameObject->flip);
}


int goingRight = 1;
void FUR_updateObject( gameObject *pGameObject )
{
	if (goingRight == 1)
	{
		pGameObject->position.x += 1;
		if (pGameObject->position.x > 320)
		{
			goingRight = 0;
		}
	}
	else if (goingRight == 0)
	{
		pGameObject->position.x -= 1;
		if (pGameObject->position.x < -45)
		{
			goingRight = 1;
		}
	}
}

void FUR_cleanObject()
{

}

