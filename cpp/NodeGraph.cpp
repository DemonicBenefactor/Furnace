#include "Game.hpp"
#include "NodeGraph.hpp"
#include "ResourceManager.hpp"

SDLSceneNode::SDLSceneNode(const LoaderParams *pParams) : 
	SceneNode(pParams), mPosition(pParams->getX(), pParams->getY())

{
    mW = pParams->getWidth();
    mH = pParams->getHeight();
    mID = pParams->getTextureID();

    mCurrentRow = 1;
    mCurrentFrame = 1;
}

void SDLSceneNode::draw()
{
    TheResourceManager::getInstance()->drawTextureFrame(mID, 
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
