#pragma once
#include "binaryFile.hpp"
#include <iostream> 
#include <string>
#include <string_view>

class Car {
private:
  std::string license_plate = "";
  int year = 0;
  std::string color = "";

public:
  Car() = default;
  Car(const std::string &plate, int y, const std::string &c);
  bool isFilled() const;
  std::string getLicensePlate() const;
  int getYear() const;
  std::string getColor() const;
  void setLicensePlate(std::string_view plate);
  void setColor(std::string_view c);
  void setYear(int y);

  void display() const;

  friend BinaryFile &operator<<(BinaryFile &file, const Car &car) {
    file << car.license_plate;
    file << car.year;
    file << car.color;
    return file;
  }

  // car.hpp (Скрытая дружественная функция с прямым доступом)

friend BinaryFile &operator>>(BinaryFile &file, Car &car) {
    file >> car.license_plate;
    file >> car.year;
    file >> car.color;

    return file;
}
  friend std::ostream &operator<<(std::ostream &os, const Car &car) {
    os << "Номер: " << car.license_plate << ", Год: " << car.year
       << ", Цвет: " << car.color;
    return os;
  }

  friend std::istream &operator>>(std::istream &is, Car &car) {
    std::cout << "Введите номер машины: ";
    is >> car.license_plate;
    std::cout << "Введите год выпуска: ";
    is >> car.year;
    std::cout << "Введите цвет: ";
    is >> car.color;
    return is;
  }
};