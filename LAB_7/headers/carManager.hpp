#pragma once
#include "binaryFile.hpp"
#include "car.hpp"

class CarManager {
private:
  BinaryFile file;

public:
  explicit CarManager(const std::string &filename);
  // Добавление машины в файл (используем перегруженный оператор)
  bool addCar(const Car &car);
  // Чтение следующей машины из файла (используем перегруженный оператор)
  bool readNextCar(Car &car);
  // Подсчет машин указанного года выпуска
  int countCarsByYear(int targetYear);
  // Сброс позиции чтения
  void reset();
  // Получение имени файла
  std::string getFileName() const;
  // Получение ссылки на файл для прямого доступа
  BinaryFile &getFile();
};