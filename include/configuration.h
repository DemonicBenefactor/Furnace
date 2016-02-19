#ifndef __configuration__
#define __configuration__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct {
	//Transition storage to pass to the player state
	//All direction inputs dump into these integers
	int P1_UPDOWN;
	int P1_LEFTRIGHT;
	int P2_UPDOWN;
	int P2_LEFTRIGHT;
	//Player One Keyboard
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
	//Player One Controller
	SDL_JoystickID P1_Controller;	 
	Uint8 P1C_DPAD_UP; //for some reason 360 pads are registered as buttons.
	Uint8 P1C_DPAD_DOWN;
	Uint8 P1C_DPAD_LEFT;
	Uint8 P1C_DPAD_RIGHT;
	Uint8 P1C_LIGHTPUNCH;
	Uint8 P1C_MEDIUMPUNCH;
	Uint8 P1C_HARDPUNCH;
	Uint8 P1C_LIGHTKICK;
	Uint8 P1C_MEDIUMKICK;
	Uint8 P1C_HARDKICK;
	Uint8 P1C_START;
	Uint8 P1C_SELECT;
	//Player Two Keyboard
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
	//Player Two Controller
	SDL_JoystickID P2_Controller;
	Uint8 P2C_DPAD_UP; //for some reason 360 pads are registered as buttons.
	Uint8 P2C_DPAD_DOWN;
	Uint8 P2C_DPAD_LEFT;
	Uint8 P2C_DPAD_RIGHT;
	Uint8 P2C_LIGHTPUNCH;
	Uint8 P2C_MEDIUMPUNCH;
	Uint8 P2C_HARDPUNCH;
	Uint8 P2C_LIGHTKICK;
	Uint8 P2C_MEDIUMKICK;
	Uint8 P2C_HARDKICK;
	Uint8 P2C_START;
	Uint8 P2C_SELECT;
} playerInput;

void FUR_initPlayerInput();

#endif //  __configuration__
