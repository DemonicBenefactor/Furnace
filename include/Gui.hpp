#ifndef __Gui__
#define __Gui__

#include "NodeGraph.hpp"

class Button : public SDLSceneNode
{
public:
	Button(const std::shared_ptr<LoaderParams> params, void (*Callback)());

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

    void (*callback)();
    bool released;
};

#endif //__Gui__
