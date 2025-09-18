# Лабораторные работы по C++

## Вариант 6

[![SonarCloud](https://sonarcloud.io/images/project_badges/sonarcloud-white.svg)](https://sonarcloud.io/project/overview?id=vodopad-ik_cpp-labs)

## Статус анализа кода
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=vodopad-ik_cpp-labs&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=vodopad-ik_cpp-labs)
[![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=vodopad-ik_cpp-labs&metric=ncloc)](https://sonarcloud.io/summary/new_code?id=vodopad-ik_cpp-labs)
<details>
<summary style="cursor: pointer; font-weight: bold;">📁 LAB_1 - Работа с матрицами</summary>

### Задание:
Создать класс матрица. Память под матрицу выделять динамически. Определить конструктор без параметров, конструктор с параметрами. Реализовать методы: ввод данных в матрицу, вывод матрицы на экран, методы вычитания матриц. Проверить работу методов этого класса.

### Требования:
- Динамическое выделение памяти под матрицу
- Конструктор по умолчанию
- Конструктор с параметрами (размеры матрицы)
- Метод ввода данных
- Метод вывода матрицы
- Метод вычитания матриц
- Тестирование всех методов

</details>

<details>
<summary style="cursor: pointer; font-weight: bold;">📁 LAB_2 - Работа с массивами</summary>

### Задание:
Создать класс для работы с одномерными массивами: перегрузить оператор | для объединения массивов. Память под массивы отводить динамически. Предоставить конструктор копирования. Определить friend функции для операций ввода-вывода в поток.

### Требования:
- Динамическое выделение памяти под массивы
- Перегрузка оператора | для объединения массивов
- Конструктор копирования
- Friend-функции для ввода/вывода
- Операции ввода-вывода через перегруженные операторы

</details>

## Структура репозитория
```📦 cpp-labs/
├── 📁 LAB_1/ # Лабораторная работа 1 - Матрицы
│ ├── 📄 main.cpp
│ ├── 📄 matrix.hpp
│ ├── 📄 matrix.cpp
│ ├── 📄 menu.hpp
│ ├── 📄 menu.cpp
│ ├── 📄 utils.hpp
│ └── 📄 utils.cpp
├── 📁 LAB_2/ # Лабораторная работа 2 - Массивы
│ ├── 📄 main.cpp
│ ├── 📄 array.hpp
│ ├── 📄 array.cpp
│ ├── 📄 menu.hpp
│ ├── 📄 menu.cpp
│ ├── 📄 utils.hpp
│ └── 📄 utils.cpp
├── 📄 .gitignore # Git ignore файлы
└── 📄 README.md # Этот файл
text
```

## Компиляция и запуск

### LAB_1 - Матрицы:
```bash
cd LAB_1
g++ -o lab1 main.cpp matrix.cpp menu.cpp utils.cpp
./lab1
```

### LAB_2 - Массивы:
```bash
cd LAB_2
g++ -o lab2 main.cpp array.cpp menu.cpp utils.cpp
./lab2
```
