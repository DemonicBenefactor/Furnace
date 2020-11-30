#include <iostream>
#include <map>
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "ResourceManager.hpp"
#include "Gui.hpp"

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
            TheGame::getInstance()->getStateMachine()->change(new PlayState());
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

//============= MENU STATE ====================

const std::string MenuState::sMenuID = "MENU";

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

    std::unique_ptr<SDLSceneNode> Background(new SDLSceneNode(new LoaderParams(-200, -240, 768, 480, "BlueMoon")));
    std::unique_ptr<Button> LocalButton(new Button(new LoaderParams(10, 10, 125, 40, "MenuButtons"), sButtonLocal));
    std::unique_ptr<Button> OnlineButton(new Button(new LoaderParams(10, 50, 125, 40, "MenuButtons"), sButtonOnline));
    std::unique_ptr<Button> OptionButton(new Button(new LoaderParams(10, 90, 125, 40, "MenuButtons"), sButtonOptions));
    std::unique_ptr<Button> ExitButton(new Button(new LoaderParams(10, 130, 125, 40, "MenuButtons"), sButtonExit));
    OnlineButton->setRow(2); 
    OptionButton->setRow(3);
    ExitButton->setRow(4);
    mSceneNodes.push_back(std::move(Background));
    mSceneNodes.push_back(std::move(LocalButton));
    mSceneNodes.push_back(std::move(OnlineButton));
    mSceneNodes.push_back(std::move(OptionButton));
    mSceneNodes.push_back(std::move(ExitButton));

    
    //TheResourceManager::getInstance()->loadTexture("resources/images/ZeldaWS.gif", "5", mRenderer);
    //std::unique_ptr<Player> p(new Player(new LoaderParams(100, 100, 75, 75, "5")));
    //mSceneNodes.push_back(std::move(p));

    return true;
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
