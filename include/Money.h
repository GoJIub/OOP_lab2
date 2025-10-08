#ifndef MONEY_H
#define MONEY_H

#include "bits/stdc++.h"

class Money {
public:
    
    Money(); // пустой: 0.00
    Money(size_t n, unsigned char t = 0); // n цифр, заполненных t (но t должно быть 0-9)
    Money(const std::initializer_list<unsigned char>& t); // из списка {5,4,3,2,1}
    Money(const std::string& str); // из строки "123.45" или "123"
    Money(const Money& other); // копирующий
    Money(Money&& other) noexcept; // перемещающий
    virtual ~Money() noexcept;

    Money& operator=(const Money& other); // копирующий оператор присваивания
    Money& operator=(Money&& other) noexcept; // перемещающий опертатор присваивания

    // Операции (возвращают новый Money)
    Money add(const Money& other) const;
    Money subtract(const Money& other) const;

    // Операции с присваиванием
    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);

    // Сравнения
    bool equals(const Money& other) const;
    bool greaterThan(const Money& other) const;
    bool lessThan(const Money& other) const;

    // Полезные методы
    std::string toString() const; // для вывода, например "123.45"
    size_t getSize() const; // размер массива

private:
    unsigned char* digits{nullptr};
    size_t size;

    void normalize();
};

// Свободные операторы
Money operator+(Money left, const Money& right);
Money operator-(Money left, const Money& right);

#endif