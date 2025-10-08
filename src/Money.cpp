#include "../include/Money.h"
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

    size_t i = 0;
    for (auto& val : t) {
        if (val > 9) throw std::invalid_argument("Digit must be 0-9");
        digits[i++] = val;
    }

    for (; i < size; ++i) digits[i] = 0;

    normalize();
}

Money::Money(const std::string& str) {
    size_t dotPos = str.find('.');

    std::string whole = (dotPos == std::string::npos) ? str : str.substr(0, dotPos);
    std::string decimal = (dotPos == std::string::npos) ? "0" : str.substr(dotPos + 1);

    if (decimal.length() > 2) throw std::invalid_argument("Too many decimals");
    while (decimal.length() < 2) decimal += '0';

    size = whole.length() + 2;
    digits = new unsigned char[size];

    if (decimal[0] < '0' || decimal[0] > '9' || decimal[1] < '0' || decimal[1] > '9')
        throw std::invalid_argument("Invalid decimal");
    digits[0] = static_cast<unsigned char>(decimal[1] - '0');
    digits[1] = static_cast<unsigned char>(decimal[0] - '0');

    for (size_t i = 0; i < whole.length(); ++i) {
        unsigned char c = whole[whole.length() - 1 - i];
        if (c < '0' || c > '9') throw std::invalid_argument("Invalid whole number");
        digits[i + 2] = c - '0';
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

Money& Money::operator=(const Money& other) {
    if (this == &other) return *this;

    delete[] digits;

    size = other.size;
    digits = new unsigned char[size];
    std::copy(other.digits, other.digits + size, digits);

    return *this;
}

Money& Money::operator=(Money&& other) noexcept {
    if (this == &other) return *this;

    delete[] digits;

    digits = other.digits;
    size = other.size;

    other.digits = nullptr;
    other.size = 0;

    return *this;
}

Money::~Money() noexcept {
    delete[] digits;
}

void Money::normalize() {
    while (size > 2 && digits[size - 1] == 0) --size;
}

Money Money::add(const Money& other) const {
    size_t maxSize = std::max(size, other.size);
    unsigned char* newDigits = new unsigned char[maxSize + 1];
    unsigned char tmp = 0;

    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char d1 = (i < size) ? digits[i] : 0;
        unsigned char d2 = (i < other.size) ? other.digits[i] : 0;
        unsigned char sum = d1 + d2 + tmp;
        newDigits[i] = sum % 10;
        tmp = sum / 10;
    }
    if (tmp) newDigits[maxSize] = tmp;

    Money result;
    delete[] result.digits;

    result.size = maxSize + (tmp ? 1 : 0);
    result.digits = new unsigned char[result.size];
    std::copy(newDigits, newDigits + result.size, result.digits);

    delete[] newDigits;
    result.normalize();
    return result;
}

Money Money::subtract(const Money& other) const {
    if (lessThan(other)) throw std::domain_error("Result would be negative");

    unsigned char* newDigits = new unsigned char[size];
    int tmp = 0;

    for (size_t i = 0; i < size; ++i) {
        int a = digits[i] - tmp;
        int b = (i < other.size) ? other.digits[i] : 0;

        if (a < b) {
            a += 10;
            tmp = 1;
        } else tmp = 0;
        newDigits[i] = a - b;
    }

    Money result;
    delete[] result.digits;
    result.size = size;
    result.digits = new unsigned char[size];
    std::copy(newDigits, newDigits + size, result.digits);

    delete[] newDigits;
    result.normalize();
    return result;
}

Money& Money::operator+=(const Money& other) {
    *this = this->add(other);
    return *this;
}

Money& Money::operator-=(const Money& other) {
    *this = this->subtract(other);
    return *this;
}

bool Money::equals(const Money& other) const {
    if (size != other.size) return false;
    return std::memcmp(digits, other.digits, size) == 0;
}

bool Money::greaterThan(const Money& other) const {
    if (size != other.size) return size > other.size;
    for (size_t i = size; i-- > 0;)
        if (digits[i] != other.digits[i]) return digits[i] > other.digits[i];
    return false;
}

bool Money::lessThan(const Money& other) const {
    if (size != other.size) return size < other.size;
    for (size_t i = size; i-- > 0;)
        if (digits[i] != other.digits[i]) return digits[i] < other.digits[i];
    return false;
}

std::string Money::toString() const {
    std::string decimal;
    decimal.push_back(char('0' + digits[1]));
    decimal.push_back(char('0' + digits[0]));

    std::string whole;
    if (size <= 2) {
        whole = "0";
    } else {
        for (size_t i = size - 1; i >= 2; --i) {
            whole.push_back('0' + digits[i]);
        }
    }
    return whole + "." + decimal;
}

size_t Money::getSize() const {
    return size;
}

Money operator+(Money left, const Money& right) {
    left += right;
    return left;
}

Money operator-(Money left, const Money& right) {
    left -= right;
    return left;
}