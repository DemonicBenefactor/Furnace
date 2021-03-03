#ifndef __GameObject__
#define __GameObject__

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <glm/glm.hpp>
#include "SDL2/SDL.h"

class LoaderParams
{
public:
    LoaderParams(int X, int Y, 
            int w, int h, std::string ID) :
       x(X), y(Y), width(w), height(h), id(ID) {}
    
    //accessor functions
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::string getTextureID() const { return id; }
private:
    int x;
    int y;
    int width;
    int height;
    std::string id;
};

class SceneNode
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
protected:    
    SceneNode(const std::shared_ptr<LoaderParams> params) {}
    virtual ~SceneNode() {}
};

class SDLSceneNode : public SceneNode
{
public:
    typedef std::unique_ptr<SDLSceneNode> Ptr;
    SDLSceneNode(const std::shared_ptr<LoaderParams> params);
    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void setRow(const int row) { currentRow = row; }
protected:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    int width;
    int height;
    int currentRow;
    int currentFrame;
    std::string id;
private:
    std::vector<Ptr> children;
    SDLSceneNode* parent;
};

#endif //__GameObject__
