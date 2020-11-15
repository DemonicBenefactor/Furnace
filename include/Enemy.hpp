#ifndef __Enemy__
#define __Enemy__

#include "NodeGraph.hpp"

class Enemy : public SDLSceneNode
{
public:

	Enemy(const LoaderParams *pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();	
};

#endif //__Enemy__
