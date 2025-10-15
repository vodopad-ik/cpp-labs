#pragma once
#include "binaryFile.hpp"
#include "car.hpp"

class CarManager {
private:
  BinaryFile file;

public:
  explicit CarManager(const std::string &filename);
  bool addCar(const Car &car);
  bool readNextCar(Car &car);
  int countCarsByYear(int targetYear);
  void reset();
  std::string getFileName() const;
  BinaryFile &getFile();
};