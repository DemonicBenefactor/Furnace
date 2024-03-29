#ifndef __Player__
#define __Player__

#include "NodeGraph.hpp"

class Player : public Node2D {
public:
  Player() {}

  virtual void load(const std::shared_ptr<LoaderParams> params) {
    Node2D::load(params);
  }
  virtual void draw();
  virtual void update();
  virtual void clean();
};

class PlayerCreator : public NodeCreator {
  nodePtr createSceneNode() const { return std::make_shared<Player>(); }
};

#endif //__Player__
