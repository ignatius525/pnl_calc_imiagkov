#pragma once

#include <string>
#include <deque>
#include <stack>
#include <iouthandler.h>

void process_trades(const std::string& filename, const std::string& method, OutHandler& handler);

double calculate_pnl_for_trade(const std::string& method,
                               char action,
                               double price,
                               int quantity,
                               std::deque<std::pair<int, double>>& fifo_storage,
                               std::stack<std::pair<int, double>>& lifo_storage);