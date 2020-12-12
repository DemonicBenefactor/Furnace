#include <iostream>
#include <map>
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "ResourceManager.hpp"
#include "Gui.hpp"
#include "Player.hpp"

void GameStateMachine::push(GameState *pState)
{
    mGameStates.push_back(pState);
    mGameStates.back()->onEnter();
}

void GameStateMachine::change(GameState *pState)
{
    if (!mGameStates.empty())
    {
        if (mGameStates.back()->getStateID() == pState->getStateID())
        {
            return; //do nothing
        }
        if (mGameStates.back()->onExit())
        {
            delete mGameStates.back();
            mGameStates.pop_back();
        }
    }
    mGameStates.push_back(pState);
    mGameStates.back()->onEnter();
}

void GameStateMachine::pop()
{
    if (!mGameStates.empty() && mGameStates.back()->onExit())
    {
        delete mGameStates.back();
        mGameStates.pop_back();
    }
}
void GameStateMachine::update()
{
    if (!mGameStates.empty())
    {
        mGameStates.back()->update();
    }
    if (mChangeState)
    {
        switch (mCurrentState)
        {
        case current_state::MENU:
            TheGame::getInstance()->getStateMachine()->change(new MenuState());
            mChangeState = false;
            break;
        case current_state::LOCAL:
            TheGame::getInstance()->getStateMachine()->change(new LocalState());
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
    for (unsigned i = 0; i < mGameStates.size(); i++)
    {
        mGameStates[i]->onExit();
    }
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
    std::map<std::string, std::string>::iterator i;
    for (i = lImages.begin(); i != lImages.end(); i++)
    {
        TheResourceManager::getInstance()->loadTexture(i->first, i->second,
            TheGame::getInstance()->getRenderer());
    }

    std::unique_ptr<SDLSceneNode> background(new SDLSceneNode(new LoaderParams(-200, -240, 768, 480, "BlueMoon")));
    std::unique_ptr<Button> localButton(new Button(new LoaderParams(10, 10, 125, 40, "MenuButtons"), sButtonLocal));
    std::unique_ptr<Button> onlineButton(new Button(new LoaderParams(10, 50, 125, 40, "MenuButtons"), sButtonOnline));
    std::unique_ptr<Button> optionButton(new Button(new LoaderParams(10, 90, 125, 40, "MenuButtons"), sButtonOptions));
    std::unique_ptr<Button> exitButton(new Button(new LoaderParams(10, 130, 125, 40, "MenuButtons"), sButtonExit));
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
    for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0; 
        i != mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->update();
    }
}

void MenuState::render()
{
    for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0; 
        i != mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->draw();
    }
}

bool MenuState::onExit()
{
    std::cout << "exiting MenuState" << std::endl;

    for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0; 
        i != mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->clean();
    }
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

//====================== Local STATE =========================

const std::string LocalState::sLocalID = "LOCAL";
bool LocalState::onEnter()
{
    std::cout << "entering LocalState" << std::endl;

    std::map<std::string, std::string> lImages
    {
        {"resources/images/ZeldaWS.gif", "Zelda"},
        {"resources/images/DrWillysLab.gif","WillysLab"}
    };
    std::map<std::string, std::string>::iterator i;
    for (i = lImages.begin(); i != lImages.end(); i++)
    {
        TheResourceManager::getInstance()->loadTexture(i->first, i->second,
            TheGame::getInstance()->getRenderer());
    }

    std::unique_ptr<SDLSceneNode> background(new SDLSceneNode(new LoaderParams(-200, -240, 768, 480, "WillysLab")));
    std::unique_ptr<Player> player(new Player(new LoaderParams(100, 100, 75, 75, "Zelda")));
    mSceneNodes.push_back(std::move(background));
    mSceneNodes.push_back(std::move(player));

    return true;
}

void LocalState::update()
{
    for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0;
        i != mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->update();
    }
}

void LocalState::render()
{
    for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0;
        i != mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->draw();
    }
}

bool LocalState::onExit()
{
    std::cout << "exiting LocalState" << std::endl;
    for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0;
        i != mSceneNodes.size(); i++)
    {
        mSceneNodes[i]->clean();
    }
    mSceneNodes.clear();
    return true;
}

//====================== Pause STATE =========================

const std::string PauseState::sPauseID = "PAUSE";