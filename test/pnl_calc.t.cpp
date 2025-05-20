#include <pnl_calc.h>
#include <gtest/gtest.h>
#include <deque>
#include <stack>

#include <gmock/gmock.h>
#include <iouthandler.h>

using ::testing::DoubleNear;
const double eps = 1e-2;

class MockOutputHandler : public OutHandler {
public:
    MOCK_METHOD(void, printPnL, (int timestamp, const std::string& symbol, double pnl), (override));
};

TEST(PnlCalculatorTest, FifoCalculation) {
    std::deque<std::pair<int, double>> fifo;
    std::stack<std::pair<int, double>> dummy;

    fifo.emplace_back(15, 11.00);
    fifo.emplace_back(15, 12.50);

    double pnl = calculate_pnl_for_trade("fifo", 'S', 13.00, 20, fifo, dummy);
    EXPECT_NEAR(pnl, 32.50, eps);
}

TEST(PnlCalculatorTest, LifoCalculation) {
    std::deque<std::pair<int, double>> dummy;
    std::stack<std::pair<int, double>> lifo;
    
    lifo.push({15, 11.00});
    lifo.push({15, 12.50});

    double pnl = calculate_pnl_for_trade("lifo", 'S', 13.00, 20, dummy, lifo);
    EXPECT_NEAR(pnl, 17.50, eps);
}

TEST(PnLCalculatorTest, MultiTickerFIFO) {
    MockOutputHandler mockOutput;
    EXPECT_CALL(mockOutput, printPnL(105, "MSFT", DoubleNear(6.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(106, "AMZN", DoubleNear(6.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(108, "GOOGL", DoubleNear(250.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(108, "AAPL", DoubleNear(20.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(109, "GOOGL", DoubleNear(120.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(111, "AAPL", DoubleNear(5.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(111, "AMZN", DoubleNear(0.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(113, "MSFT", DoubleNear(-7.00, eps)));

    process_trades("data/moretickers.csv", "fifo", mockOutput);
}

TEST(PnLCalculatorTest, MultiTickerLIFO) {
    MockOutputHandler mockOutput;
    EXPECT_CALL(mockOutput, printPnL(105, "MSFT", DoubleNear(6.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(106, "AMZN", DoubleNear(6.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(108, "GOOGL", DoubleNear(250.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(108, "AAPL", DoubleNear(10, eps)));
    EXPECT_CALL(mockOutput, printPnL(109, "GOOGL", DoubleNear(120.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(111, "AAPL", DoubleNear(15.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(111, "AMZN", DoubleNear(0.00, eps)));
    EXPECT_CALL(mockOutput, printPnL(113, "MSFT", DoubleNear(-7.00, eps)));

    process_trades("data/moretickers.csv", "lifo", mockOutput);
}