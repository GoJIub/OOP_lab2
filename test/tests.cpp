#include <gtest/gtest.h>
#include "../include/Money.h"

// --- Конструкторы ---

TEST(MoneyTest, DefaultConstructor) {
    Money m;
    EXPECT_EQ(m.toString(), "0.00");
    EXPECT_EQ(m.getSize(), 2);
}

TEST(MoneyTest, FromStringWithCents) {
    Money m("123.45");
    EXPECT_EQ(m.toString(), "123.45");
    EXPECT_EQ(m.getSize(), 5);
}

TEST(MoneyTest, FromStringWithoutCents) {
    Money m("67");
    EXPECT_EQ(m.toString(), "67.00");
    EXPECT_EQ(m.getSize(), 4);
}

TEST(MoneyTest, FromInitializerList) {
    // digits = {5,4,3,2,1} → число = 123.45
    Money m({5, 4, 3, 2, 1});
    EXPECT_EQ(m.toString(), "123.45");
}

// --- Арифметика ---

TEST(MoneyTest, AdditionSimple) {
    Money a("123.45");
    Money b("67.00");
    Money sum = a.add(b);
    EXPECT_EQ(sum.toString(), "190.45");
}

TEST(MoneyTest, AdditionWithCarry) {
    Money a("999.99");
    Money b("0.01");
    Money sum = a.add(b);
    EXPECT_EQ(sum.toString(), "1000.00");
}

TEST(MoneyTest, SubtractionSimple) {
    Money a("123.45");
    Money b("23.45");
    Money diff = a.subtract(b);
    EXPECT_EQ(diff.toString(), "100.00");
}

TEST(MoneyTest, SubtractionWithBorrow) {
    Money a("1000.00");
    Money b("999.99");
    Money diff = a.subtract(b);
    EXPECT_EQ(diff.toString(), "0.01");
}

// --- Сравнения ---

TEST(MoneyTest, ComparisonEquals) {
    Money a("50.00");
    Money b("50.00");
    EXPECT_TRUE(a.equals(b));
    EXPECT_FALSE(a.greaterThan(b));
    EXPECT_FALSE(a.lessThan(b));
}

TEST(MoneyTest, ComparisonGreaterLess) {
    Money a("123.45");
    Money b("67.00");
    EXPECT_TRUE(a.greaterThan(b));
    EXPECT_FALSE(a.lessThan(b));
    EXPECT_FALSE(a.equals(b));
}

// --- Нормализация и исключения ---

TEST(MoneyTest, NormalizationRemovesLeadingZeros) {
    Money m("000100.00");
    EXPECT_EQ(m.toString(), "100.00");
}

TEST(MoneyTest, InvalidInputTooManyCents) {
    EXPECT_THROW(Money("12.345"), std::invalid_argument);
}

TEST(MoneyTest, SubtractionNegativeResultThrows) {
    Money a("50.00");
    Money b("100.00");
    EXPECT_THROW(a.subtract(b), std::domain_error);
}

// --- Пограничные случаи ---

TEST(MoneyTest, ZeroPlusZero) {
    Money a("0.00");
    Money b("0.00");
    Money c = a.add(b);
    EXPECT_EQ(c.toString(), "0.00");
}

TEST(MoneyTest, LargeAddition) {
    Money a("123456789.99");
    Money b("0.01");
    Money c = a.add(b);
    EXPECT_EQ(c.toString(), "123456790.00");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}