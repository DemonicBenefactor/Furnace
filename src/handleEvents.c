#include "handleEvents.h"
#include "configuration.h"
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
				break;
			case SDL_KEYUP:
				//printf( " %s\n", SDL_GetKeyName( event.key.keysym.sym ) );
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					gameRunning = false;
				}
				else if (event.key.keysym.sym == playerInput.P1K_UP)
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
				break;
			/////////////////////////////////////////////////////////////////
			//HANDLE FIGHT STICKS
			/////////////////////////////////////////////////////////////////
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
				break;

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
