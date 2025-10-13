#include "car.hpp"
#include <iostream>

Car::Car(const std::string &plate, int y, const std::string &c)
    : license_plate(plate), year(y), color(c) {}
bool Car::isFilled() const {
  return (!license_plate.empty() && !color.empty() && year) ? true : false;
}
std::string Car::getLicensePlate() const { return license_plate; }
int Car::getYear() const { return year; }
std::string Car::getColor() const { return color; }

void Car::setLicensePlate(std::string_view plate) { license_plate = plate; }
void Car::setColor(std::string_view c) { color = c; }
void Car::setYear(int y) { year = y; }

void Car::display() const {
  std::cout << "Номер: " << license_plate << ", Год: " << year
            << ", Цвет: " << color << std::endl;
}

// **** РЕАЛИЗАЦИИ ОПЕРАТОРОВ БЫЛИ УДАЛЕНЫ ИЗ ЭТОГО ФАЙЛА ****
// **** И ПЕРЕМЕЩЕНЫ В car.hpp В КАЧЕСТВЕ СКРЫТЫХ ДРУЗЕЙ ****