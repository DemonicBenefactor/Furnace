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
  strinng name;
};

Class Layer {
Public:
  virtual void update() = 0;
  virtual void render() = 0;
Private:
  virtual ~Layer() {}
};

Class Level {
Public:

  Level();
  ~Level() {}

  void update();
  void render();

  shared_ptr<vector<Tileset>> getTilesets() { return tilesets; }
  shared_ptr<vector<unique_ptr<Layer>>> getLayers() { return layers; }

Private:
  shared_ptr<vector<Tileset>> tilesets;
  shared_ptr<vector<unique_ptr<Layer>>> layers;
};

#endif // __Level__
