#include "Gui.hpp"
#include "InputHandler.hpp"

// Button::Button(const std::shared_ptr<LoaderParams> pParams, void
// (*Callback)()) : 	Node2D(pParams), callback(Callback), released(false)
//{
//	currentFrame = MOUSE_OUT; // start at frame 0
//}

void Button::draw() { Node2D::draw(); }

void Button::update() {
  glm::vec2 pos = InputHandler::Get().getMousePosition();

  if (pos.x < position.x + width && pos.x > position.x &&
      pos.y < position.y + height && pos.y > position.y) {
    if (InputHandler::Get().getMouseButton(mouse_buttons::LEFT) &&
        released) {
      currentFrame = CLICKED;
      callback();
      released = false;
    } else if (!InputHandler::Get().getMouseButton(
                   mouse_buttons::LEFT)) {
      released = true;
      currentFrame = MOUSE_OVER;
    }
  } else {
    currentFrame = MOUSE_OUT;
  }
  Node2D::update();
}

void Button::clean() { Node2D::clean(); }
