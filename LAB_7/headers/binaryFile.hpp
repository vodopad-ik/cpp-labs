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
    if (std::ofstream file(file_name, std::ios::binary | std::ios::app);
        file.is_open()) {
      file.write(static_cast<const char *>(static_cast<const void *>(&data)),
                 sizeof(T));
    } else
      std::cerr << "Ошибка открытия файла для записи: " << file_name
                << std::endl;
    return *this;
  }

  template <typename T> BinaryFile &operator>>(T &data) {
    if (std::ifstream file(file_name, std::ios::binary); file.is_open()) {
      if (current_position != 0)
        file.seekg(current_position);
      if (file.peek() == EOF) {
        current_position = std::streampos(-1);
        return *this;
      }
      file.read(static_cast<char *>(static_cast<void *>(&data)), sizeof(T));

      if (file.fail())
        current_position = std::streampos(-1);
      else
        current_position = file.tellg();
    } else {
      std::cerr << "Ошибка открытия файла для чтения: " << file_name
                << std::endl;
      current_position = std::streampos(-1);
    }
    return *this;
  }

  BinaryFile &operator<<(const std::string &str);
  BinaryFile &operator>>(std::string &str);
  void resetPosition();
  std::string getFileName() const;
  std::streampos getCurrentPosition() const;
  bool isEndOfFile() const;
  bool fileExistsAndNotEmpty() const;
};