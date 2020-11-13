/*
    Furnace
    Copyright (C) 2015-2016 Demonic Benefactor <demonic@tutanota.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "player.h"
#include "characters.h"
#include "game.h"

int FUR_initPlayers( SDL_Renderer* pRenderer, character P1, character P2 )
{	
	int i;
	
	for (i = 0; i < 2; i++)
	{
		player* p;
		p = (player*)malloc(sizeof(player));
		if ( i == 0 )
		{
			p->who = P1;
			p->position.x = 100;
			p->flip = SDL_FLIP_NONE;
			FUR_initCharacter( p );
		}
		else {
			p->who = P2;
			p->position.x = 604;
			p->flip = SDL_FLIP_HORIZONTAL;
			FUR_initCharacter( p );
		}		
		p->jumping = false;
		p->jumpTimer = 0;
		p->armor = 0;
		
		a_players[i] = p;
	}
	return 1;
}

void FUR_renderPlayers( SDL_Renderer *pRenderer, player *pP1, player *pP2)
{
    FUR_textureDrawFrame( 0, pP1->textures.idle, pP1->position, 250, 250,
		    	0, 0, 0.0, 255, pRenderer, pP1->flip);
    FUR_textureDrawFrame( 0, pP2->textures.idle, pP2->position, 250, 250,
		    	0, 0, 0.0, 255, pRenderer, pP2->flip);
}

void FUR_updatePlayers()
{
	int i;	
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
			if (a_players[i]->position.x < 804)
			{
				a_players[i]->position.x += 3;
			}
		}
		else if (a_players[i]->axis == left)
		{
			if (a_players[i]->position.x > -100)
			{
				a_players[i]->position.x -= 3;
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
	
	if (a_players[0]->position.x > a_players[1]->position.x)
	{
		a_players[0]->flip = SDL_FLIP_HORIZONTAL;
		a_players[1]->flip = SDL_FLIP_NONE;
	}
	else
	{
		a_players[0]->flip = SDL_FLIP_NONE;
		a_players[1]->flip = SDL_FLIP_HORIZONTAL;
	}
	
	
}

void FUR_cleanPlayer()
{

}

void FUR_playerJump( player* pPlayer )
{	
	static float startPos, endPos;
	static int duration;

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
		pPlayer->position.y = (int)(-endPos * pPlayer->currentTime * 
				(pPlayer->currentTime - 2) + startPos);
	}
	else
	{
		pPlayer->currentTime = pPlayer->jumpTimer - 39;
		pPlayer->currentTime /= duration;
		pPlayer->position.y = (int)(-endPos * pPlayer->currentTime * 
				pPlayer->currentTime + 30);
	}
	
	pPlayer->jumpTimer += 1;
	if ( pPlayer->jumpTimer >= normal )
	{
		pPlayer->jumping = false;
		pPlayer->jumpTimer = 0;
	}
}
