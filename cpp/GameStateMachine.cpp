#include "GameStateMachine.hpp"
#include "Game.hpp"
#include "Gui.hpp"
#include "InputHandler.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include <iostream>
#include <map>

void GameStateMachine::push(std::shared_ptr<GameState> state) {
  gameStates.push_back(state);
  gameStates.back()->onEnter();
}

void GameStateMachine::change(std::shared_ptr<GameState> state) {
  if (!gameStates.empty()) {
    if (gameStates.back()->getStateID() == state->getStateID()) {
      return; // do nothing
    }
    clean();
  }
  gameStates.push_back(state);
  gameStates.back()->onEnter();
}

void GameStateMachine::update() {
  if (!gameStates.empty()) {
    gameStates.back()->update();
  }
  if (popState) {
    if (!gameStates.empty() && gameStates.back()->onExit()) {
      gameStates.pop_back();
      popState = false;
    }
  }
  if (changeState) {
    switch (currentState) {
    case current_state::MENU:
      TheGame::getInstance()->getStateMachine()->change(
          std::make_shared<MenuState>());
      changeState = false;
      break;
    case current_state::LOCAL:
      TheGame::getInstance()->getStateMachine()->change(
          std::make_shared<LocalState>());
      changeState = false;
      break;
    case current_state::ONLINE:
      TheGame::getInstance()->getStateMachine()->change(
          std::make_shared<OnlineState>());
      changeState = false;
      break;
    case current_state::OPTIONS:
      TheGame::getInstance()->getStateMachine()->change(
          std::make_shared<OptionsState>());
      changeState = false;
      break;
    case current_state::PAUSE:
      TheGame::getInstance()->getStateMachine()->change(
          std::make_shared<PauseState>());
      changeState = false;
      break;
    default:
      break;
    }
  }
}

void GameStateMachine::render() {
  if (!gameStates.empty()) {
    gameStates.back()->render();
  }
}

void GameStateMachine::clean() {
  for (auto &i : gameStates)
    i->onExit();
  gameStates.clear();
}

//===================== MENU STATE =======================

const std::string MenuState::menuID = "MENU";

bool MenuState::onEnter() {
  TheResourceManager::getInstance()->loadJson("resources/json/GameStates.json",
                                              "MenuState", sceneNodes);

  for (auto &i : sceneNodes) {
    if (dynamic_cast<Button *>(i.get())) {
      switch (i->getCallbackID()) {
      case 1:
        dynamic_cast<Button *>(i.get())->setCallback(buttonLocal);
        break;
      case 2:
        dynamic_cast<Button *>(i.get())->setCallback(buttonOnline);
        break;
      case 3:
        dynamic_cast<Button *>(i.get())->setCallback(buttonOptions);
        break;
      case 4:
        dynamic_cast<Button *>(i.get())->setCallback(buttonExit);
        break;
      default:
        break;
      }
    }
  }
  return true;
}

void MenuState::update() {
  // for (std::vector<std::unique_ptr<SceneNode>>::size_type i = 0;
  //    i != mSceneNodes.size(); i++)
  //{
  //    mSceneNodes[i]->update();
  //}//  //THE OLD WAY,  NOW WE DO IT LIKE THIS:
  for (auto &i : sceneNodes)
    i->update();
}

void MenuState::render() {
  for (auto &i : sceneNodes)
    i->draw();
}

bool MenuState::onExit() {
  std::cout << "exiting MenuState" << std::endl;

  for (auto &i : sceneNodes)
    i->clean();
  sceneNodes.clear();
  return true;
}
void MenuState::buttonLocal() {
  TheGame::getInstance()->getStateMachine()->setState(current_state::LOCAL);
}

void MenuState::buttonExit() { TheGame::getInstance()->quit(); }

//====================== LOCAL STATE =========================

const std::string LocalState::localID = "LOCAL";

bool LocalState::onEnter() {
  TheResourceManager::getInstance()->loadJson("resources/json/GameStates.json",
                                              "LocalState", sceneNodes);

  return true;
}

void LocalState::update() {
  if (TheInputHandler::getInstance()->getKey(SDL_SCANCODE_ESCAPE)) {
    TheGame::getInstance()->getStateMachine()->push(
        std::make_shared<PauseState>());
  }
  for (auto &i : sceneNodes)
    i->update();
}

void LocalState::render() {
  for (auto &i : sceneNodes)
    i->draw();
}

bool LocalState::onExit() {
  std::cout << "exiting LocalState" << std::endl;
  for (auto &i : sceneNodes)
    i->clean();
  sceneNodes.clear();
  return true;
}

//====================== ONLINE STATE =========================

const std::string OnlineState::onlineID = "ONLINE";

//=====================OPTIONS STATE ========================

const std::string OptionsState::optionsID = "OPTIONS";

//====================== PAUSE STATE =========================

const std::string PauseState::pauseID = "PAUSE";

bool PauseState::onEnter() {
  TheResourceManager::getInstance()->loadJson("resources/json/GameStates.json",
                                              "PauseState", sceneNodes);
  for (auto &i : sceneNodes) {
    if (dynamic_cast<Button *>(i.get())) {
      switch (i->getCallbackID()) {
      case 1:
        dynamic_cast<Button *>(i.get())->setCallback(buttonResume);
        break;
      case 2:
        dynamic_cast<Button *>(i.get())->setCallback(buttonMenu);
        break;
      default:
        break;
      }
    }
  }
  std::cout << "Entering Pause State." << std::endl;
  return true;
}

void PauseState::update() {
  for (auto &i : sceneNodes)
    i->update();
}

void PauseState::render() {
  for (auto &i : sceneNodes)
    i->draw();
}

bool PauseState::onExit() {
  std::cout << "exiting PauseState" << std::endl;
  for (auto &i : sceneNodes)
    i->clean();
  sceneNodes.clear();
  return true;
}

void PauseState::buttonResume() {
  TheGame::getInstance()->getStateMachine()->pop();
}

void PauseState::buttonMenu() {
  TheGame::getInstance()->getStateMachine()->setState(current_state::MENU);
}

