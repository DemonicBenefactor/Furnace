#ifndef __Gui__
#define __Gui__

#include "NodeGraph.hpp"

class Button : public SDLSceneNode
{
public:
	Button(const LoaderParams* pParams, void (*callback)());

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

    void (*mCallback)();
    bool mReleased;
};

#endif //__Gui__
