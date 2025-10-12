#pragma once
#include <fstream>
#include <iostream>
#include <string>

class BinaryFile {
private:
  std::string file_name;
  std::streampos current_position;

public:
  BinaryFile(const std::string &file_name);

  // Перегрузка оператора << для записи любых данных
  template <typename T> BinaryFile &operator<<(const T &data) {
    std::ofstream file(file_name, std::ios::binary | std::ios::app);
    if (file.is_open()) {
      file.write(reinterpret_cast<const char *>(&data), sizeof(T));
    } else {
      std::cerr << "Ошибка открытия файла для записи: " << file_name
                << std::endl;
    }
    return *this;
  }

  // Перегрузка оператора >> для чтения любых данных
  template <typename T> BinaryFile &operator>>(T &data) {
    std::ifstream file(file_name, std::ios::binary);
    if (file.is_open()) {
      if (current_position != 0) {
        file.seekg(current_position);
      }

      // Проверяем, есть ли еще данные для чтения
      if (file.peek() == EOF) {
        current_position = std::streampos(-1);
        return *this;
      }

      file.read(reinterpret_cast<char *>(&data), sizeof(T));

      // Если чтение не удалось, устанавливаем позицию в -1
      if (file.fail()) {
        current_position = std::streampos(-1);
      } else {
        current_position = file.tellg();
      }
    } else {
      std::cerr << "Ошибка открытия файла для чтения: " << file_name
                << std::endl;
      current_position = std::streampos(-1);
    }
    return *this;
  }

  // Специализация для строк
  BinaryFile &operator<<(const std::string &str);

  BinaryFile &operator>>(std::string &str);

  // Сброс позиции
  void resetPosition();

  // Получение имени файла
  std::string getFileName() const;

  // Получение текущей позиции
  std::streampos getCurrentPosition() const;

  // Проверка конца файла
  bool isEndOfFile() const;

  // Проверка существования файла и его размера
  bool fileExistsAndNotEmpty() const;
};