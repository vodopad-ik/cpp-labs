#include "program.hpp"
#include "utils.hpp"

int main() {
  setlocale(LC_ALL, "Russian");
  int choice = 0;
  Program program;
  std::cout << "Выберите опцию из представленных ниже: \n";
  printMenu();
  while ((choice = Utils::inputInt()) != 0 && program.run(choice)) {
    std::cout << "\nВыберите опцию из представленных ниже: \n";
    printMenu();
  }
  return 0;
}
