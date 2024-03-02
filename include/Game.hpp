#ifndef __Game__
#define __Game__

#include "GameStateMachine.hpp"
#include "NodeGraph.hpp"
#include <memory>
#include <vector>
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

class Game {
public:
  Game(const Game &) = delete;
  Game(Game &&) = delete;
  Game &operator=(const Game &) = delete;
  Game &operator=(Game &&) = delete;

  static Game &Get() {
    static Game singleton;
    return singleton;
  }
  bool init();
  void handleEvents();
  void update();
  void render();
  void clean();
  void quit() { running = false; }

  // accessor functions
  bool getRunning() const { return running; }
  SDL_Renderer *getRenderer() const { return renderer; }
  GameStateMachine *getStateMachine() { return gameStateMachine; }

private:
  Game() {} // singleton

  const GLubyte *GLversion;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_GLContext GLContext;
  bool hasOpenGL;
  bool running;
  GameStateMachine *gameStateMachine;
};

#endif // __Game__
