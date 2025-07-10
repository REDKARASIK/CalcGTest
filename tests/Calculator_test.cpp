#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <InMemoryHistory.h>
#include <SimpleCalculator.h>

using namespace calc;

class MockHistChecker : public IHistory {
public:
    MOCK_METHOD(void, AddEntry, (const std::string& operation), (override));
    MOCK_METHOD(std::vector<std::string>, GetLastOperations, (size_t count), (const, override));
};

// Простое сложение
TEST(SimpleCalcTest, AddTest) {
    InMemoryHistory hist;
    SimpleCalculator calc(hist);
    EXPECT_EQ(calc.Add(1, 2), 3);
}

// Проверка добавления сложения в историю
TEST(SimpleCalcTestHistory, AddTestHistory) {
    MockHistChecker hist;
    EXPECT_CALL(hist, AddEntry("2 + 0 = 2")).Times(::testing::Exactly(1));
    SimpleCalculator calc(hist);
    EXPECT_EQ(calc.Add(2, 0), 2);
}

// Проверка вычитания
TEST(SimpleCalcTest, SubstractTest) {
    InMemoryHistory hist;
    SimpleCalculator calc(hist);
    EXPECT_EQ(calc.Subtract(0, 1), -1);
}

// Проверка добавления вычитания в истории
TEST(SimpleCalcTestHistory, SubstractTestHistory) {
    MockHistChecker hist;
    EXPECT_CALL(hist, AddEntry("5 - 3 = 2")).Times(::testing::Exactly(1));
    SimpleCalculator calc(hist);
    EXPECT_EQ(calc.Subtract(5, 3), 2);
}

// Проверка умножения
TEST(SimpleCalcTest, MultiplyTest) {
    InMemoryHistory hist;
    SimpleCalculator calc(hist);
    EXPECT_EQ(calc.Multiply(2, 0), 0);
}

// Проверка добавления умножения в историю
TEST(SimpleCalcTestHistory, MultiplyTestHistory) {
    MockHistChecker hist;
    EXPECT_CALL(hist, AddEntry("2 * 2 = 4")).Times(::testing::Exactly(1));
    SimpleCalculator calc(hist);
    EXPECT_EQ(calc.Multiply(2, 2), 4);
}

// Проверка деления
TEST(SimpleCalcTest, DivideTest) {
    InMemoryHistory hist;
    SimpleCalculator calc(hist);
    EXPECT_EQ(calc.Divide(5, 2), 2);
}

// Проверка деления на 0
TEST(SimpleCalcTest, DivideByZeroTest) {
    InMemoryHistory hist;
    SimpleCalculator calc(hist);
    EXPECT_THROW(calc.Divide(2, 0), std::invalid_argument);
}

// Проверка добавления деления в историю
TEST(SimpleCalcTestHistory, DivideTestHistory) {
    MockHistChecker hist;
    EXPECT_CALL(hist, AddEntry("6 / 2 = 3")).Times(::testing::Exactly(1));
    SimpleCalculator calc(hist);
    EXPECT_EQ(calc.Divide(6, 2), 3);
}

// Проверка получения последнего добавления
TEST(SimpleCalcTestHistory, HistoryTest) {
    InMemoryHistory hist;
    SimpleCalculator calc(hist);
    calc.Add(1, 2);
    std::vector<std::string> oper = hist.GetLastOperations(1);
    ASSERT_EQ(oper.size(), 1);
    EXPECT_EQ(oper[0], "1 + 2 = 3");
}

TEST(SimpleCalcTestHistory, SwapHistoryTest) {
    InMemoryHistory hist1;
    SimpleCalculator calc(hist1);
    calc.Subtract(2, 1);
    EXPECT_EQ(hist1.GetLastOperations(1).back(), "2 - 1 = 1");
    MockHistChecker hist2;
    EXPECT_CALL(hist2, AddEntry("1 + 1 = 2")).Times(::testing::Exactly(1));
    calc.SetHistory(hist2);
    EXPECT_EQ(calc.Add(1, 1), 2);
}
