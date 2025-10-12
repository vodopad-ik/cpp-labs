#pragma once
#include <fstream>
#include <iostream>
#include <string>

class BinaryFile {
private:
  std::string file_name;
  std::streampos current_position = 0;

public:
  explicit BinaryFile(const std::string &file_name);

  template <typename T> BinaryFile &operator<<(const T &data) {
    // Используем init-statement в if
    if (std::ofstream file(file_name, std::ios::binary | std::ios::app);
        file.is_open()) {
      // Безопасное приведение типов
      file.write(static_cast<const char *>(static_cast<const void *>(&data)),
                 sizeof(T));
    } else {
      std::cerr << "Ошибка открытия файла для записи: " << file_name
                << std::endl;
    }
    return *this;
  }

  // Перегрузка оператора >> для чтения любых данных
  template <typename T> BinaryFile &operator>>(T &data) {
    // Используем init-statement в if
    if (std::ifstream file(file_name, std::ios::binary); file.is_open()) {
      if (current_position != 0) {
        file.seekg(current_position);
      }

      if (file.peek() == EOF) {
        current_position = std::streampos(-1);
        return *this;
      }

      // Безопасное приведение типов
      file.read(static_cast<char *>(static_cast<void *>(&data)), sizeof(T));

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