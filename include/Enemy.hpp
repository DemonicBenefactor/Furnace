#ifndef __Enemy__
#define __Enemy__

#include "NodeGraph.hpp"

class Enemy : public Node2D {
public:
  Enemy() {}

  virtual void load(const std::shared_ptr<LoaderParams> params) {
    Node2D::load(params);
  }
  virtual void draw();
  virtual void update();
  virtual void clean();
};

class EnemyCreator : public NodeCreator {
  nodePtr createSceneNode() const {
      //std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
      return std::make_shared<Enemy>();
  }
};

#endif //__Enemy__
