#ifndef __Enemy__
#define __Enemy__

#include "GameObject.hpp"

class Enemy : public SDLGameObject
{
public:

	Enemy(const LoaderParams *pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();	
};

#endif //__Enemy__
