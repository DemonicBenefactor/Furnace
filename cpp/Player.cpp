#include "Player.hpp"
#include "InputHandler.hpp"

Player::Player(const LoaderParams *pParams) : 
	SDLSceneNode(pParams)
{

}

void Player::draw()
{
	SDLSceneNode::draw();
}

void Player::update()
{
    /*
    glm::vec2 vec = TheInputHandler::getInstance()->getPadAxis(0,controller_axis::LEFT_STICK) ;
    if (vec.x > DEADZONE || vec.x < -DEADZONE || vec.y > DEADZONE || vec.y < -DEADZONE)
    {        
        mVelocity = vec / static_cast<float>(5000);            
    }
    else {mVelocity = {0,0};}    
    if (mPosition.x < 0.0)
            {mPosition.x = 0.0;}        
    if (mPosition.x > 580.0)
            {mPosition.x = 580.0;}        
    if (mPosition.y < 0.0)
            {mPosition.y = 0.0;}        
    if (mPosition.y > 400.0)
            {mPosition.y = 400.0;}
    */

    glm::vec2 vec = TheInputHandler::getInstance()->getMousePosition();
    mVelocity = (vec - mPosition) / (float)100;
    SDLSceneNode::update();
}

void Player::clean()
{
}
