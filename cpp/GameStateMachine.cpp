#include <iostream>
#include <map>
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "ResourceManager.hpp"
#include "Gui.hpp"
#include "Player.hpp"

void GameStateMachine::push(std::shared_ptr<GameState> state)
{
    gameStates.push_back(state);
    gameStates.back()->onEnter();
}

void GameStateMachine::change(std::shared_ptr<GameState> state)
{
    if (!gameStates.empty())
    {
        if (gameStates.back()->getStateID() == state->getStateID())
        {
            return; //do nothing
        }
        clean();
    }
    gameStates.push_back(state);
    gameStates.back()->onEnter();
}

void GameStateMachine::update()
{
    if (!gameStates.empty())
    {
        gameStates.back()->update();
    }
    if (popState)
	{
		if (!gameStates.empty() && gameStates.back()->onExit())
		{
			gameStates.pop_back();
			popState = false;
		}
	}
	if (changeState)
    {
        switch (currentState)
        {
        case current_state::MENU:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<MenuState>());
            changeState = false;
            break;
        case current_state::LOCAL:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<LocalState>());
            changeState = false;
            break;
        case current_state::ONLINE:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<OnlineState>());
            changeState = false;
            break;
        case current_state::OPTIONS:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<OptionsState>());
            changeState = false;
			break;
        case current_state::PAUSE:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<PauseState>());
            changeState = false;
			break;
        default: break;
        }
    }
}

void GameStateMachine::render()
{
    if (!gameStates.empty())
    {
        gameStates.back()->render();
    }
}

void GameStateMachine::clean()
{
    for (auto &i : gameStates) i->onExit();
    gameStates.clear();
}

//===================== MENU STATE =======================

const std::string MenuState::menuID = "MENU";
bool MenuState::onEnter()
{
    std::cout << "entering MenuState" << std::endl;

    std::map<std::string, std::string> lImages
    {
        {"resources/images/Buttons.gif", "MenuButtons"},
        {"resources/images/BlueMoon.gif","BlueMoon"}
    };
    for (auto &i : lImages)    
    {
        TheResourceManager::getInstance()->loadTexture(i.first, i.second,
            TheGame::getInstance()->getRenderer());
    }

    std::unique_ptr<SDLSceneNode> background(std::make_unique<SDLSceneNode>(std::make_shared<LoaderParams>(-200, -240, 768, 480, "BlueMoon")));
    std::unique_ptr<Button> localButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 10, 125, 40, "MenuButtons"), buttonLocal));
    std::unique_ptr<Button> onlineButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 50, 125, 40, "MenuButtons"), buttonOnline));
    std::unique_ptr<Button> optionButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 90, 125, 40, "MenuButtons"), buttonOptions));
    std::unique_ptr<Button> exitButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 130, 125, 40, "MenuButtons"), buttonExit));
    onlineButton->setRow(2);
    optionButton->setRow(3);
    exitButton->setRow(4);
    sceneNodes.push_back(std::move(background));
    sceneNodes.push_back(std::move(localButton));
    sceneNodes.push_back(std::move(onlineButton));
    sceneNodes.push_back(std::move(optionButton));
    sceneNodes.push_back(std::move(exitButton));

    return true;
}

void MenuState::update()
{
    /*for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0; 
        i != mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->update();
    }*/  //THE OLD WAY,  NOW WE DO IT LIKE THIS:
    for (auto &i : sceneNodes) i->update();
}

void MenuState::render()
{
    for (auto &i : sceneNodes) i->draw();
}

bool MenuState::onExit()
{
    std::cout << "exiting MenuState" << std::endl;

    for (auto &i : sceneNodes) i->clean();
    sceneNodes.clear();
    return true;
}

void MenuState::buttonLocal()
{
    TheGame::getInstance()->getStateMachine()->setState(current_state::LOCAL);
}

void MenuState::buttonExit()
{
    TheGame::getInstance()->quit();
}

//====================== LOCAL STATE =========================

const std::string LocalState::localID = "LOCAL";
bool LocalState::onEnter()
{
    std::cout << "entering LocalState" << std::endl;

    std::map<std::string, std::string> lImages
    {
        {"resources/images/ZeldaWS.gif", "Zelda"},
        {"resources/images/DrWillysLab.gif","WillysLab"}
    };
    for (auto &i : lImages) 
    {
        TheResourceManager::getInstance()->loadTexture(i.first, i.second,
            TheGame::getInstance()->getRenderer());
    }

    std::unique_ptr<SDLSceneNode> background(std::make_unique<SDLSceneNode>(std::make_shared<LoaderParams>(-200, -240, 768, 480, "WillysLab")));
    std::unique_ptr<Player> player(std::make_unique<Player>(std::make_shared<LoaderParams>(100, 100, 75, 75, "Zelda")));
    sceneNodes.push_back(std::move(background));
    sceneNodes.push_back(std::move(player));

    return true;
}

void LocalState::update()
{
    if (TheInputHandler::getInstance()->getKey(SDL_SCANCODE_ESCAPE))
    {
        TheGame::getInstance()->getStateMachine()->push(std::make_shared<PauseState>());
    }
	for (auto &i : sceneNodes) i->update();
}

void LocalState::render()
{
    for (auto &i : sceneNodes) i->draw();
}

bool LocalState::onExit()
{
    std::cout << "exiting LocalState" << std::endl;
    for (auto &i : sceneNodes) i->clean();
    sceneNodes.clear();
    return true;
}
//====================== ONLINE STATE =========================

const std::string OnlineState::onlineID = "ONLINE";

//=====================OPTIONS STATE ========================

const std::string OptionsState::optionsID = "OPTIONS";

//====================== PAUSE STATE =========================

const std::string PauseState::pauseID = "PAUSE";

bool PauseState::onEnter()
{
    std::map<std::string, std::string> lImages
    {
        {"resources/images/Buttons.gif", "MenuButtons"},
        {"resources/images/Daily.gif","Daily"}
    };
    for (auto &i : lImages)
    {
        TheResourceManager::getInstance()->loadTexture(i.first, i.second,
            TheGame::getInstance()->getRenderer());
    }
	
	std::unique_ptr<SDLSceneNode> background(std::make_unique<SDLSceneNode>(std::make_shared<LoaderParams>(-200, -240, 768, 480, "Daily")));
    std::unique_ptr<Button> resumeButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 10, 125, 40, "MenuButtons"), buttonResume));
    std::unique_ptr<Button> menuButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 50, 125, 40, "MenuButtons"), buttonMenu));

    menuButton->setRow(2);
    sceneNodes.push_back(std::move(background));
    sceneNodes.push_back(std::move(resumeButton));
    sceneNodes.push_back(std::move(menuButton));

    std::cout << "Entering Pause State." << std::endl;
    return true;
}

void PauseState::update()
{
	for (auto &i : sceneNodes) i->update();
}

void PauseState::render()
{
    for (auto &i : sceneNodes) i->draw();
}

bool PauseState::onExit()
{
    std::cout << "exiting PauseState" << std::endl;
    for (auto &i : sceneNodes) i->clean();
    sceneNodes.clear();
    return true;
}

void PauseState::buttonResume()
{
    TheGame::getInstance()->getStateMachine()->pop();
}

void PauseState::buttonMenu()
{
	TheGame::getInstance()->getStateMachine()->setState(current_state::MENU);
}
