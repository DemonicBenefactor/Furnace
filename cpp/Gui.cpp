#include "InputHandler.hpp"
#include "Gui.hpp"

Button::Button(const LoaderParams *pParams) :
	SDLSceneNode(pParams)
{
	mCurrentFrame = MOUSE_OUT; // start at frame 0
}

void Button::draw()
{
	SDLSceneNode::draw();
}

void Button::update()
{
	glm::vec2 pos = TheInputHandler::getInstance()
		->getMousePosition();

	if (pos.x < mPosition.x + mW
		&& pos.x > mPosition.x
		&& pos.y < mPosition.y + mH
		&& pos.y > mPosition.y)
	{
		mCurrentFrame = MOUSE_OVER;
		if (TheInputHandler::getInstance()->getMouseButton(mouse_buttons::LEFT))
		{
			mCurrentFrame = CLICKED;
		}
	}
	else
	{
		mCurrentFrame = MOUSE_OUT;
	}
}

void Button::clean()
{
	SDLSceneNode::clean();
}