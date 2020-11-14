#include "Game.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"

SDLGameObject::SDLGameObject(const LoaderParams *pParams) : 
	GameObject(pParams), m_position(pParams->getX(), pParams->getY())

{
    m_w = pParams->getWidth();
    m_h = pParams->getHeight();
    m_id = pParams->getTextureID();

    m_currentRow = 1;
    m_currentFrame = 1;
}

void SDLGameObject::draw()
{
    TheTextureManager::getInstance()->draw(m_id, 
		    static_cast<int>(m_position.x), 
		    static_cast<int>(m_position.y),
		    m_w, m_h, 
		    TheGame::getInstance()->getRenderer());
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}
