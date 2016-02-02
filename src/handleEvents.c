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
	    if ( i < 10 )
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

    if ( SDL_PollEvent( &event ) )
	{
	    switch ( event.type )
		{
		    case SDL_QUIT:
			gameRunning = false;
		    break;

		    case SDL_KEYDOWN:
		        //printf( " %s\n", SDL_GetKeyName( event.key.keysym.sym ) );
		    	if ( event.key.keysym.sym == SDLK_ESCAPE )
				{
					gameRunning = false;
				}
				else if ( event.key.keysym.sym == playerInput.P1K_UP )
				{
					gameRunning = false;
				}
				else if ( event.key.keysym.sym == playerInput.P1K_DOWN )
				{
				
				}
				break;
		    
		    case SDL_MOUSEBUTTONDOWN:
		    	gameRunning = false;
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
