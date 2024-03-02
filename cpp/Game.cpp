#include <iostream>
#include "Game.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "ResourceManager.hpp"
#include "InputHandler.hpp"

#define __arm__

bool Game::init()
{    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
      #ifdef __arm__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
      #else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
      #endif
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        int flags = 0;
        if (FULLSCREEN)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }
        
        std::cout << "SDL init success" << std::endl;
        window = SDL_CreateWindow("FurnaceXX", WIN_POSX, WIN_POSY,
            WIN_W, WIN_H, flags | SDL_WINDOW_OPENGL);
        if (window != 0)
        {
            std::cout << "Window creation success" << std::endl;
            // startup our OpenGL
            GLContext = SDL_GL_CreateContext(window);
            if (GLContext == NULL)
            {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                //throw std::runtime_error("OpenGL Fail"); // openGL version fail
            }
            GLversion = glGetString(GL_VERSION);
            printf("openGL version %s\n", GLversion);
          #ifdef __arm__
                std::cout << "Using OpenGL ES 2" << std::endl;
                hasOpenGL = true;
          #else
            hasOpenGL = true;
            if (GLversion < (GLubyte*)'2') 
            {
                printf("openGL version %s not high enough\n", GLversion);
                //throw std::runtime_error("OpenGL Fail"); // openGL version fail
                hasOpenGL = false;
            }
            else
            {
                GLenum err;
                glewExperimental = GL_TRUE;
                err = glewInit();
                if (GLEW_OK != err)
                {
                    std::cout << "Error: " << glewGetErrorString(err) << std::endl;
                }
                std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
            }

			#endif
            //Finished with our OpenGL init,  make whatever calls -
            //you want to our MainContext,  have fun.
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer != 0)
            {
                std::cout << "Renderer creation success" << std::endl;
                SDL_RenderSetLogicalSize(renderer, 320, 240);
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                if (hasOpenGL)
                {
                    SDL_GL_SetSwapInterval(1);
                    glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(window);
                }
            }
            else
            {
                throw std::runtime_error( "Renderer creation failed");
                return false;
            }
        }
        else
        {
            throw std::runtime_error("Window init failed");
            return false;
        }
    }
    else
    {
        throw std::runtime_error("SDL init failed");
        return false;
    }

    std::cout << "Init success!" << std::endl;
    
    gameStateMachine = new GameStateMachine();
    gameStateMachine->setState(current_state::MENU);
    running = true;
    return running;
}


void Game::handleEvents()
{
    InputHandler::Get().update();    
}


void Game::render()
{
    SDL_RenderClear(renderer);
    gameStateMachine->render();
    SDL_RenderPresent(renderer);
}


void Game::update()
{
    gameStateMachine->update();
}

void Game::clean()
{
    std::cout << "Cleaning Up" << std::endl;
    gameStateMachine->clean();
    ResourceManager::Get().clean();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

//===============MAIN======================================

int main(int argc, char *argv[])
{
    std::cout << "Initializing Furnace..." << std::endl;
    if (Game::Get().init())
    {
        std::cout << "Initialization success." << std::endl;
        Uint32 frameStart, frameTime = 0;
        
        while (Game::Get().getRunning())
        {
            frameStart = SDL_GetTicks();
            Game::Get().handleEvents();
            Game::Get().update();
            Game::Get().render();
            frameTime = SDL_GetTicks() - frameStart;
            if(frameTime < DELAY_TIME)
            {
                SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
            }
        }
    }
    else
    {
        std::cout << "Initialization Failed - " << SDL_GetError()
            << std::endl;
        return -1;
    }

    std::cout << "Closing Furnace.." <<  std::endl;
    Game::Get().clean();
    return 0;   
}
