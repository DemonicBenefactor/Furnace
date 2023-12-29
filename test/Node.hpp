#ifndef __Node__
#define __Node__

#include <string>
#include <memory>

using namespace std;

/*------------BASE CLASS-----------*/

class Node {
public:
  virtual void update() = 0;

protected:
  virtual ~Node() {}
};

/*-----------DERIVED CLASS----------*/

class Node2D : Node {
public:
  Node2D() : x(0), y(0) {}
  Node2D(double ix, double iy) : x(ix), y(iy) {}
  Node2D(const Node2D &) {}
  ~Node2D() {}

  Node2D &operator=(const Node2D &) { return *this; }

  virtual void update() {}

  double x, y;

private:
};

/*-----------DERIVED CLASS----------*/

class Node3D : Node2D {
public:
  void update();

private:
};

#endif //__Node__
