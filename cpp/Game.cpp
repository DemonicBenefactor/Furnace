#include <iostream>
#include "Game.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "ResourceManager.hpp"
#include "InputHandler.hpp"

///////////////////////Singleton Setup Start
Game *Game::instance = 0;
Game *Game::getInstance()
{
    if (instance == 0)
    {
        instance = new Game();
    }
    return instance;
}
/////////////////////////Singleton Setup End

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
        mWindow = SDL_CreateWindow("FurnaceXX", WIN_POSX, WIN_POSY,
            WIN_W, WIN_H, flags | SDL_WINDOW_OPENGL);
        if (mWindow != 0)
        {
            std::cout << "Window creation success" << std::endl;
            // startup our OpenGL
            GLContext = SDL_GL_CreateContext(mWindow);
            if (GLContext == NULL)
            {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                throw std::runtime_error("OpenGL Fail"); // openGL version fail
            }
            mGLversion = glGetString(GL_VERSION);
            printf("openGL version %s\n", mGLversion);
#ifdef __arm__
            std::cout << "Using OpenGL ES 2" << std::endl;
            mHasOpenGL = true;
#else
            mHasOpenGL = true;
            if (mGLversion < (GLubyte*)'2') 
            {
                printf("openGL version %s not high enough\n", mGLversion);
                throw std::runtime_error("OpenGL Fail"); // openGL version fail
                mHasOpenGL = false;
            }
#endif
            //Finished with our OpenGL init,  make whatever calls -
            //you want to our MainContext,  have fun.
            mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
            if (mRenderer != 0)
            {
                std::cout << "Renderer creation success" << std::endl;
                SDL_RenderSetLogicalSize(mRenderer, 320, 240);
                SDL_SetRenderDrawColor(mRenderer, 128, 128, 128, 255);
                if (mHasOpenGL)
                {
                    SDL_GL_SetSwapInterval(1);
                    glClearColor(0.2, 0.2, 0.2, 0.0);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(mWindow);
                }
            }
            else
            {
                throw std::runtime_error( "Renderer creation failed");
            }
        }
        else
        {
            throw std::runtime_error("Window init failed");
        }
    }
    else
    {
        throw std::runtime_error("SDL init failed");
    }

    std::cout << "Init success!" << std::endl;
    
    mGameStateMachine = new GameStateMachine();
    mGameStateMachine->setState(current_state::MENU);
    mRunning = true;
    return mRunning;
}


void Game::handleEvents()
{
    TheInputHandler::getInstance()->update();
    if (TheInputHandler::getInstance()->getKey(SDL_SCANCODE_ESCAPE))
    {
        quit();
    }
}


void Game::render()
{
    SDL_RenderClear(mRenderer);
    mGameStateMachine->render();
    SDL_RenderPresent(mRenderer);
}


void Game::update()
{
    mGameStateMachine->update();
}

void Game::clean()
{
    std::cout << "Cleaning Up" << std::endl;
    mGameStateMachine->clean();
    TheResourceManager::getInstance()->clean();
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

//===============MAIN======================================

int main(int argc, char *argv[])
{
    std::cout << "Initializing Furnace..." << std::endl;
    if (TheGame::getInstance()->init())
    {
        std::cout << "Initialization success." << std::endl;
        Uint32 frameStart, frameTime = 0;
        
        while (TheGame::getInstance()->running())
        {
            frameStart = SDL_GetTicks();
            TheGame::getInstance()->handleEvents();
            TheGame::getInstance()->update();
            TheGame::getInstance()->render();
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
    TheGame::getInstance()->clean();
    return 0;   
}
