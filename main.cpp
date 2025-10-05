#include "include/Money.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // Пример 1: Пустой конструктор (0.00)
        Money zero;
        std::cout << "Zero: " << zero.toString() << std::endl;

        // Пример 2: Из строки с копейками
        Money a("123.45");
        std::cout << "A: " << a.toString() << " (size: " << a.getSize() << ")" << std::endl;

        // Пример 3: Из строки без копеек
        Money b("67");
        std::cout << "B: " << b.toString() << " (size: " << b.getSize() << ")" << std::endl;

        // Пример 4: Сложение
        Money sum = a.add(b);
        std::cout << "A + B: " << sum.toString() << " (size: " << sum.getSize() << ")" << std::endl;

        // Пример 5: Вычитание
        Money diff = a.subtract(b);
        std::cout << "A - B: " << diff.toString() << " (size: " << diff.getSize() << ")" << std::endl;

        // Пример 6: Сравнения
        std::cout << "A == B? " << (a.equals(b) ? "Yes" : "No") << std::endl;
        std::cout << "A > B? " << (a.greaterThan(b) ? "Yes" : "No") << std::endl;
        std::cout << "A < B? " << (a.lessThan(b) ? "Yes" : "No") << std::endl;

        // Пример 7: Из initializer_list
        Money c({5, 4, 3, 2, 1});  // 123.45
        std::cout << "C from list: " << c.toString() << std::endl;

        // Пример 8: С переносом в сложении (999.99 + 0.01 = 1000.00)
        Money big("999.99");
        Money small("0.01");
        Money carrySum = big.add(small);
        std::cout << "999.99 + 0.01: " << carrySum.toString() << " (size: " << carrySum.getSize() << ")" << std::endl;

        // Пример 9: Вычитание с заёмом (100.00 - 99.99 = 0.01)
        Money diffBorrow = carrySum.subtract(big);
        std::cout << "1000.00 - 999.99: " << diffBorrow.toString() << std::endl;

        // Пример 10: Исключения
        // Money invalid("123.456");  // Бросит invalid_argument (слишком много копеек)
        // Money negative = b.subtract(a);  // Бросит domain_error (отрицательный результат)

        // Пример 11: Нормализация (ведущие нули)
        Money withZeros("000100.00");  // Должно нормализоваться к 100.00, size=5
        std::cout << "With zeros: " << withZeros.toString() << " (size: " << withZeros.getSize() << ")" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}