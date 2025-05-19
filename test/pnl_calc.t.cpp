#include <pnl_calc.h>
#include <gtest/gtest.h>
#include <deque>
#include <stack>

TEST(PnlCalculatorTest, FifoCalculation) {
    std::deque<std::pair<int, double>> fifo;
    std::stack<std::pair<int, double>> dummy;

    fifo.emplace_back(15, 11.00);
    fifo.emplace_back(15, 12.50);

    double pnl = calculate_pnl_for_trade("fifo", 'S', 13.00, 20, fifo, dummy);
    EXPECT_NEAR(pnl, 32.50, 1e-2);
}

TEST(PnlCalculatorTest, LifoCalculation) {
    std::deque<std::pair<int, double>> dummy;
    std::stack<std::pair<int, double>> lifo;

    lifo.push({15, 12.50});
    lifo.push({15, 11.00});

    double pnl = calculate_pnl_for_trade("lifo", 'S', 13.00, 20, dummy, lifo);
    EXPECT_NEAR(pnl, 17.50, 1e-2);
}