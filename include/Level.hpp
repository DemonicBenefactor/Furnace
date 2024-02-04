#ifndef __Level__
#define __Level__

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct Tileset {
  int firstGridID;
  int tileWidth;
  int tileHeight;
  int spacing;
  int margin;
  int width;
  int height;
  int numColums;
  string name;
};

class Layer {
public:
  virtual void update() = 0;
  virtual void render() = 0;
private:
  virtual ~Layer() {}
};

class Level {
public:

  Level();
  ~Level() {}

  void update();
  void render();

//  shared_ptr<vector<Tileset>> getTilesets() { return tilesets; }
//  shared_ptr<vector<unique_ptr<Layer>>> getLayers() { return layers; }

private:
//  shared_ptr<vector<Tileset>> tilesets;
//  shared_ptr<vector<unique_ptr<Layer>>> layers;
};

#endif // __Level__
