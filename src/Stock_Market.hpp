#ifndef STOCK_MARKET_HPP
#define STOCK_MARKET_HPP

#include <vector>

class Stock_Market_Initialisation;
#include "Stock_Market_Initialisation.hpp"

class Stock_Market{
    public:
    // Constructor
    Stock_Market();

    // Functions
    std::pair<std::vector<double>, std::vector<double>> Simulate_GBM();

    // Variables
    int num_of_days;
};

#endif