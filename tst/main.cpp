#include <iostream>
#include "Stock_Market.hpp"

using namespace std;

int main() {
    Stock_Market stock_instance;
    auto stock_prices = stock_instance.Simulate_GBM();

    for (int i = 0; i < stock_prices.first.size(); ++i) {
        std::cout << "Day " << i << ": Opening Price = " << stock_prices.first[i] << ", Closing Price = " << stock_prices.second[i] << std::endl;
    }

    return 0;
}



