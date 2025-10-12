#pragma once
#include "binaryFile.hpp"
#include <iostream>
#include <string>

class Car {
private:
  std::string license_plate;
  int year;
  std::string color;

public:
  Car();
  Car(const std::string &plate, int y, const std::string &c);
  bool isFilled()const ;
  std::string getLicensePlate() const;
  int getYear() const;
  std::string getColor() const;
  void setLicensePlate(const std::string &plate);
  void setYear(int y);
  void setColor(const std::string &c);

  void display() const;

  // Перегрузка операторов для работы с BinaryFile
  friend BinaryFile &operator<<(BinaryFile &file, const Car &car);
  friend BinaryFile &operator>>(BinaryFile &file, Car &car);

  // Перегрузка для стандартных потоков
  friend std::ostream &operator<<(std::ostream &os, const Car &car);
  friend std::istream &operator>>(std::istream &is, Car &car);
};