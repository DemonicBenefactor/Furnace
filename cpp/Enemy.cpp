#include "InputHandler.hpp"
#include "Enemy.hpp"

Enemy::Enemy(const LoaderParams *pParams) : 
	SDLGameObject(pParams)
{

}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
    glm::vec2 vec = TheInputHandler::getInstance()->getPadAxis(0,controller_axis::RIGHT_STICK) ;
    if (vec.x > DEADZONE || vec.x < -DEADZONE || vec.y > DEADZONE || vec.y < -DEADZONE)
    {
        
        
        m_velocity = vec / static_cast<float>(5000);
            
    }
    else {m_velocity = {0,0};}
    
    if (m_position.x < 0.0)
            {m_position.x = 0.0;}
        
    if (m_position.x > 580.0)
            {m_position.x = 580.0;}
        
    if (m_position.y < 0.0)
            {m_position.y = 0.0;}
        
    if (m_position.y > 400.0)
            {m_position.y = 400.0;}
    SDLGameObject::update();
}

void Enemy::clean()
{
}