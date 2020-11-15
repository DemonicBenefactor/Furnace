#ifndef __Player__
#define __Player__

#include "NodeGraph.hpp"

class Player : public SDLSceneNode
{
public:

	Player(const LoaderParams *pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();	
};

#endif //__Player__
