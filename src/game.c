#include <stdio.h>
#include "game.h"


bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == 0 )
    {
	printf("SDL init success\n");
	//init the window
	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    }

    return true;
}
