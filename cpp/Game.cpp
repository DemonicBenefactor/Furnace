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

Game::Game() : mRunning(true), mGameStateMachine(nullptr), mRenderer(nullptr),
mWindow(nullptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
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
            if (mGLversion < (GLubyte*)'2') 
            {
                printf("openGL version %s not high enough\n", mGLversion);
                throw std::runtime_error("OpenGL Fail"); // openGL version fail
            }
            //Finished with our OpenGL init,  make whatever calls -
            //you want to our MainContext,  have fun.
            mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
            if (mRenderer != 0)
            {
                std::cout << "Renderer creation success" << std::endl;
                SDL_RenderSetLogicalSize(mRenderer, 384, 224);
                SDL_SetRenderDrawColor(mRenderer, 128, 128, 128, 255);
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

    if (!TheResourceManager::getInstance()->loadTexture("resources/images/ZeldaWS.gif", "5", mRenderer))
    {
        throw std::runtime_error("image not found");
    }

    std::unique_ptr<Player> p(new Player(new LoaderParams(100, 100, 75, 75, "5")));
    mSceneNodes.push_back(std::move(p));
   	//mSceneNodes.push_back(new Player(new LoaderParams(100, 100, 75, 75, "5")));
	//mSceneNodes.push_back(new Enemy(new LoaderParams(300, 300, 75, 75, "5")));    
    
    mGameStateMachine = new GameStateMachine();
    mGameStateMachine->changeState(new MenuState());

    mRunning = true;
}


void Game::handleEvents()
{
    TheInputHandler::getInstance()->update();
    if (TheInputHandler::getInstance()->getKey(SDL_SCANCODE_RETURN))
    {
        mGameStateMachine->changeState(new PlayState());
    }
    if (TheInputHandler::getInstance()->getKey(SDL_SCANCODE_ESCAPE))
    {
        quit();
    }
}


void Game::render()
{
    SDL_RenderClear(mRenderer);
	for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0;
			i != mSceneNodes.size(); i++)
	{
		mSceneNodes[i]->draw();
	}

    SDL_RenderPresent(mRenderer);
}


void Game::update()
{
	for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0;
			i != mSceneNodes.size(); i++)
	{
		mSceneNodes[i]->update();
	}
}

void Game::clean()
{
    std::cout << "Cleaning Up" << std::endl;
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

//===============MAIN======================================

int main(int argc, char *argv[])
{
    std::cout << "Initializing Furnace..." << std::endl;
    if (TheGame::getInstance()->running())
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
