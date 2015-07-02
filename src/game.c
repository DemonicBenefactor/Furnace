#include <stdio.h>
#include "game.h"

// INIT FUNCTION ============================================================
bool FUR_init( const char* title, int xpos, int ypos, int width, int height, bool fullscreen )
{
    int flags = 0;
    
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == 0 )
    {
	printf( "SDL init success\n" );
	// init the window
	m_pWindow = SDL_CreateWindow( title, xpos, ypos, width, height, flags );
	if ( m_pWindow != 0 ) // window init success
	{
	    printf( "window creation success\n" );
	    m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, 0 );
	    if ( m_pRenderer != 0 ) // renderer init success
	    {
		printf( "renderer init success\n" );
		SDL_SetRenderDrawColor( m_pRenderer, 255, 255, 255, 255 );
	    }
	    else
	    {
		printf( "renderer init fail\n" );
		return false; // renderer init fail
	    }
	}
	else
	{
	    printf( "window init fail\n" );
	    return false; // window init fail
	}
    }
    else
    {
	printf( "SDL init fail\n" );
	return false; // SDL init fail
    }

    printf( "SDL init success\n" );
    m_bRunning = true; // init successful, start main loop

    return true;
}

// RENDER FUNCTION ============================================================
void FUR_render()
{
    SDL_RenderClear( m_pRenderer  ); // clear the renderer to draw the color
    SDL_RenderPresent( m_pRenderer ); // draw to the screen
}

// UPDATE FUNCTION ============================================================
void FUR_update()
{
}

// CLEAN FUNCTION===============================================================
void FUR_clean()
{
    printf( "cleaning up the game\n" );
    SDL_DestroyWindow( m_pWindow );
    SDL_DestroyRenderer( m_pRenderer );
    SDL_Quit();
}
	
