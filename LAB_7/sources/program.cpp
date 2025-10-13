#include "program.hpp"
#include "carValidNumber.hpp"
#include "utils.hpp"

int Program::getValidChoice(int min, int max) const {
  return Utils::inputIntInRange(
      "", min, max, "Выберите один из вариантов, представленных в меню!!!\n> ");
}

bool Program::run(int choice) const {
  CarManager manager("cars.dat");
  switch (choice) {
  case 0:
    return false;
  case 1: {
    std::string plate = CarNumber::inputLicensePlate("Введите номер машины: ");
    std::cout << "Введите год выпуска: ";
    int year = Utils::inputIntInRange(
        "", 1900, 2025,
        "Внимание! Год должен быть в интервале от 1900 до 2025 года.");
    std::string color = Utils::inputOnlyLetters("Введите оттенок кузова: ");

    if (Car newCar(plate, year, color); manager.addCar(newCar)) {
      std::cout << "Машина успешно добавлена!" << std::endl;
      newCar.display();
    } else
      std::cout << "Ошибка: не удалось добавить машину!" << std::endl;
    break;
  }
  case 2: {
    std::cout << "\nВсе машины в файле:" << std::endl;
    manager.reset();
    Car car;
    int count = 0;

    while (manager.readNextCar(car)) {
      // Извлекаем инкремент из выражения
      count++;
      std::cout << count << ". ";
      car.display();
    }

    if (count == 0)
      std::cout << "Файл пуст или не существует!" << std::endl;
    break;
  }
  case 3: {
    int year = Utils::inputIntInRange("Введите год выпуска для поиска: ", 1900,
                                      2025, "Год должен быть от 1900 до 2025.");
    int count = manager.countCarsByYear(year);
    std::cout << "Количество машин " << year << " года выпуска: " << count
              << std::endl;
    break;
  }
  default:
    std::cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
  }
  return true;
}