#include "InputHandler.hpp"
#include "Gui.hpp"

Button::Button(const std::shared_ptr<LoaderParams> pParams, void (*callback)()) :
	SDLSceneNode(pParams), mCallback(callback), mReleased(false)
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
        if (TheInputHandler::getInstance()->getMouseButton(mouse_buttons::LEFT)
                && mReleased)
		{
			mCurrentFrame = CLICKED;
            mCallback();
            mReleased = false;
		}
        else if (!TheInputHandler::getInstance()->getMouseButton(mouse_buttons::LEFT))
        {
            mReleased = true;
            mCurrentFrame = MOUSE_OVER;
        }
	}
	else
	{
		mCurrentFrame = MOUSE_OUT;
	}
	SDLSceneNode::update();
}

void Button::clean()
{
	SDLSceneNode::clean();
}
