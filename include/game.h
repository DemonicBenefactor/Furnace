#ifndef __game__
#define __game__

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "textureManager.h"

int m_currentFrame;
bool m_bRunning;

bool FUR_init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

void FUR_render();
void FUR_update();
void FUR_clean();

SDL_Window* m_pWindow;
SDL_Renderer* m_pRenderer;

#endif
