#include "Game.hpp"
#include "NodeGraph.hpp"
#include "ResourceManager.hpp"

SDLSceneNode::SDLSceneNode(const LoaderParams *pParams) : 
	SceneNode(pParams), m_position(pParams->getX(), pParams->getY())

{
    m_w = pParams->getWidth();
    m_h = pParams->getHeight();
    m_id = pParams->getTextureID();

    m_currentRow = 1;
    m_currentFrame = 1;
}

void SDLSceneNode::draw()
{
    TheResourceManager::getInstance()->drawTexture(m_id, 
		    static_cast<int>(m_position.x), 
		    static_cast<int>(m_position.y),
		    m_w, m_h, 
		    TheGame::getInstance()->getRenderer());
}

void SDLSceneNode::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}
