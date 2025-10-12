#include "binaryFile.hpp"
#include <fstream>
#include <iostream>

BinaryFile::BinaryFile(const std::string &file_name)
    : file_name(file_name) {}
BinaryFile &BinaryFile::operator<<(const std::string &str) {
  // Используем init-statement в if
    if (std::ofstream file(file_name, std::ios::binary | std::ios::app); file.is_open()) {
        size_t size = str.size();
        // Безопасное приведение типов
        file.write(static_cast<const char*>(static_cast<const void*>(&size)), sizeof(size));
        file.write(str.c_str(), size);
    } else {
        std::cerr << "Ошибка открытия файла для записи: " << file_name << std::endl;
    }
  return *this;
}

BinaryFile &BinaryFile::operator>>(std::string &str) {
   // Используем init-statement в if
    if (std::ifstream file(file_name, std::ios::binary); file.is_open()) {
        if (current_position != 0) {
            file.seekg(current_position);
        }
        
        if (file.peek() == EOF) {
            current_position = std::streampos(-1);
            return *this;
        }
        
        size_t size;
        // Безопасное приведение типов
        file.read(static_cast<char*>(static_cast<void*>(&size)), sizeof(size));
        
        if (file.fail()) {
            current_position = std::streampos(-1);
            return *this;
        }
        
        str.resize(size);
        file.read(&str[0], size);
        
        if (file.fail()) {
            current_position = std::streampos(-1);
        } else {
            current_position = file.tellg();
        }
    } else {
        std::cerr << "Ошибка открытия файла для чтения: " << file_name << std::endl;
        current_position = std::streampos(-1);
    }
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