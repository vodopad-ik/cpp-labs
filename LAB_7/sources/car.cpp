#include "car.hpp"
#include <iostream>

Car::Car() : license_plate(""), year(0), color("") {}

Car::Car(const std::string &plate, int y, const std::string &c)
    : license_plate(plate), year(y), color(c) {}

bool Car::isFilled() const {
  return (!license_plate.empty() && !color.empty() && year);
}

std::string Car::getLicensePlate() const { return license_plate; }
int Car::getYear() const { return year; }
std::string Car::getColor() const { return color; }

void Car::setLicensePlate(std::string_view plate) { 
    license_plate = plate; 
}

void Car::setColor(std::string_view c) { 
    color = c; 
}

void Car::setYear(int y) { year = y; }

void Car::display() const {
  std::cout << "Номер: " << license_plate << ", Год: " << year
            << ", Цвет: " << color << std::endl;
}

// Перегрузка для BinaryFile - запись
BinaryFile &operator<<(BinaryFile &file, const Car &car) {
  file << car.license_plate;
  file << car.year;
  file << car.color;
  return file;
}

// Перегрузка для BinaryFile - чтение
BinaryFile &operator>>(BinaryFile &file, Car &car) {
    std::string plate;
    std::string color;
    int year;

    file >> plate;
    file >> year;
    file >> color;

    car.setLicensePlate(plate);
    car.setYear(year);
    car.setColor(color);

    return file;
}

// Перегрузка для стандартных потоков
std::ostream &operator<<(std::ostream &os, const Car &car) {
  os << "Номер: " << car.license_plate << ", Год: " << car.year
     << ", Цвет: " << car.color;
  return os;
}

std::istream &operator>>(std::istream &is, Car &car) {
  std::cout << "Введите номер машины: ";
  is >> car.license_plate;
  std::cout << "Введите год выпуска: ";
  is >> car.year;
  std::cout << "Введите цвет: ";
  is >> car.color;
  return is;
}