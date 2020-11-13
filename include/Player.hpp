#ifndef __Player__
#define __Player__

#include "GameObject.hpp"

class Player : public SDLGameObject
{
public:

	Player(const LoaderParams *pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();	
};

#endif //__Player__
