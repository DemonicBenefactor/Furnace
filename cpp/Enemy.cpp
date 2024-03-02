#include "Enemy.hpp"
#include "InputHandler.hpp"

void Enemy::draw() { SDLSceneNode::draw(); }

void Enemy::update() {
  glm::vec2 vec = InputHandler::Get().getPadAxis(
      0, controller_axis::RIGHT_STICK);

  if (vec.x > DEADZONE || vec.x < -DEADZONE || vec.y > DEADZONE ||
      vec.y < -DEADZONE) {
    velocity = vec / static_cast<float>(5000);
  } else {
    velocity = {0, 0};
  }

  if (position.x < 0.0) {
    position.x = 0.0;
  }

  if (position.x > 580.0) {
    position.x = 580.0;
  }

  if (position.y < 0.0) {
    position.y = 0.0;
  }

  if (position.y > 400.0) {
    position.y = 400.0;
  }
  SDLSceneNode::update();
}

void Enemy::clean() {}
