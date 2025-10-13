#pragma once
#include "binaryFile.hpp"
#include <string>
#include <string_view> // добавляем

class Car {
private:
  std::string license_plate;
  int year;
  std::string color;

public:
  Car();
  Car(const std::string &plate, int y, const std::string &c);
  bool isFilled() const;
  std::string getLicensePlate() const;
  int getYear() const;
  std::string getColor() const;
  void setLicensePlate(std::string_view plate);
  void setColor(std::string_view c);
  void setYear(int y);

  void display() const;

  // Перегрузка операторов для работы с BinaryFile
  friend BinaryFile &operator<<(BinaryFile &file, const Car &car);
  friend BinaryFile &operator>>(BinaryFile &file, Car &car);

  // Перегрузка для стандартных потоков
  friend std::ostream &operator<<(std::ostream &os, const Car &car);
  friend std::istream &operator>>(std::istream &is, Car &car);
};