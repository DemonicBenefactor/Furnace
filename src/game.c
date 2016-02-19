#include <stdio.h>
#include <stdlib.h>
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
		FUR_initialiseJoysticks();
		FUR_initPlayerInput();
		printf( "window creation success\n" );
	    pRenderer = SDL_CreateRenderer( pWindow, -1, 0 );
	    if ( pRenderer != 0 ) // renderer init success
	    {
		printf( "renderer init success\n" );
		SDL_RenderSetLogicalSize(pRenderer, 640, 480);
		SDL_SetRenderDrawColor( pRenderer, 200, 200, 200, 255 );
		FUR_createObject( "images/biped.png",0, -50.0f, 150.0f, 250,250,0,0,0.0,255,pRenderer,SDL_FLIP_NONE );
		FUR_createObject( "images/biped.png",1, 420.0f, 150.0f, 250,250,0,0,0.0,255,pRenderer,SDL_FLIP_HORIZONTAL );
		FUR_initPlayer();
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
    SDL_RenderPresent( pRenderer ); // draw to the screen
}

// UPDATE FUNCTION ============================================================
void FUR_update()
{
	int i;
	
	FUR_updateObject(a_gameObjects[0]);
	for (i = 0; i < 4; i++)
	{
		if ( a_joysticks[i] != NULL )
		{
		if (playerInput.P1_UPDOWN > 0 && playerInput.P1_LEFTRIGHT > 0) { SDL_SetRenderDrawColor(pRenderer, 0, 50, 0, 255); } //upLeft
		else if (playerInput.P1_UPDOWN > 0 && playerInput.P1_LEFTRIGHT < 0) { SDL_SetRenderDrawColor(pRenderer, 50, 0, 0, 255); } //upRight
		else if (playerInput.P1_UPDOWN < 0 && playerInput.P1_LEFTRIGHT > 0) { SDL_SetRenderDrawColor(pRenderer, 0, 50, 50, 255); } //downLeft
		else if (playerInput.P1_UPDOWN < 0 && playerInput.P1_LEFTRIGHT < 0) { SDL_SetRenderDrawColor(pRenderer, 50, 0, 50, 255); } //downRight
		else if (playerInput.P1_UPDOWN > 0) { SDL_SetRenderDrawColor(pRenderer, 50, 50, 0, 255); } //up
		else if (playerInput.P1_UPDOWN < 0) { SDL_SetRenderDrawColor(pRenderer, 0, 0, 100, 255); } //down
		else if (playerInput.P1_LEFTRIGHT > 0) { SDL_SetRenderDrawColor(pRenderer, 0, 100, 0, 255); } //left
		else if (playerInput.P1_LEFTRIGHT < 0) { SDL_SetRenderDrawColor(pRenderer, 100, 0, 0, 255); } //right
		else { SDL_SetRenderDrawColor(pRenderer, 200, 200, 200, 255); }
	    }
	}
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
	
void FUR_testMessage(const char* text)
{
	SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION,
		"message", text, NULL );
}
