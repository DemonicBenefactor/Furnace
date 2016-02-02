#include <stdio.h>
#include "game.h"

// INIT FUNCTION ============================================================
bool FUR_init( const char* title, int xpos, int ypos, int width, int height, bool fullscreen )
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == 0 )
    {
	printf( "SDL init success\n" );
	// init the window
	pWindow = SDL_CreateWindow( title, xpos, ypos, width, height, fullscreen );
	if ( pWindow != 0 ) // window init success
	{
	    printf( "window creation success\n" );
	    pRenderer = SDL_CreateRenderer( pWindow, -1, 0 );
	    if ( pRenderer != 0 ) // renderer init success
	    {
		printf( "renderer init success\n" );
		SDL_RenderSetLogicalSize(pRenderer, 640, 480);
		SDL_SetRenderDrawColor( pRenderer, 200, 200, 200, 255 );
		FUR_createObject( "images/biped.png",0, -50.0f, 150.0f, 250,250,0,0,0.0,255,pRenderer,SDL_FLIP_NONE );
		FUR_createObject( "images/biped.png",1, 420.0f, 150.0f, 250,250,0,0,0.0,255,pRenderer,SDL_FLIP_HORIZONTAL );
		FUR_initPlayerInput();
		//FUR_textureLoad("images/biped.png", 0, pRenderer);
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
    gameRunning = true; // init successful, start main loop

    return true;
}

// RENDER FUNCTION ============================================================
void FUR_render()
{
    SDL_RenderClear( pRenderer  ); // clear the renderer to draw the color

    FUR_drawObject( pRenderer, a_gameObjects[0] );
    FUR_drawObject( pRenderer, a_gameObjects[1] );
    //FUR_textureDrawFrame(0, -50, 150, 250, 250, 0, 0, 0, 255, m_pRenderer, SDL_FLIP_NONE);

    SDL_RenderPresent( pRenderer ); // draw to the screen
}

// UPDATE FUNCTION ============================================================
void FUR_update()
{
	FUR_updateObject(a_gameObjects[0]);
}

// CLEAN FUNCTION===============================================================
void FUR_clean()
{
    printf( "cleaning up the game\n" );
    FUR_cleanEvents();
    SDL_DestroyWindow( pWindow );
    SDL_DestroyRenderer( pRenderer );
    SDL_Quit();
}
	
