#include "Player.hpp"
#include "InputHandler.hpp"

void Player::draw() { SDLSceneNode::draw(); }

void Player::update() {
  /*
  glm::vec2 vec =
  TheInputHandler::getInstance()->getPadAxis(0,controller_axis::LEFT_STICK) ; if
  (vec.x > DEADZONE || vec.x < -DEADZONE || vec.y > DEADZONE || vec.y <
  -DEADZONE)
  {
      velocity = vec / static_cast<float>(5000);
  }
  else {velocity = {0,0};}
  if (position.x < 0.0)
          {position.x = 0.0;}
  if (position.x > 580.0)
          {position.x = 580.0;}
  if (position.y < 0.0)
          {position.y = 0.0;}
  if (position.y > 400.0)
          {position.y = 400.0;}
  */

  glm::vec2 vec = TheInputHandler::getInstance()->getMousePosition();
  velocity = (vec - position) / (float)100;
  SDLSceneNode::update();
}

void Player::clean() {}
