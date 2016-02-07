#include "handleEvents.h"
#include "configuration.h"
/*****************************************************
 * GAMEPAD SETUP
 * **************************************************/

void FUR_initialiseJoysticks()
{
    int i;
	//The keyboard is treated as a joystick in this game,
	//so we need to init it as such
	vector4D* keyboard_1;
	vector4D* keyboard_2;
	keyboard_1 = malloc(sizeof(vector4D));
	keyboard_2 = malloc(sizeof(vector4D));
	a_joystickStates[10] = keyboard_1;
	a_joystickStates[11] = keyboard_2;
	//Finished initializing the keyboard;

    if ( SDL_WasInit( SDL_INIT_JOYSTICK ) == 0 )
    {
	SDL_InitSubSystem( SDL_INIT_JOYSTICK );
    }

    if ( SDL_NumJoysticks() > 0 )
    {
	for ( i = 0; i < SDL_NumJoysticks(); i++ )
	{
	    if ( i < 9 )
	    {		
			SDL_Joystick* joy;
	    	joy = SDL_JoystickOpen(i);
			a_joysticks[i] = joy;
			vector4D* joyDirection;
			joyDirection = malloc(sizeof(vector4D));
			a_joystickStates[i] = joyDirection;
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
					a_joystickStates[10]->x = 1;
				}
				else if ( event.key.keysym.sym == playerInput.P1K_DOWN )
				{
					a_joystickStates[10]->y = 1;
				}
				else if (event.key.keysym.sym == playerInput.P1K_LEFT)
				{
					a_joystickStates[10]->z = 1;
				}
				else if (event.key.keysym.sym == playerInput.P1K_RIGHT)
				{
					a_joystickStates[10]->w = 1;
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
					a_joystickStates[10]->x = 0;
				}
				else if (event.key.keysym.sym == playerInput.P1K_DOWN)
				{
					a_joystickStates[10]->y = 0;
				}
				else if (event.key.keysym.sym == playerInput.P1K_LEFT)
				{
					a_joystickStates[10]->z = 0;
				}
				else if (event.key.keysym.sym == playerInput.P1K_RIGHT)
				{
					a_joystickStates[10]->w = 0;
				}
				break;
			/////////////////////////////////////////////////////////////////
			//HANDLE FIGHT STICKS
			/////////////////////////////////////////////////////////////////
			case SDL_JOYAXISMOTION:
				if ( event.jaxis.axis == 0 )
					if (event.jaxis.value > deadZone)
					{
					a_joystickStates[event.jaxis.which]->w = 1;
					}
					else if (event.jaxis.value < -deadZone)
					{
						a_joystickStates[event.jaxis.which]->z = 1;
					}
					else { a_joystickStates[event.jaxis.which]->w = 0; a_joystickStates[event.jaxis.which]->z = 0; }

				else if (event.jaxis.axis == 1)
					if (event.jaxis.value > deadZone)
					{
					a_joystickStates[event.jaxis.which]->y = 1;
					}
					else if (event.jaxis.value < -deadZone)
					{
						a_joystickStates[event.jaxis.which]->x = 1;
					}
					else { a_joystickStates[event.jaxis.which]->x = 0; a_joystickStates[event.jaxis.which]->y = 0; }
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
