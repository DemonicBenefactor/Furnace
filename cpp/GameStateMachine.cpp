#include <iostream>
#include "GameStateMachine.hpp"

void GameStateMachine::pushState(GameState *pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState *pState)
{
    if (!m_gameStates.empty())
    {
        if (m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return; //do nothing
        }
        if (m_gameStates.back()->onExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
    if (!m_gameStates.empty() && m_gameStates.back()->onExit())
    {
        delete m_gameStates.back();
        m_gameStates.pop_back();
    }
}

//============= MENU STATE ====================

const std::string MenuState::s_menuID = "MENU";

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

const std::string PlayState::s_playID = "PLAY";

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
