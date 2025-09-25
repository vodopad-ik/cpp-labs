#include "classA.hpp"
#include "classB.hpp"
#include "classC.hpp"
#include "utils.hpp"
#include <cmath>
#include <iostream>
#include <locale>
using namespace std;

int main() {
  setlocale(LC_ALL, "Russian");
  cout << "Введите коэффициенты a, b, c: \n";
  double a = input("Введите коэффициент a: ");
  double b = input("Введите коэффициент b: ");
  double c = input("Введите коэффициент c: ");
  C equation(a, b, c);
  equation.solve();
  return 0;
}