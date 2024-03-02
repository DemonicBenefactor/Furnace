#ifndef __NodeGraph__
#define __NodeGraph__

#include "SDL2/SDL.h"
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class LoaderParams {
public:
  LoaderParams(int X, int Y, int W, int H, std::string ID, int callbackID = 0,
               int frameNum = 0, int frameSpeed = 0)
      : x(X), y(Y), width(W), height(H), id(ID), frames(frameNum),
        speed(frameSpeed), callback(callbackID) {}

  // accessor functions
  int getX() const { return x; }
  int getY() const { return y; }
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  int getCallbackID() const { return callback; }
  std::string getTextureID() const { return id; }

private:
  int x;
  int y;
  int width;
  int height;
  std::string id;
  int frames;
  int speed;
  int callback;
};

class SceneNode {
public:
  virtual void load(const std::shared_ptr<LoaderParams> params) = 0;
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

protected:
  SceneNode() {}
  virtual ~SceneNode() {}
};

class SDLSceneNode : public SceneNode {
public:
  typedef std::unique_ptr<SDLSceneNode> Ptr;
  SDLSceneNode() {}
  virtual void load(const std::shared_ptr<LoaderParams> params);
  virtual void draw();
  virtual void update();
  virtual void clean();

  virtual void setRow(const int row) { currentRow = row; }
  virtual int getCallbackID() { return callbackID; }

protected:
  glm::vec2 position;
  glm::vec2 velocity;
  glm::vec2 acceleration;
  int width;
  int height;
  int currentRow;
  int currentFrame;
  int callbackID;
  std::string id;

private:
  std::vector<Ptr> children;
  SDLSceneNode *parent;
};

class NodeCreator {
public:
  typedef std::shared_ptr<SceneNode> nodePtr;
  virtual nodePtr createSceneNode() const = 0;
  virtual ~NodeCreator() {}
};

#endif //__NodeGraph__
