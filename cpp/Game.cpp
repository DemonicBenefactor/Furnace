#include <iostream>
#include "Game.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "TextureManager.hpp"
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

bool Game::init(const char *title, int xpos, int ypos,
                int width, int height, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        int flags = 0;
        if (fullscreen)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }
        
        std::cout << "SDL init success" << std::endl;
        m_pWindow = SDL_CreateWindow(title, xpos, ypos,
                width, height, flags);
        if (m_pWindow != 0)
        {
            std::cout << "Window creation success" << std::endl;
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != 0)
            {
                std::cout << "Renderer creation success" << std::endl;
                SDL_SetRenderDrawColor(m_pRenderer, 128, 128, 128, 255);
            }
            else
            {
                std::cout << "Renderer creation failed" << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "Window init failed" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "SDL init failed" << std::endl;
        return false;
    }

    std::cout << "Init success!" << std::endl;
    m_bRunning = true;
    //start the stateMachine and load a state
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());
    
	//Load images
    if (!TheTextureManager::getInstance()->load("resources/images/digit15.png", "5", m_pRenderer))
    {
        throw std::runtime_error("image not found");
    }

	m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 75, 75, "5")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 75, 75, "5")));

    return true;
}


void Game::handleEvents()
{
    TheInputHandler::getInstance()->update();
    if (TheInputHandler::getInstance()->getKey(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
    if (TheInputHandler::getInstance()->getKey(SDL_SCANCODE_ESCAPE))
    {
        quit();
    }
}


void Game::render()
{
    SDL_RenderClear(m_pRenderer);
	for (std::vector<GameObject*>::size_type i = 0;
			i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

    SDL_RenderPresent(m_pRenderer);
}


void Game::update()
{
	for (std::vector<GameObject*>::size_type i = 0;
			i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void Game::clean()
{
    std::cout << "Cleaning Up" << std::endl;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

//===============MAIN======================================

int main(int argc, char *argv[])
{
    std::cout << "Initializing Furnace..." << std::endl;
    if (TheGame::getInstance()->init("FurnaceXX", 
                100, 100, 640, 480, false))
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
