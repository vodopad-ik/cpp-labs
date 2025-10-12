#include "binaryFile.hpp"
#include <fstream>
#include <iostream>

BinaryFile::BinaryFile(const std::string &file_name)
    : file_name(file_name), current_position(0) {}
BinaryFile &BinaryFile::operator<<(const std::string &str) {
  std::ofstream file(file_name, std::ios::binary | std::ios::app);
  if (file.is_open()) {
    size_t size = str.size();
    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    file.write(str.c_str(), size);
  } else {
    std::cerr << "Ошибка открытия файла для записи: " << file_name << std::endl;
  }
  return *this;
}

BinaryFile &BinaryFile::operator>>(std::string &str) {
  std::ifstream file(file_name, std::ios::binary);
  if (file.is_open()) {
    if (current_position != 0)
      file.seekg(current_position);

    size_t size;
    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    if (file.good()) {
      str.resize(size);
      file.read(&str[0], size);
      current_position = file.tellg();
    }
  } else
    std::cerr << "Ошибка открытия файла для чтения: " << file_name << std::endl;
  return *this;
}

void BinaryFile::resetPosition() { current_position = 0; }
std::string BinaryFile::getFileName() const { return file_name; }
std::streampos BinaryFile::getCurrentPosition() const {
  return current_position;
}
bool BinaryFile::isEndOfFile() const {
  return current_position == std::streampos(-1);
}

// Проверка существования файла и его размера
bool BinaryFile::fileExistsAndNotEmpty() const {
  std::ifstream file(file_name, std::ios::binary | std::ios::ate);
  return file.is_open() && file.tellg() > 0;
}