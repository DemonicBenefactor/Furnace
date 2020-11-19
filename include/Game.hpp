#ifndef __Game__
#define __Game__

#include <vector>
#include <memory>
#include "NodeGraph.hpp"
#include "GameStateMachine.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

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
    void quit() {mRunning = false;}
    
    //accessor functions
    bool running() const { return mRunning; }
    SDL_Renderer *getRenderer() const { return mRenderer; }    
    

private:
    
    const GLubyte* mGLversion;
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    SDL_GLContext GLContext; //FIXME

    bool mRunning;
    GameStateMachine *mGameStateMachine;
	std::vector<std::unique_ptr<SDLSceneNode>> mSceneNodes;
};

typedef Game TheGame;

#endif // __Game__
