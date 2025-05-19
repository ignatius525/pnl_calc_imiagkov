#include <pnl_calc.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <deque>
#include <stack> 


double calculate_pnl_for_trade(const std::string& method,
                               char action,
                               double price,
                               int quantity,
                               std::deque<std::pair<int, double>>& fifo_storage,
                               std::stack<std::pair<int, double>>& lifo_storage)
{
    double pnl = 0.0;
    return pnl;
}

void process_trades(const std::string& filename, const std::string& method) {
    std::ifstream file(filename);
    std::string line;
    getline(file, line);
}