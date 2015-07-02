#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"
#include "handleEvents.h"

int main( int argc, char* argv[])
{
    FUR_init( "Furnace", 100, 100, 640, 480, 0);

    while( m_bRunning )
    {
	FUR_handleEvents();
	FUR_update();
	FUR_render();
    }

    FUR_clean();
    return 0;
}



