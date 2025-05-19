#include <pnl_calc.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./pnl_calculator <input_file.csv> <fifo|lifo>\n";
        return 1;
    }

    std::string method = argv[2];
    if (method != "fifo" && method != "lifo") {
        std::cerr << "Use 'fifo' or 'lifo'.\n";
        return 1;
    }

    process_trades(argv[1], method);
    return 0;
}