#ifndef __Enemy__
#define __Enemy__

#include "NodeGraph.hpp"
#include "NodeFactory.hpp"


class Enemy : public SDLSceneNode
{
public:

	Enemy() {}

	virtual void load(const std::shared_ptr<LoaderParams> params) { SDLSceneNode::load(params) }
    virtual void draw();
	virtual void update();
	virtual void clean();	
};

class EnemyCreator : public NodeCreator
{
    nodePtr createSceneNode() const { return std::make_shared<Enemy> } 
}

#endif //__Enemy__
