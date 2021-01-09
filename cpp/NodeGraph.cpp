#include "Game.hpp"
#include "NodeGraph.hpp"
#include "ResourceManager.hpp"

SDLSceneNode::SDLSceneNode(const std::shared_ptr<LoaderParams> pParams) :
    SceneNode(pParams), mPosition(pParams->getX(), pParams->getY()),
    mVelocity(0), mAcceleration(0), mCurrentRow(1), mCurrentFrame(0)
{
    mW = pParams->getWidth();
    mH = pParams->getHeight();
    mID = pParams->getTextureID();
}

void SDLSceneNode::draw()
{
    TheResourceManager::getInstance()->drawTexture(mID, 
		    static_cast<int>(mPosition.x), 
		    static_cast<int>(mPosition.y),            
		    mW, mH, mCurrentRow, mCurrentFrame,
		    TheGame::getInstance()->getRenderer());
}

void SDLSceneNode::update()
{
    mVelocity += mAcceleration;
    mPosition += mVelocity;
}

void SDLSceneNode::clean()
{
    TheResourceManager::getInstance()->clearTexture(mID);
}
