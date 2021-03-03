#ifndef __Enemy__
#define __Enemy__

#include "NodeGraph.hpp"

class Enemy : public SDLSceneNode
{
public:

	Enemy(const std::shared_ptr<LoaderParams> params);

	virtual void draw();
	virtual void update();
	virtual void clean();	
};

#endif //__Enemy__
