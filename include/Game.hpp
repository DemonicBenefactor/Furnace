#ifndef __Game__
#define __Game__

#include <vector>
#include "GameObject.hpp"
#include "GameStateMachine.hpp"
#include "SDL2/SDL.h"

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;
const int WIN_POSX = 100;
const int WIN_POSY = 100;
const int WIN_W = 640;
const int WIN_H = 480;
const bool FULLSCREEN = false;

class Game
{
private:
    //singleton
    Game();
    ~Game() {}
    static Game *instance;

public:
    static Game *getInstance();
    void handleEvents();
    void update();
    void render();
    void clean();
    void quit() {m_bRunning = false;}
    
    //accessor functions
    bool running() const { return m_bRunning; }
    SDL_Renderer *getRenderer() const { return m_pRenderer; }    

private:
    
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    bool m_bRunning;
    GameStateMachine *m_pGameStateMachine;
	std::vector<GameObject*> m_gameObjects;
};

typedef Game TheGame;

#endif // __Game__
