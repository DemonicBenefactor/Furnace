#ifndef __game__
#define __game__

#include <stdbool.h>
#include <SDL2/SDL.h>

bool m_bRunning;

bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

void render();
void update();
void handleEvents();
void clean();

SDL_Window* m_pWindow;
SDL_Renderer* m_pRenderer;

#endif
