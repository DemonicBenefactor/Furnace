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

#include "input.h"


void FUR_initPlayerInput()
{
	playerInput.P1_UPDOWN = 0;
	playerInput.P1_LEFTRIGHT = 0;
	playerInput.P2_UPDOWN = 0;
	playerInput.P2_LEFTRIGHT = 0;

	playerInput.P1_Controller = 1;
	playerInput.P1K_UP = SDLK_UP;
	playerInput.P1K_DOWN = SDLK_DOWN;
	playerInput.P1K_LEFT = SDLK_LEFT;
	playerInput.P1K_RIGHT = SDLK_RIGHT;
	playerInput.P1K_LIGHTPUNCH = SDLK_u;
	playerInput.P1K_MEDIUMPUNCH = SDLK_i;
	playerInput.P1K_HARDPUNCH = SDLK_o;
	playerInput.P1K_LIGHTKICK = SDLK_j;
	playerInput.P1K_MEDIUMKICK = SDLK_k;
	playerInput.P1K_HARDKICK = SDLK_l;

	playerInput.P2_Controller = 2;
	playerInput.P2K_UP = SDLK_w;
	playerInput.P2K_DOWN = SDLK_s;
	playerInput.P2K_LEFT = SDLK_a;
	playerInput.P2K_RIGHT = SDLK_d;
	playerInput.P2K_LIGHTPUNCH = SDLK_r;
	playerInput.P2K_MEDIUMPUNCH = SDLK_t;
	playerInput.P2K_HARDPUNCH = SDLK_y;
	playerInput.P2K_LIGHTKICK = SDLK_f;
	playerInput.P2K_MEDIUMKICK = SDLK_g;
	playerInput.P2K_HARDKICK = SDLK_h;
}

/*****************************************************
 * GAMEPAD SETUP
 * **************************************************/

void FUR_initialiseJoysticks()
{
    int i;

    if ( SDL_WasInit( SDL_INIT_JOYSTICK ) == 0 )
    {
		SDL_InitSubSystem( SDL_INIT_JOYSTICK );
    }

    if ( SDL_NumJoysticks() > 0 )
    {
	for ( i = 0; i < SDL_NumJoysticks(); i++ )
	{
	    if ( i < 4 )
	    {		
			SDL_Joystick* joy;
	    	joy = SDL_JoystickOpen(i);
			a_joysticks[i] = joy;
	    }	
	}
	
	SDL_JoystickEventState( SDL_ENABLE );
	bJoysticksInitialized = true;
	printf( "initialized %d joysitck(s)\n", (int)(SDL_NumJoysticks() ) );

    }
    else
    {
	bJoysticksInitialized = false;
    }
}

bool FUR_joysticksInitialized()
{
	return bJoysticksInitialized = true;
}



/******************************************************
 * THE MAIN EVENT HANDLER
 * ****************************************************/


void FUR_handleEvents()
{
    SDL_Event event;
    deadZone = 10000;

    if ( SDL_PollEvent( &event ) )
    {
	switch ( event.type )
	{
	    case SDL_QUIT:
		gameRunning = false;
		break;
		////////////////////////////////////////////////////////////
		//HANDLE THE KEYBOARD INPUTS
		////////////////////////////////////////////////////////////
		case SDL_KEYDOWN:
		//printf( " %s\n", SDL_GetKeyName( event.key.keysym.sym ) );
		    if ( event.key.keysym.sym == SDLK_ESCAPE )
		    {
			gameRunning = false;
		    }
		    //PLAYER ONE BUFFER
		    else if ( event.key.keysym.sym == playerInput.P1K_UP )
		    {
			playerInput.P1_UPDOWN = 1;
		    }
				
		    else if ( event.key.keysym.sym == playerInput.P1K_DOWN )
		    {
			playerInput.P1_UPDOWN = -1;
		    }
		    else if (event.key.keysym.sym == playerInput.P1K_LEFT)
		    {
			playerInput.P1_LEFTRIGHT = 1;
		    }
		    else if (event.key.keysym.sym == playerInput.P1K_RIGHT)
		    {
			playerInput.P1_LEFTRIGHT = -1;
		    }
		    //PLAYER TWO BUFFER
		    else if ( event.key.keysym.sym == playerInput.P2K_UP )
		    {
			playerInput.P2_UPDOWN = 1;
		    }
		    else if ( event.key.keysym.sym == playerInput.P2K_DOWN )
		    {
			playerInput.P2_UPDOWN = -1;
		    }
		    else if (event.key.keysym.sym == playerInput.P2K_LEFT)
		    {
			playerInput.P2_LEFTRIGHT = 1;
		    }
		    else if (event.key.keysym.sym == playerInput.P2K_RIGHT)
		    {
		    playerInput.P2_LEFTRIGHT = -1;
		    }
		    break;
		
		case SDL_KEYUP:
		    //PLAYER ONE BUFFER
		    if (event.key.keysym.sym == playerInput.P1K_UP)
		    {
			playerInput.P1_UPDOWN = 0;
		    }
		    else if (event.key.keysym.sym == playerInput.P1K_DOWN)
		    {
			playerInput.P1_UPDOWN = 0;
		    }
		    else if (event.key.keysym.sym == playerInput.P1K_LEFT)
		    {
			playerInput.P1_LEFTRIGHT = 0;
		    }
		    else if (event.key.keysym.sym == playerInput.P1K_RIGHT)
		    {
			playerInput.P1_LEFTRIGHT = 0;
		    }
		    //PLAYER TWO BUFFER
		    if (event.key.keysym.sym == playerInput.P2K_UP)
		    {
			playerInput.P2_UPDOWN = 0;
		    }
		    else if (event.key.keysym.sym == playerInput.P2K_DOWN)
		    {
			playerInput.P2_UPDOWN = 0;
		    }
		    else if (event.key.keysym.sym == playerInput.P2K_LEFT)
		    {
			playerInput.P2_LEFTRIGHT = 0;
		    }
		    else if (event.key.keysym.sym == playerInput.P2K_RIGHT)
		    {
			playerInput.P2_LEFTRIGHT = 0;
		    }
		    
		    break;
		//////////////////////////////////////////////////////////////
		//HANDLE FIGHT STICKS
		//////////////////////////////////////////////////////////////
		case SDL_JOYAXISMOTION:
		    if (event.jaxis.which == playerInput.P1_Controller)
		    {
			if (event.jaxis.axis == 0)
			{
			    if (event.jaxis.value > deadZone)
			    {
				playerInput.P1_LEFTRIGHT = -1; //right
			    }
			    else if (event.jaxis.value < -deadZone)
			    {
				playerInput.P1_LEFTRIGHT = 1; //left
			    }
			    else { playerInput.P1_LEFTRIGHT = 0; }
			}
			else if (event.jaxis.axis == 1)
			{
			    if (event.jaxis.value > deadZone)
			    {
				playerInput.P1_UPDOWN = -1; //down
			    }
			    else if (event.jaxis.value < -deadZone)
			    {
				playerInput.P1_UPDOWN = 1;//up
			    }
			    else { playerInput.P1_UPDOWN = 0; }
			}
		    }
		    else if (event.jaxis.which == playerInput.P2_Controller)
		    {
			if (event.jaxis.axis == 0)
			{
			    if (event.jaxis.value > deadZone)
			    {
				playerInput.P2_LEFTRIGHT = -1; //right
			    }
			    else if (event.jaxis.value < -deadZone)
			    {
				playerInput.P2_LEFTRIGHT = 1; //left
			    }
			    else { playerInput.P2_LEFTRIGHT = 0; }
			    }
			else if (event.jaxis.axis == 1)
			{
			    if (event.jaxis.value > deadZone)
			    {
			    	playerInput.P2_UPDOWN = -1; //down
			    }
			    else if (event.jaxis.value < -deadZone)
			    {
				playerInput.P2_UPDOWN = 1;//up
			    }
			    else { playerInput.P2_UPDOWN = 0; }
			}
		    }				
		    break;
			
		    ///////////////////////////////////////////
		    //  D PAD
		    //////////////////////////////////////////
		case SDL_JOYHATMOTION:
		    switch (event.jhat.value)
		    {
			case SDL_HAT_UP:
			    playerInput.P1_UPDOWN = 1;
			    playerInput.P1_LEFTRIGHT = 0;
			    break;
			case SDL_HAT_RIGHTUP:
			    playerInput.P1_UPDOWN = 1;
			    playerInput.P1_LEFTRIGHT = -1;
			    break;
			case SDL_HAT_RIGHT:
			    playerInput.P1_LEFTRIGHT = -1;
			    playerInput.P1_UPDOWN = 0;
			    break;
			case SDL_HAT_RIGHTDOWN:
			    playerInput.P1_LEFTRIGHT = -1;
			    playerInput.P1_UPDOWN = -1;
			    break;
			case SDL_HAT_DOWN:
			    playerInput.P1_UPDOWN = -1;
			    playerInput.P1_LEFTRIGHT = 0;
			    break;
			case SDL_HAT_LEFTDOWN:
			    playerInput.P1_LEFTRIGHT = 1;
			    playerInput.P1_UPDOWN = -1;
			    break;
			case SDL_HAT_LEFT:
			    playerInput.P1_LEFTRIGHT = 1;
			    playerInput.P1_UPDOWN = 0;
			    break;
			case SDL_HAT_LEFTUP:
			    playerInput.P1_LEFTRIGHT = 1;
			    playerInput.P1_UPDOWN = 1;
			    break;
			case 0:
			    playerInput.P1_UPDOWN = 0;
			    playerInput.P1_LEFTRIGHT = 0;
			default:
			    break;
		    }

		case SDL_JOYBUTTONDOWN:
		    break;
		case SDL_JOYBUTTONUP:
		    break;

		case SDL_MOUSEBUTTONDOWN:
		    //gameRunning = false;
		    	break;
		    default:
		    	break;
	}
    }
}

/******************************************************
 * CLEAN UP TIME
 * ***************************************************/

void FUR_cleanEvents()
{
    unsigned int i;
    if ( bJoysticksInitialized == true )
    {
	for ( i = 0; i < (unsigned int)SDL_NumJoysticks(); i++ )
	{
	    SDL_JoystickClose( a_joysticks[i] );
	}

    }

}
