#ifndef __configuration__
#define __configuration__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct {
	Sint32 P1K_UP;
	Sint32 P1K_DOWN;
	Sint32 P1K_LEFT;
	Sint32 P1K_RIGHT;
	Sint32 P1K_LIGHTPUNCH;
	Sint32 P1K_MEDIUMPUNCH;
	Sint32 P1K_HARDPUNCH;
	Sint32 P1K_LIGHTKICK;
	Sint32 P1K_MEDIUMKICK;
	Sint32 P1K_HARDKICK;
	//
	Sint32 P2K_UP;
	Sint32 P2K_DOWN;
	Sint32 P2K_LEFT;
	Sint32 P2K_RIGHT;
	Sint32 P2K_LIGHTPUNCH;
	Sint32 P2K_MEDIUMPUNCH;
	Sint32 P2K_HARDPUNCH;
	Sint32 P2K_LIGHTKICK;
	Sint32 P2K_MEDIUMKICK;
	Sint32 P2K_HARDKICK;
} playerInput;

void FUR_initPlayerInput();

#endif //  __configuration__
