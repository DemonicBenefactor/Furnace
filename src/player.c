
#include "player.h"
#include "game.h"

int FUR_initPlayers( SDL_Renderer* pRenderer, character P1, character P2 )
{	
	for (i = 0; i < 2; i++)
	{
		character tmpCharacter;
		player* p;
		p = malloc(sizeof(player));
		if ( i == 0 )
		{
			tmpCharacter = P1;
			p->position.x = -50;
		}
		else {
			tmpCharacter = P2;
			p->position.x = 420;
		}		
		p->jumping = false;
		p->jumpTimer = 0;
		p->guardBreak = 100;
		p->position.y = 230;
		p->armor = 0;
		 switch (tmpCharacter)
		 {
			case Demonic:
				strcpy( p->name,"Demonic");
				p->who = Demonic;
				p->health = 100;
				p->jumpSpeed = normal;
				p->walkSpeed = normal;
				p->jumpDistance = mid;
				p->meter = 4;
				break;
			case Zoe:
				strcpy( p->name, "Zoe" );
				p->who = Zoe;
				p->health = 80;
				p->jumpSpeed = fast;
				p->walkSpeed = fast;
				p->jumpDistance = mid;
				p->meter = 2;
				break;
		 }
		
		
		a_players[i] = p;
	}
	return 1;
}

void FUR_updatePlayers()
{
	
	//////////////////////////////////////////////////////////////
	//PLAYER 1 TRANSFER OF INPUTS
	//////////////////////////////////////////////////////////////	
	if (playerInput.P1_UPDOWN > 0 && playerInput.P1_LEFTRIGHT > 0)	
	{ 
		a_players[0]->axis = upLeft;
	} //upLeft
	else if (playerInput.P1_UPDOWN > 0 && playerInput.P1_LEFTRIGHT < 0) 
	{
		a_players[0]->axis = upRight;
	} //upRight
	else if (playerInput.P1_UPDOWN < 0 && playerInput.P1_LEFTRIGHT > 0) 
	{ 
		a_players[0]->axis = downLeft; 
	} //downLeft
	else if (playerInput.P1_UPDOWN < 0 && playerInput.P1_LEFTRIGHT < 0) 
	{ 
		a_players[0]->axis = downRight; 
	} //downRight
	else if (playerInput.P1_UPDOWN > 0) 
	{ 
		a_players[0]->axis = up; 
	} //up
	else if (playerInput.P1_UPDOWN < 0) 
	{
		a_players[0]->axis = down; 
	} //down
	else if (playerInput.P1_LEFTRIGHT > 0) 
	{ 
		a_players[0]->axis = left; 
	} //left
	else if (playerInput.P1_LEFTRIGHT < 0) 
	{ 
		a_players[0]->axis = right; 
	} //right
	else { 
		a_players[0]->axis = center;
	} //center
	//////////////////////////////////////////////////////////////
	//PLAYER 2 TRANSFER OF INPUTS
	//////////////////////////////////////////////////////////////
	if (playerInput.P2_UPDOWN > 0 && playerInput.P1_LEFTRIGHT > 0)	
	{ 
		a_players[1]->axis = upLeft;
	} //upLeft
	else if (playerInput.P2_UPDOWN > 0 && playerInput.P2_LEFTRIGHT < 0) 
	{
		a_players[1]->axis = upRight;
	} //upRight
	else if (playerInput.P2_UPDOWN < 0 && playerInput.P2_LEFTRIGHT > 0) 
	{ 
		a_players[1]->axis = downLeft; 
	} //downLeft
	else if (playerInput.P2_UPDOWN < 0 && playerInput.P2_LEFTRIGHT < 0) 
	{ 
		a_players[1]->axis = downRight;
	} //downRight
	else if (playerInput.P2_UPDOWN > 0) 
	{ 
		a_players[1]->axis = up; 
	} //up
	else if (playerInput.P2_UPDOWN < 0) 
	{
		a_players[1]->axis = down; 
	} //down
	else if (playerInput.P2_LEFTRIGHT > 0) 
	{ 
		a_players[1]->axis = left; 
	} //left
	else if (playerInput.P2_LEFTRIGHT < 0) 
	{ 
		a_players[1]->axis = right; 
	} //right
	else { 
		a_players[1]->axis = center; 
	} //center
	
	//FINISHED INPUT TRANSFER

	for ( i = 0; i < 2; i++ )
	{
		if (a_players[i]->axis == right)
		{
			if (a_gameObjects[i]->position.x < 650)
			{
				a_gameObjects[i]->position.x += 3;
			}
		}
		else if (a_players[i]->axis == left)
		{
			if (a_gameObjects[i]->position.x > -100)
			{
				a_gameObjects[i]->position.x -= 3;
			}
		}
		else if ( a_players[i]->axis == up )
		{
			a_players[i]->jumping = true;
		}
		else if ( a_players[i]->axis == center )
		{

		}
				
		//JUMP
		if (a_players[i]->jumping == true)
		{
			FUR_playerJump( a_players[i] );
		}
	}
	

	// FIX PLAYER DIRECTION
	if (a_gameObjects[0]->position.x > a_gameObjects[1]->position.x)
	{
		a_gameObjects[0]->flip = SDL_FLIP_HORIZONTAL;
		a_gameObjects[1]->flip = SDL_FLIP_NONE;
	}
	else
	{
		a_gameObjects[0]->flip = SDL_FLIP_NONE;
		a_gameObjects[1]->flip = SDL_FLIP_HORIZONTAL;
	}
	
}

void FUR_cleanPlayer()
{

}

void FUR_playerJump( player* pPlayer )
{	
	if ( pPlayer->jumpTimer == 0 )
	{			
		startPos = 230;
		endPos = -200;
	}
	duration = normal / 2;
	if ( pPlayer->jumpTimer <= duration )
	{
		pPlayer->currentTime = pPlayer->jumpTimer;
		pPlayer->currentTime /= duration;
		a_gameObjects[0]->position.y = (int)(-endPos * pPlayer->currentTime * (pPlayer->currentTime - 2) + startPos);
	}
	else
	{
		pPlayer->currentTime = pPlayer->jumpTimer - 39;
		pPlayer->currentTime /= duration;
		a_gameObjects[0]->position.y = (int)(-endPos * pPlayer->currentTime * pPlayer->currentTime + 30);
	}
	/*
	if (pPlayer->jumpTimer < (normal / 2))
	{
	a_gameObjects[0]->position.y -= 5;
	}
	else {a_gameObjects[0]->position.y += 5;}
	*/
	
	pPlayer->jumpTimer += 1;
	if ( pPlayer->jumpTimer >= normal )
	{
		pPlayer->jumping = false;
		pPlayer->jumpTimer = 0;
	}
}