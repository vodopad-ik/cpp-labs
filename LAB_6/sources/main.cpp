#include "classA.hpp"
#include "classB.hpp"
#include "classC.hpp"
#include "utils.hpp"

using namespace std;

int main() {
  setlocale(LC_ALL, "Russian");
  cout << "Примеры форматов: 2x^2 + 3x - 5 = 0, x^2 - 4x + 4 = 0\n";
  while (true) {
    try {
      C equation;
      equation.solve();
      equation.printSolve();
      break;
    } catch (const invalid_argument &e) {
      cout << " " << e.what() << endl;
      cout << "Попробуйте снова.\n";
    } catch (const exception &e) {
      cout << "Неожиданная ошибка: " << e.what() << endl;
      cout << "Попробуйте снова.\n";
    }
  }
  return 0;
}