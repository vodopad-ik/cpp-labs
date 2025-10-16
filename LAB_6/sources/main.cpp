#include "classA.hpp"
#include "classB.hpp"
#include "classC.hpp"
#include "utils.hpp"
#include "exceptions.hpp"
using namespace std;

int main() {
  setlocale(LC_ALL, "Rus");
  cout << "Примеры форматов: 2x^2 + 3x - 5 = 0, x^2 - 4x + 4 = 0, 1.5x^2 + 2.7x - 3.14 = 0\n";
  while (true) {
    try {
      C equation;
      equation.solve();
      equation.printSolve();
      break;
    } catch (const InvalidEquationException &e) {
      cout << "Ошибка в уравнении: " << e.what() << endl;
      cout << "Попробуйте снова.\n";
    } catch (const ZeroCoefficientException &e) {
      cout << "Математическая ошибка: " << e.what() << endl;
      cout << "Попробуйте снова.\n";
    } catch (const MathException &e) {
      cout << "Ошибка: " << e.what() << endl;
      cout << "Попробуйте снова.\n";
    } catch (const exception &e) {
      cout << "Неожиданная ошибка: " << e.what() << endl;
      cout << "Попробуйте снова.\n";
    }
  }
  return 0;
}