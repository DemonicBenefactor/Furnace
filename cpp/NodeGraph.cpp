#include "NodeGraph.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"

void SDLSceneNode::load(const std::shared_ptr<LoaderParams> params) {
  position = {params->getX(), params->getY()};
  velocity = {0, 0};
  acceleration = {0, 0};
  width = params->getWidth();
  height = params->getHeight();
  id = params->getTextureID();
  callbackID = params->getCallbackID();
  currentRow = 1;
  currentFrame = 0;
}

void SDLSceneNode::draw() {
  TheResourceManager::getInstance()->drawTexture(
      id, static_cast<int>(position.x), static_cast<int>(position.y), width,
      height, currentRow, currentFrame, TheGame::getInstance()->getRenderer());
}

void SDLSceneNode::update() {
  velocity += acceleration;
  position += velocity;
}

void SDLSceneNode::clean() {
  TheResourceManager::getInstance()->clearTexture(id);
}
