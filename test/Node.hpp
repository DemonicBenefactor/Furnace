#ifndef __Node__
#define __Node__

#include <array>
#include <functional>
#include <memory>
#include <string>

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
  Node2D() : mX(0), mY(0), x(mX), y(mY), xy({mX, mY}), yx({mY, mX}) {}
  Node2D(double ix, double iy)
      : mX(ix), mY(iy), x(mX), y(mY), xy({mX, mY}), yx({mY, mX}) {}
  Node2D(const Node2D &m)
      : mX(m.x), mY(m.y), x(mX), y(mY), xy({mX, mY}), yx({mY, mX}) {}
  ~Node2D() {}

  Node2D &operator=(const Node2D &) { return *this; }

  virtual void update() {}

  double &x, &y;
  array<reference_wrapper<double>, 2> xy, yx;

private:
  double mX, mY;
};

/*-----------DERIVED CLASS----------*/

class Node3D : Node2D {
public:
  void update();

private:
};

#endif //__Node__
