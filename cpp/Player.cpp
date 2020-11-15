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
    */

    glm::vec2 vec = TheInputHandler::getInstance()->getMousePosition();
    m_velocity = (vec - m_position) / (float)100;
    SDLSceneNode::update();
}

void Player::clean()
{
}
