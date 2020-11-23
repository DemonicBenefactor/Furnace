#include <iostream>
#include "GameStateMachine.hpp"

void GameStateMachine::pushState(GameState *pState)
{
    mGameStates.push_back(pState);
    mGameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState *pState)
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

void GameStateMachine::popState()
{
    if (!mGameStates.empty() && mGameStates.back()->onExit())
    {
        //delete mGameStates.back();
        mGameStates.pop_back();
    }
}

//============= MENU STATE ====================

const std::string MenuState::sMenuID = "MENU";

void MenuState::update()
{
    //UPDATE ME
}

void MenuState::render()
{
    //UPDATE ME
}

bool MenuState::onEnter()
{
    std::cout << "entering MenuState" << std::endl;
    return true;
}

bool MenuState::onExit()
{
    std::cout << "exiting MenuState" << std::endl;
    return true;
}

//============= PLAY STATE ====================

const std::string PlayState::sPlayID = "PLAY";

void PlayState::update()
{
    //UPDATE ME
}

void PlayState::render()
{
    //UPDATE ME
}

bool PlayState::onEnter()
{
    std::cout << "entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit()
{
    std::cout << "exiting PlayState" << std::endl;
    return true;
}
