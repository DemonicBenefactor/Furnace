#ifndef __GameObject__
#define __GameObject__

#include <iostream>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "SDL2/SDL.h"

class LoaderParams
{
public:
    LoaderParams(int x, int y, 
            int w, int h, std::string id) :
       mX(x), mY(y), mW(w), mH(h), mID(id) {}
    
    //accessor functions
    int getX() const { return mX; }
    int getY() const { return mY; }
    int getWidth() const { return mW; }
    int getHeight() const { return mH; }
    std::string getTextureID() const { return mID; }
private:
    int mX;
    int mY;
    int mW;
    int mH;
    std::string mID;
};

class SceneNode
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
protected:    
    SceneNode(const LoaderParams *pParams) {}
    virtual ~SceneNode() {}
};

class SDLSceneNode : public SceneNode
{
public:
    typedef std::unique_ptr<SDLSceneNode> Ptr;
    SDLSceneNode(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void setRow(const int row) { mCurrentRow = row; }
protected:
    glm::vec2 mPosition;
    glm::vec2 mVelocity;
    glm::vec2 mAcceleration;
    int mW;
    int mH;
    int mCurrentRow;
    int mCurrentFrame;
    std::string mID;
private:
    std::vector<Ptr> mChildren;
    SDLSceneNode* mParent;
};

#endif //__GameObject__
