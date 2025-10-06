#include <iostream>
#include "classA.hpp"

A::A(double a_val) : a(a_val) {}
void A::setA(double val) { a = val; }
double A::getA() const { return a; }