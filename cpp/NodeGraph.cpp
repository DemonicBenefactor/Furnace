#include "NodeGraph.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"

void Node2D::load(const std::shared_ptr<LoaderParams> params) {
  position = {params->x, params->y};
  velocity = {0, 0};
  acceleration = {0, 0};
  width = params->width;
  height = params->height;
  id = params->id;
  callbackID = params->callback;
  currentRow = 1;
  currentFrame = 0;
}

void Node2D::draw() {
  ResourceManager::Get().drawTexture(
      id, static_cast<int>(position.x), static_cast<int>(position.y), width,
      height, currentRow, currentFrame, Game::Get().getRenderer());
}

void Node2D::update() {
  velocity += acceleration;
  position += velocity;
}

void Node2D::clean() {
  ResourceManager::Get().clearTexture(id);
}
