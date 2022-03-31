#include "Gui.hpp"
#include "InputHandler.hpp"

// Button::Button(const std::shared_ptr<LoaderParams> pParams, void
// (*Callback)()) : 	SDLSceneNode(pParams), callback(Callback), released(false)
//{
//	currentFrame = MOUSE_OUT; // start at frame 0
//}

void Button::draw() { SDLSceneNode::draw(); }

void Button::update() {
  glm::vec2 pos = TheInputHandler::getInstance()->getMousePosition();

  if (pos.x < position.x + width && pos.x > position.x &&
      pos.y < position.y + height && pos.y > position.y) {
    if (TheInputHandler::getInstance()->getMouseButton(mouse_buttons::LEFT) &&
        released) {
      currentFrame = CLICKED;
      callback();
      released = false;
    } else if (!TheInputHandler::getInstance()->getMouseButton(
                   mouse_buttons::LEFT)) {
      released = true;
      currentFrame = MOUSE_OVER;
    }
  } else {
    currentFrame = MOUSE_OUT;
  }
  SDLSceneNode::update();
}

void Button::clean() { SDLSceneNode::clean(); }
