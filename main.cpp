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

        // Пример 4: Сложение через метод add()
        Money sum = a.add(b);
        std::cout << "A + B (add): " << sum.toString() << " (size: " << sum.getSize() << ")" << std::endl;

        // Пример 5: Вычитание через метод subtract()
        Money diff = a.subtract(b);
        std::cout << "A - B (subtract): " << diff.toString() << " (size: " << diff.getSize() << ")" << std::endl;

        // Пример 6: Сравнения
        std::cout << "A == B? " << (a.equals(b) ? "Yes" : "No") << std::endl;
        std::cout << "A > B? " << (a.greaterThan(b) ? "Yes" : "No") << std::endl;
        std::cout << "A < B? " << (a.lessThan(b) ? "Yes" : "No") << std::endl;

        // Пример 7: Из initializer_list
        Money c({5, 4, 3, 2, 1});  // -> 123.45
        std::cout << "C from list: " << c.toString() << std::endl;

        // Пример 8: Перенос в сложении (999.99 + 0.01 = 1000.00)
        Money big("999.99");
        Money small("0.01");
        Money carrySum = big + small; // теперь оператор+
        std::cout << "999.99 + 0.01: " << carrySum.toString() << " (size: " << carrySum.getSize() << ")" << std::endl;

        // Пример 9: Заём при вычитании (1000.00 - 999.99 = 0.01)
        Money diffBorrow = carrySum - big; // оператор-
        std::cout << "1000.00 - 999.99: " << diffBorrow.toString() << std::endl;

        // Пример 10: Проверка +=
        Money plusEq("10.25");
        plusEq += Money("0.75");
        std::cout << "10.25 += 0.75 -> " << plusEq.toString() << std::endl;

        // Пример 11: Проверка -=
        Money minusEq("50.00");
        minusEq -= Money("20.25");
        std::cout << "50.00 -= 20.25 -> " << minusEq.toString() << std::endl;

        // Пример 12: Цепочка операторов (chaining)
        Money chain("1.00");
        chain += Money("2.00") += Money("3.00");
        std::cout << "1.00 += 2.00 += 3.00 -> " << chain.toString() << std::endl;

        // Пример 13: Проверка копирующего присваивания
        Money copySrc("777.77");
        Money copyRes("0.00");
        copyRes = copySrc;
        std::cout << "Copy assignment: " << copyRes.toString() << std::endl;

        // Пример 14: Проверка перемещающего присваивания
        Money moveSrc("888.88");
        Money moveRes("0.00");
        moveRes = std::move(moveSrc);
        std::cout << "Move assignment: " << moveRes.toString() << std::endl;
        std::cout << "(moveSrc is safe after moving, size=" << moveSrc.getSize() << ")" << std::endl;

        // Пример 15: Нормализация ведущих нулей
        Money withZeros("000100.00");  // → 100.00
        std::cout << "With zeros: " << withZeros.toString() 
                  << " (size: " << withZeros.getSize() << ")" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}