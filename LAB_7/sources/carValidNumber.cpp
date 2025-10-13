#include "carValidNumber.hpp"
#include <algorithm>
#include <iostream>
#include <string_view> // Включаем для использования std::string_view

const std::string CarNumber::validLetters = "ABEIKMNOPCTX";
const std::string CarNumber::validDigits = "0123456789";

// =========================================================
// Вспомогательные функции (аналог contains)
// =========================================================

bool CarNumber::isValidDigit(char c) { 
    // Эквивалент validDigits.contains(c) для C++17
    return validDigits.find(c) != std::string::npos; 
}

bool CarNumber::isValidLetter(char c) {
    char upperC = std::toupper(c);
    // Эквивалент validLetters.contains(upperC) для C++17
    return validLetters.find(upperC) != std::string::npos;
}

void CarNumber::displayTemplate() {
    std::cout << "Формат: 1234AB или 1234AB1" << std::endl;
    std::cout << "Допустимые буквы: A B E I K M N O P C T X" << std::endl;
}

// =========================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ РЕФАКТОРИНГА
// =========================================================

// Заменено const std::string& на std::string_view
bool CarNumber::checkLength(std::string_view formatted) {
    if (formatted.length() < 6 || formatted.length() > 7) {
        std::cout << "Ошибка: номер должен содержать 6 или 7 символов!" << std::endl;
        return false;
    }
    return true;
}

bool CarNumber::checkFirstFourDigits(std::string_view formatted) {
    for (int i = 0; i < 4; i++) {
        if (!CarNumber::isValidDigit(formatted[i])) {
            std::cout << "Ошибка: первые 4 символа должны быть цифрами!" << std::endl;
            return false;
        }
    }
    return true;
}

// Удален аргумент const std::string &validLetters, чтобы избежать затенения.
// Используется CarNumber::validLetters.
bool CarNumber::checkLetters(std::string_view formatted) {
    for (int i = 4; i < 6; i++) {
        if (!CarNumber::isValidLetter(formatted[i])) {
            // Используем статическое поле класса
            std::cout << "Ошибка: символы 5-6 должны быть буквами из списка: " 
                      << CarNumber::validLetters << std::endl;
            return false;
        }
    }
    return true;
}

bool CarNumber::checkRegionCode(std::string_view formatted) {
    // Объединяем проверку длины и валидности символа
    if (formatted.length() == 7 && 
        (!CarNumber::isValidDigit(formatted[6]) || formatted[6] == '0')) {
        std::cout << "Ошибка: код региона должен быть цифрой от 1 до 9!" << std::endl;
        return false;
    }
    return true;
}

// =========================================================
// РЕФАКТОРИНГ: ОСНОВНАЯ ФУНКЦИЯ inputLicensePlate
// =========================================================

std::string CarNumber::inputLicensePlate(const std::string &message) {
    std::string plate;
    bool valid = false;

    while (!valid) {
        std::cout << message;
        displayTemplate();
        std::getline(std::cin, plate);

        // 1. Форматирование
        std::string formatted;
        for (char c : plate) {
            if (c != ' ' && c != '-')
                formatted += std::toupper(c);
        }
        
        // 2. Валидация (используем std::string_view для передачи)
        if (!checkLength(formatted)) continue;
        if (!checkFirstFourDigits(formatted)) continue;
        // Передаем только formatted
        if (!checkLetters(formatted)) continue; 
        if (!checkRegionCode(formatted)) continue;

        // Если все проверки пройдены, выходим из цикла
        valid = true;
        plate = formatted; 
    }
    
    // 3. Форматирование вывода с пробелом
    std::string result;
    for (int i = 0; i < plate.length(); i++) {
        result += plate[i];
        if (i == 3) result += " ";
    }
    
    std::cout << "Принят номер: " << result << std::endl;
    return plate;
}