#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"
#include "handleEvents.h"

#define FPS 60
#define DELAY_TIME 1000/FPS


int main( int argc, char* argv[])
{
    Uint32 frameStart, frameTime;
	
	FUR_init( "Furnace", 100, 100, 1920, 1080, true );
	
    while( gameRunning )
    {
	frameStart = SDL_GetTicks();

	FUR_handleEvents();
	FUR_update();
	FUR_render();

	frameTime = SDL_GetTicks() - frameStart;
	if ( frameTime < DELAY_TIME )
	{
		SDL_Delay( (int)( DELAY_TIME - frameTime ));
	}

    }

    FUR_clean();
    return 0;
}



