#ifndef __Gui__
#define __Gui__

#include "NodeFactory.hpp"
#include "NodeGraph.hpp"

class Button : public SDLSceneNode {
public:
  // Button(const std::shared_ptr<LoaderParams> params, void (*Callback)());
  Button() : /*currentFrame(MOUSE_OUT),*/ released(false) {}

  virtual void load(const std::shared_ptr<LoaderParams> params) {
    SDLSceneNode::load(params);
  }
  virtual void draw();
  virtual void update();
  virtual void clean();

  void setCallback( void (*Callback)()) { callback = Callback; }  

private:
  enum button_state { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 };

  void (*callback)();
  bool released;
};

class ButtonCreator : public NodeCreator {
  nodePtr createSceneNode() const { return std::make_shared<Button>(); }
};

#endif //__Gui__
