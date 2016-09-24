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

#include <stdio.h>
#include <stdlib.h>
#include "game.h"


// INIT FUNCTION ============================================================
bool FUR_init( const char* title, int xpos, int ypos, 
		int width, int height, bool fullscreen )
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == 0 )
    {
	printf( "SDL init success\n" );
	// init the window
	pWindow = SDL_CreateWindow( title, xpos, ypos, width, 
					height, fullscreen );
	if ( pWindow != 0 ) // window init success
	{
	    // startup our OpenGL
		MainContext = SDL_GL_CreateContext(pWindow);
		GLubyte* openGL_version = glGetString(GL_VERSION);
		if (openGL_version < '2') {
			printf("openGL version %s not high enough", openGL_version);
			return false; // openGL version fail
		}
		//Finished with our OpenGL init,  make whatever calls -
		//you want to our MainContext,  have fun.

		FUR_initialiseJoysticks();
	    FUR_initPlayerInput();
	    printf( "window creation success\n" );
	    pRenderer = SDL_CreateRenderer( pWindow, -1, 
			    			SDL_RENDERER_PRESENTVSYNC );
	    if ( pRenderer != 0 ) // renderer init success
	    {
		printf( "renderer init success\n" );
		SDL_RenderSetLogicalSize(pRenderer, 855, 480);
		SDL_SetRenderDrawColor( pRenderer, 200, 200, 200, 255 );
		FUR_initPlayers( pRenderer, Demonic, Zoe );
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
    FUR_renderPlayers( pRenderer, a_players[0], a_players[1] ); 
    SDL_RenderPresent( pRenderer ); // draw to the screen
}

// UPDATE FUNCTION ============================================================
void FUR_update()
{
	FUR_updatePlayers();
}

// CLEAN FUNCTION===============================================================
void FUR_clean()
{
    printf( "cleaning up the game\n" );
    FUR_cleanEvents();
    SDL_DestroyWindow( pWindow );
    SDL_DestroyRenderer( pRenderer );
	SDL_GL_DeleteContext(MainContext);
    SDL_Quit();
}
	
void FUR_testMessage(const char* text)
{
	SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION,
		"message", text, NULL );
}
