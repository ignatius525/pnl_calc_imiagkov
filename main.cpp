#include <pnl_calc.h>
#include <iouthandler.h>
#include <iomanip>
#include <iostream>

class StdOutHandler : public OutHandler {
public:
    void printPnL(int timestamp, const std::string& symbol, double pnl) override {
        std::cout << timestamp << "," << symbol << "," << std::fixed << std::setprecision(2) << pnl << std::endl;
    }
};

int main(int argc, char* argv[]) {
    using namespace std;
    if (argc != 3) {
        cerr << "Usage: ./pnl_calculator <input_file.csv> <fifo|lifo>\n";
        return 1;
    }

    string filepath = argv[1];
    string method = argv[2];
    if (method != "fifo" && method != "lifo") {
        cerr << "Use 'fifo' or 'lifo'.\n";
        return 1;
    }
    // this weird interface class handler is for easy mocking in unit tests and comparing print statements
    StdOutHandler handler;

    try {
        cout << "TIMESTAMP,SYMBOL,PNL\n"; 
        process_trades(filepath, method, handler);
    } catch (const std::exception& e) {
        cerr << "Error processing trades: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}