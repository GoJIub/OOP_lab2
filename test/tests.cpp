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
    Money m({5, 4, 3, 2, 1}); // digits = {5,4,3,2,1} → число 123.45
    EXPECT_EQ(m.toString(), "123.45");
}

// --- Присваивания ---
TEST(MoneyAssignmentTest, CopyAssignment) {
    Money a("123.45");
    Money b("67.00");

    b = a; // копирующее присваивание
    EXPECT_EQ(b.toString(), "123.45");
    EXPECT_EQ(a.toString(), "123.45");
    EXPECT_NE(&a, &b); // разные объекты
}

TEST(MoneyAssignmentTest, MoveAssignment) {
    Money a("999.99");
    Money b("0.00");

    b = std::move(a);
    EXPECT_EQ(b.toString(), "999.99");
    EXPECT_TRUE(a.getSize() == 0 || a.toString() == "0.00");
}

TEST(MoneyAssignmentTest, SelfAssignment) {
    Money a("321.10");
    a = a;
    EXPECT_EQ(a.toString(), "321.10");
}

// --- Арифметика с присваиванием ---
TEST(MoneyArithmeticAssignmentTest, PlusEqualsSimple) {
    Money a("100.50");
    Money b("0.50");

    a += b;
    EXPECT_EQ(a.toString(), "101.00");
}

TEST(MoneyArithmeticAssignmentTest, MinusEqualsSimple) {
    Money a("200.00");
    Money b("50.25");

    a -= b;
    EXPECT_EQ(a.toString(), "149.75");
}

TEST(MoneyArithmeticAssignmentTest, PlusEqualsWithCarry) {
    Money a("999.99");
    Money b("0.01");

    a += b;
    EXPECT_EQ(a.toString(), "1000.00");
}

TEST(MoneyArithmeticAssignmentTest, MinusEqualsWithBorrow) {
    Money a("1000.00");
    Money b("999.99");

    a -= b;
    EXPECT_EQ(a.toString(), "0.01");
}

TEST(MoneyArithmeticAssignmentTest, MinusEqualsThrowsWhenNegative) {
    Money a("5.00");
    Money b("10.00");

    EXPECT_THROW(a -= b, std::domain_error);
}

// --- Свободные операторы + и - ---
TEST(MoneyTest, AdditionOperator) {
    Money a("123.45");
    Money b("67.00");
    Money c = a + b;
    EXPECT_EQ(c.toString(), "190.45");
}

TEST(MoneyTest, SubtractionOperator) {
    Money a("123.45");
    Money b("67.00");
    Money c = a - b;
    EXPECT_EQ(c.toString(), "56.45");
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
    Money c = a + b;
    EXPECT_EQ(c.toString(), "0.00");
}

TEST(MoneyTest, LargeAddition) {
    Money a("123456789.99");
    Money b("0.01");
    Money c = a + b;
    EXPECT_EQ(c.toString(), "123456790.00");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}