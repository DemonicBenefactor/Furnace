#include "InputHandler.hpp"
#include "Enemy.hpp"

Enemy::Enemy(const LoaderParams *pParams) : 
	SDLSceneNode(pParams)
{

}

void Enemy::draw()
{
	SDLSceneNode::draw();
}

void Enemy::update()
{
    glm::vec2 vec = TheInputHandler::getInstance()->getPadAxis(0,controller_axis::RIGHT_STICK) ;
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
    SDLSceneNode::update();
}

void Enemy::clean()
{
}
