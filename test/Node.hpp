#ifndef __Node__
#define __Node__

#include <array>
#include <memory>

using namespace std;

class Node {
public:
  Node() : X(0), Y(0), Z(0) {}
  Node(double ix, double iy, double iz) : X(ix), Y(iy), Z(iz) {}
  Node(const Node&) {}
  ~Node() {}

  Node& operator=(const Node&) {return *this;}

//  void x(double x) { X = x; }
//  void y(double y) { Y = y; }
//  void z(double z) { Z = z; }
//  void Set() {}

//  double x() { return X; }
//  double y() { return Y; }
//  double z() { return Z; }

unique_ptr<double> x;

private:
  double X, Y, Z;
};

#endif //__Node__
