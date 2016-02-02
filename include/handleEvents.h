#ifndef __handleEvents__
#define __handleEvents__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "vectors.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

bool bJoysticksInitialized;
SDL_Joystick* a_joysticks[10];
vector4D* a_joystickStates[10];


void FUR_initialiseJoysticks();
bool FUR_joysticksInitialised();
void FUR_handleEvents();
void FUR_cleanEvents();

#endif //  __handleEvents__
