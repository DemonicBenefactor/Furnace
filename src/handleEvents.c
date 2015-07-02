#include "handleEvents.h"

void FUR_handleEvents()
{
    SDL_Event event;
    
    if ( SDL_PollEvent( &event ) )
	{
	    switch ( event.type )
		{
		    case SDL_QUIT:
			m_bRunning = false;
		    break;

		    case SDL_KEYDOWN:
		        printf( " %s\n", SDL_GetKeyName( event.key.keysym.sym ) );
		    	switch ( event.key.keysym.sym )
			    {
				case SDLK_ESCAPE:
				    m_bRunning = false;
				    break;

				default:
				    break;
			    }
		    	break;
		    
		    case SDL_MOUSEBUTTONDOWN:
		    	m_bRunning = false;
		    	break;


		    default:
		    	break;	
		}
	}
}
