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
    std::pair<std::vector<double>, std::vector<double>> Household_Spending(const std::vector<double> daily_price_return);
    std::vector<double> Investor_Sentiment(const std::vector<double> daily_price_return);
    void Train_AR_model(const std::vector<double> prices, const std::vector<double> sentiment_values, int epochs);
    std::vector<double> Predict_Sentiment(const std::vector<double> prices, double weight);


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
    double stock_return;
    double investment;
    double household_number;
    double percent_invest;
    double tot_reservation_wage;
    double weight;
    double learning_rate;
    double loss;
    int num_of_days;
};

#endif