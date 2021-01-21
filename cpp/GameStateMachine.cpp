#include <iostream>
#include <map>
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "ResourceManager.hpp"
#include "Gui.hpp"
#include "Player.hpp"

void GameStateMachine::push(std::shared_ptr<GameState> pState)
{
    mGameStates.push_back(pState);
    mGameStates.back()->onEnter();
}

void GameStateMachine::change(std::shared_ptr<GameState> pState)
{
    if (!mGameStates.empty())
    {
        if (mGameStates.back()->getStateID() == pState->getStateID())
        {
            return; //do nothing
        }
        clean();
    }
    mGameStates.push_back(pState);
    mGameStates.back()->onEnter();
}

void GameStateMachine::update()
{
    if (!mGameStates.empty())
    {
        mGameStates.back()->update();
    }
    if (mPopState)
	{
		if (!mGameStates.empty() && mGameStates.back()->onExit())
		{
			mGameStates.pop_back();
			mPopState = false;
		}
	}
	if (mChangeState)
    {
        switch (mCurrentState)
        {
        case current_state::MENU:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<MenuState>());
            mChangeState = false;
            break;
        case current_state::LOCAL:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<LocalState>());
            mChangeState = false;
            break;
        case current_state::ONLINE:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<OnlineState>());
            mChangeState = false;
            break;
        case current_state::OPTIONS:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<OptionsState>());
            mChangeState = false;
			break;
        case current_state::PAUSE:
            TheGame::getInstance()->getStateMachine()->change(std::make_shared<PauseState>());
            mChangeState = false;
			break;
        default: break;
        }
    }
}

void GameStateMachine::render()
{
    if (!mGameStates.empty())
    {
        mGameStates.back()->render();
    }
}

void GameStateMachine::clean()
{
    for (auto &i : mGameStates) i->onExit();
    mGameStates.clear();
}

//===================== MENU STATE =======================

const std::string MenuState::sMenuID = "MENU";
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
    std::unique_ptr<Button> localButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 10, 125, 40, "MenuButtons"), sButtonLocal));
    std::unique_ptr<Button> onlineButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 50, 125, 40, "MenuButtons"), sButtonOnline));
    std::unique_ptr<Button> optionButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 90, 125, 40, "MenuButtons"), sButtonOptions));
    std::unique_ptr<Button> exitButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 130, 125, 40, "MenuButtons"), sButtonExit));
    onlineButton->setRow(2);
    optionButton->setRow(3);
    exitButton->setRow(4);
    mSceneNodes.push_back(std::move(background));
    mSceneNodes.push_back(std::move(localButton));
    mSceneNodes.push_back(std::move(onlineButton));
    mSceneNodes.push_back(std::move(optionButton));
    mSceneNodes.push_back(std::move(exitButton));

    return true;
}

void MenuState::update()
{
    /*for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0; 
        i != mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->update();
    }*/  //THE OLD WAY,  NOW WE DO IT LIKE THIS:
    for (auto &i : mSceneNodes) i->update();
}

void MenuState::render()
{
    for (auto &i : mSceneNodes) i->draw();
}

bool MenuState::onExit()
{
    std::cout << "exiting MenuState" << std::endl;

    for (auto &i : mSceneNodes) i->clean();
    mSceneNodes.clear();
    return true;
}

void MenuState::sButtonLocal()
{
    TheGame::getInstance()->getStateMachine()->setState(current_state::LOCAL);
}

void MenuState::sButtonExit()
{
    TheGame::getInstance()->quit();
}

//====================== LOCAL STATE =========================

const std::string LocalState::sLocalID = "LOCAL";
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
    mSceneNodes.push_back(std::move(background));
    mSceneNodes.push_back(std::move(player));

    return true;
}

void LocalState::update()
{
    if (TheInputHandler::getInstance()->getKey(SDL_SCANCODE_ESCAPE))
    {
        TheGame::getInstance()->getStateMachine()->push(std::make_shared<PauseState>());
    }
	for (auto &i : mSceneNodes) i->update();
}

void LocalState::render()
{
    for (auto &i : mSceneNodes) i->draw();
}

bool LocalState::onExit()
{
    std::cout << "exiting LocalState" << std::endl;
    for (auto &i : mSceneNodes) i->clean();
    mSceneNodes.clear();
    return true;
}
//====================== ONLINE STATE =========================

const std::string OnlineState::sOnlineID = "ONLINE";

//=====================OPTIONS STATE ========================

const std::string OptionsState::sOptionsID = "OPTIONS";

//====================== PAUSE STATE =========================

const std::string PauseState::sPauseID = "PAUSE";

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
    std::unique_ptr<Button> resumeButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 10, 125, 40, "MenuButtons"), sButtonResume));
    std::unique_ptr<Button> menuButton(std::make_unique<Button>(std::make_shared<LoaderParams>(10, 50, 125, 40, "MenuButtons"), sButtonMenu));

    menuButton->setRow(2);
    mSceneNodes.push_back(std::move(background));
    mSceneNodes.push_back(std::move(resumeButton));
    mSceneNodes.push_back(std::move(menuButton));

    std::cout << "Entering Pause State." << std::endl;
    return true;
}

void PauseState::update()
{
	for (auto &i : mSceneNodes) i->update();
}

void PauseState::render()
{
    for (auto &i : mSceneNodes) i->draw();
}

bool PauseState::onExit()
{
    std::cout << "exiting PauseState" << std::endl;
    for (auto &i : mSceneNodes) i->clean();
    mSceneNodes.clear();
    return true;
}

void PauseState::sButtonResume()
{
    TheGame::getInstance()->getStateMachine()->pop();
}

void PauseState::sButtonMenu()
{
	TheGame::getInstance()->getStateMachine()->setState(current_state::MENU);
}
