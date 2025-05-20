#pragma once
#include <string>

class OutHandler {
public:
    virtual void printPnL(int timestamp, const std::string& symbol, double pnl) = 0;
    virtual ~OutHandler() = default;
};