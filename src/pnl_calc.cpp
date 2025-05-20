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
    int remaining = quantity;
    double pnl = 0.0;

    if (method == "fifo") {
        // we pull what came in first to calc
        while (remaining > 0 && !fifo_storage.empty()) {
            auto& [q, p] = fifo_storage.front();
            int matched = std::min(remaining, q);
            pnl += matched * (price - p);
            q -= matched;
            remaining -= matched;
            if (q == 0) fifo_storage.pop_front();
        }
    } else {
        // we pull what came in latest (last) to calc
        while (remaining > 0 && !lifo_storage.empty()) {
            auto& [q, p] = lifo_storage.top();
            int matched = std::min(remaining, q);
            pnl += matched * (price - p);
            q -= matched;
            remaining -= matched;
            if (q == 0) lifo_storage.pop();
        }
    }

    return pnl;
}

void process_trades(const std::string& filename, const std::string& method, OutHandler& handler) {
    std::ifstream file(filename);
    std::string line;
    getline(file, line);

    // i know this is not optimal, if production case i would create wrapper class that points
    // to correct struct based on method provided
    std::map<std::string, std::deque<std::pair<int, double>>> fifo_map;
    std::map<std::string, std::stack<std::pair<int, double>>> lifo_map;

    // get all info needed, make sure safely parsed and append to appropriate struct
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string ts_str, symbol, act_str, price_str, qty_str;
        getline(iss, ts_str, ',');
        getline(iss, symbol, ',');
        getline(iss, act_str, ',');
        getline(iss, price_str, ',');
        getline(iss, qty_str, ',');

        int timestamp = 0;
        try {
            timestamp = std::stoi(ts_str);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid number format for timestamp: " << ts_str << "\n";
            return;
        } catch (const std::out_of_range& e) {
            std::cerr << "Number out of range for timestamp: " << ts_str << "\n";
            return;
        }
        
        double price = 0.0;
        try {
            price = std::stod(price_str);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid number format for price: " << price_str << "\n";
            return;
        } catch (const std::out_of_range& e) {
            std::cerr << "Number out of range for price: " << price_str << "\n";
            return;
        }
        
        int qty = 0;
        try {
            qty = std::stoi(qty_str);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid number format for qty: " << qty_str << "\n";
            return;
        } catch (const std::out_of_range& e) {
            std::cerr << "Number out of range for qty: " << qty_str << "\n";
            return;
        }

        char action = act_str[0];
        if (action == 'B') {
            if (method == "fifo") {
                fifo_map[symbol].emplace_back(qty, price);
            } else {
                lifo_map[symbol].push({qty, price});
            }
        } else if (action == 'S') {
            double pnl = calculate_pnl_for_trade(method, action, price, qty, fifo_map[symbol], lifo_map[symbol]);
            // handler is nice for mock test cases :)
            handler.printPnL(timestamp, symbol, pnl);
        }
    }
}