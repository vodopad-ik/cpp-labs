#include <iostream>
#include "classA.hpp"
#include "classB.hpp"
using namespace std;

B::B(double a_val, double b_val) : A(a_val), b(b_val) {}
void B::setB(double val) { b = val; }
double B::getB() const { return b; }