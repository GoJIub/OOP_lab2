#include "Money.h"
#include <cstring>
#include <algorithm>

Money::Money() : size(2) {
    digits = new unsigned char[2]{0, 0};
}

Money::Money(size_t n, unsigned char t) : size(std::max(n, static_cast<size_t>(2))) {
    if (t > 9) throw std::invalid_argument("Digit must be 0-9");
    digits = new unsigned char[size];
    std::fill_n(digits, size, t);
}

Money::Money(const std::initializer_list<unsigned char>& t) : size(std::max(t.size(), static_cast<size_t>(2))) {
    digits = new unsigned char[size];
    auto it = t.begin();
    for (size_t i = 0; i < size && it != t.end(); ++i, ++it) {
        if (*it > 9) throw std::invalid_argument("Digit must be 0-9");
        digits[i] = *it;
    }
    for (size_t i = t.size(); i < size; ++i) {
        digits[i] = 0;
    }
    normalize();
}

Money::Money(const std::string& str) {
    size_t dotPos = str.find(".");
    std::string whole = (dotPos == std::string::npos) ? str : str.substr(dotPos);
    std::string decimal = (dotPos == std::string::npos) ? "0" : str.substr(dotPos + 1);
    if (decimal.length() > 2) throw std::invalid_argument("Too many decimals");
    while (decimal.length() < 2) decimal += '0';

    size = whole.length() + 2;
    digits = new unsigned char[size];
    for (size_t i = 0; i < decimal.length(); ++i) {
        if (decimal[i] < '0' || decimal[i] > '9') throw std::invalid_argument("Invalid decimal");
        digits[i] = decimal[i] - '0';
    }
    for (size_t i = 0; i < whole.length(); ++i) {
        if (whole[i] < '0' || whole[i] > '9') throw std::invalid_argument("Invalid whole number");
        digits[decimal.length() + i] = whole[i] - '0';
    }
    normalize();
}

Money::Money(const Money& other) : size(other.size) {
    digits = new unsigned char[size];
    std::copy(other.digits, other.digits + size, digits);
}

Money::Money(Money&& other) noexcept : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

Money::~Money() noexcept {
    delete[] digits;
}

void Money::normalize() {
    while (size > 2 && digits[size - 1] == 0) {
        --size;
    }
}

