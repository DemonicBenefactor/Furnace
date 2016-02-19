
#include "player.h"
#include "game.h"

int FUR_initPlayers()
{	
	int i;
	for (i = 0; i < 2; i++)
	{
		player* p;
		p = malloc(sizeof(player));
		a_players[i] = p;
	}
	return 1;
}


void FUR_updatePlayers()
{
	if (playerInput.P1_UPDOWN > 0 && playerInput.P1_LEFTRIGHT > 0)	
	{ 
		a_players[0]->axis = upLeft; 
		//SDL_SetRenderDrawColor(pRenderer, 0, 50, 0, 255);
	} //upLeft
	else if (playerInput.P1_UPDOWN > 0 && playerInput.P1_LEFTRIGHT < 0) 
	{
		a_players[0]->axis = upRight;
		//SDL_SetRenderDrawColor(pRenderer, 50, 0, 0, 255);
	} //upRight
	else if (playerInput.P1_UPDOWN < 0 && playerInput.P1_LEFTRIGHT > 0) 
	{ 
		a_players[0]->axis = downLeft;
		//SDL_SetRenderDrawColor(pRenderer, 0, 50, 50, 255); 
	} //downLeft
	else if (playerInput.P1_UPDOWN < 0 && playerInput.P1_LEFTRIGHT < 0) 
	{ 
		a_players[0]->axis = downRight;
		//SDL_SetRenderDrawColor(pRenderer, 50, 0, 50, 255); 
	} //downRight
	else if (playerInput.P1_UPDOWN > 0) 
	{ 
		a_players[0]->axis = up;
		//SDL_SetRenderDrawColor(pRenderer, 50, 50, 0, 255); 
	} //up
	else if (playerInput.P1_UPDOWN < 0) 
	{
		a_players[0]->axis = down;
		//SDL_SetRenderDrawColor(pRenderer, 0, 0, 100, 255); 
	} //down
	else if (playerInput.P1_LEFTRIGHT > 0) 
	{ 
		a_players[0]->axis = left;
		//SDL_SetRenderDrawColor(pRenderer, 0, 100, 0, 255); 
	} //left
	else if (playerInput.P1_LEFTRIGHT < 0) 
	{ 
		a_players[0]->axis = right;
		//SDL_SetRenderDrawColor(pRenderer, 100, 0, 0, 255); 
	} //right
	else { 
		a_players[0]->axis = center;
		//SDL_SetRenderDrawColor(pRenderer, 200, 200, 200, 255); 
	} //center



	if (a_players[0]->axis == right)
	{
		if (a_gameObjects[0]->position.x < 650)
		{
			a_gameObjects[0]->position.x += 3;
		}
	}
	else if (a_players[0]->axis == left)
	{
		if (a_gameObjects[0]->position.x > -100)
		{
			a_gameObjects[0]->position.x -= 3;
		}
	}

	if (a_gameObjects[0]->position.x > a_gameObjects[1]->position.x)
	{
		a_gameObjects[0]->flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		a_gameObjects[0]->flip = SDL_FLIP_NONE;
	}
}

void FUR_cleanPlayer()
{

}

