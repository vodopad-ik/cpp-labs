#include "carManager.hpp"

CarManager::CarManager(const std::string &filename) : file(filename) {}

bool CarManager::addCar(const Car &car) {
    if (car.isFilled()) {
        file << car;
        return true;
    }
    return false;
}

bool CarManager::readNextCar(Car &car) {
    // Проверяем, не достигли ли конца файла
    if (file.isEndOfFile()) {
        return false;
    }
    
    file >> car;
    
    // Проверяем, удалось ли прочитать корректные данные
    return !file.isEndOfFile() && car.isFilled();
}

int CarManager::countCarsByYear(int year) {
    file.resetPosition();
    int count = 0;
    
    // Читаем все машины и считаем подходящие
    while (true) {
        Car temp;
        if (!readNextCar(temp)) {
            break;
        }
        
        if (temp.getYear() == year) {
            count++;
        }
    }
    
    file.resetPosition();
    return count;
}

void CarManager::reset() { 
    file.resetPosition(); 
}

std::string CarManager::getFileName() const { 
    return file.getFileName(); 
}

BinaryFile &CarManager::getFile() { 
    return file; 
}