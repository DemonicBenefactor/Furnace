#ifndef __Node__
#define __Node__

#include <array>

using namespace std;

class Node {
public:
  Node() : X(0), Y(0), Z(0) {}
  Node(double x, double y, double z ) : X(x), Y(y), Z(z) {}
  Node(&Node) {}
  

  ~Omni() {}

  x(double x) { X = x; }
  y(double y) { Y = y; }
  z(double z) { Z = z; }
  Set() {}

  x() { return X; }
  y() { return Y; }
  z() { return Z; }

private:
  double X, Y, Z;
};

#endif //__Node__
