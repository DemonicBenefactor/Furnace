#include "Node.hpp"
#include <iostream>
#include <array>
#include <functional>

using namespace std;

int main(int argc, char **argv) {

    Node2D n1;
    Node2D n2(69, -7.7);
    Node2D n3(n2);

    n1.xy = n2.yx;

  cout << n3.xy[0] << endl;

  return 0;
}
