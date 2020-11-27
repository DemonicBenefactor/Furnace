#include <iostream>
#include <map>
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "ResourceManager.hpp"
#include "Gui.hpp"

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
}
void GameStateMachine::render()
{
    if (!mGameStates.empty())
    {
        mGameStates.back()->render();
    }
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

    std::unique_ptr<Button> LocalButton(new Button(new LoaderParams(10, 10, 124, 38, "MenuButtons")));
    std::unique_ptr<Button> OnlineButton(new Button(new LoaderParams(10, 50, 124, 38, "MenuButtons")));
    std::unique_ptr<Button> OptionButton(new Button(new LoaderParams(10, 90, 124, 38, "MenuButtons")));
    std::unique_ptr<SDLSceneNode> Background(new SDLSceneNode(new LoaderParams(0, 0, 320, 240, "BlueMoon")));
    OnlineButton->setRow(2); 
    OptionButton->setRow(3);
    mSceneNodes.push_back(std::move(Background));
    mSceneNodes.push_back(std::move(LocalButton));
    mSceneNodes.push_back(std::move(OnlineButton));
    mSceneNodes.push_back(std::move(OptionButton));

    
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
    TheResourceManager::getInstance()->clearTexture("MenuButtons");
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
