#ifndef __Game__
#define __Game__

#include <vector>
#include <memory>
#include "NodeGraph.hpp"
#include "GameStateMachine.hpp"
#ifdef __arm__
#include <SDL2/SDL_opengles2.h>
#else
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#endif

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
    Game() {}
    ~Game() {}
    static Game *instance;

public:
    static Game *getInstance();
    bool init();
    void handleEvents();
    void update();
    void render();
    void clean();
    void quit() {running = false;}
    
    //accessor functions
    bool getRunning() const { return running; }
    SDL_Renderer *getRenderer() const { return renderer; }    
    GameStateMachine *getStateMachine() { return gameStateMachine; }
    

private:
    
    const GLubyte* GLversion;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext GLContext;
    bool hasOpenGL;
    bool running;
    GameStateMachine *gameStateMachine;
};

typedef Game TheGame;

#endif // __Game__
