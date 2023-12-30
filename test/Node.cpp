#include "Node.hpp"
#include <iostream>
#include <array>

using namespace std;

int main(int argc, char **argv) {
  array<double, 2> position = {3.333, -4.567};
  double &x = position[0];
  double &y = position[1];
  array<double, 2> &xy = position;


  cout << xy[0] << endl;

  return 0;
}
