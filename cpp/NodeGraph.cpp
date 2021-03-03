#include "Game.hpp"
#include "NodeGraph.hpp"
#include "ResourceManager.hpp"

SDLSceneNode::SDLSceneNode(const std::shared_ptr<LoaderParams> params) :
    SceneNode(params), position(params->getX(), params->getY()),
    velocity(0), acceleration(0), currentRow(1), currentFrame(0)
{
    width = params->getWidth();
    height = params->getHeight();
    id = params->getTextureID();
}

void SDLSceneNode::draw()
{
    TheResourceManager::getInstance()->drawTexture(id, 
		    static_cast<int>(position.x), 
		    static_cast<int>(position.y),            
		    width, height, currentRow, currentFrame,
		    TheGame::getInstance()->getRenderer());
}

void SDLSceneNode::update()
{
    velocity += acceleration;
    position += velocity;
}

void SDLSceneNode::clean()
{
    TheResourceManager::getInstance()->clearTexture(id);
}
