#ifndef STOCK_MARKET_HPP
#define STOCK_MARKET_HPP

#include <vector>

// class Stock_Market_Initialisation;


class Stock_Market{
    public:
    // Constructor
    Stock_Market();

    // Functions
    std::pair<std::vector<double>, std::vector<double>> Simulate_GBM();

    private:
    // Variables
    double initial_price;
    double mu;
    double sigma;
    double sentiment;
    double alpha;
    double beta_1;
    double beta_2;
    double epsilon;
    int num_of_days;
};

#endif