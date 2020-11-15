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
       m_x(x), m_y(y), m_w(w), m_h(h), m_id(id) {}
    
    //accessor functions
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_w; }
    int getHeight() const { return m_h; }
    std::string getTextureID() const { return m_id; }
private:
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    std::string m_id;
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
    virtual void clean() {}
protected:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    glm::vec2 m_acceleration;
    int m_w;
    int m_h;
    int m_currentRow;
    int m_currentFrame;
    std::string m_id;
private:
    std::vector<Ptr> mChildren;
    SDLSceneNode* mParent;
};

#endif //__GameObject__
