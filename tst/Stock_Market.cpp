#include "Stock_Market.hpp"

#include <vector>
#include <random>
#include <cmath>
#include <iostream>


// Constructor to initialise variables
Stock_Market::Stock_Market(){
    // GBM constants
    initial_price = 100;    // Initial price
    mu = 0.5;               // Drift  £/day
    sigma = 2;              // Volatility  £/sqrt(s)

    // Investor sentiment constants
    sentiment = 1;          // Investor sentiment 
    alpha = 0.1;
    beta_1 = 0.2;
    beta_2 = 0.3;
    epsilon = 0.4;

    // Initialise number of days to simulate for
    num_of_days = 200;      // Number of days to predict for

    
}

// Function to simulate geometric brownian motion
std::pair<std::vector<double>, std::vector<double>> Stock_Market::Simulate_GBM(){

    // Initialise prices arrays
    std::vector<double> prices(num_of_days);
    std::vector<double> sentiment_values(num_of_days, sentiment);

    // Generate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generate random numbers following normal distribution
    std::normal_distribution<double> distribution(0.0, 1.0);

    double dt = 1.0 ; // Timestep days

    // Set the day 0 opening and closing prices to a random number
    prices[0] = initial_price;
    sentiment_values[0] = sentiment;

    // Iterate through the number of days to predict for
    for (int i = 1; i < num_of_days; ++i) {

        // Calculate drift
        double drift = mu;

        // Calculate random factor (Wiener process)
        double dW = distribution(gen) * sigma * sqrt(dt);

        // Calculate price change 
        double price_change = drift + dW;

        prices[i] = prices[i-1] + (price_change);  

        // Determine whether to increase or decrease investor sentiment
        if (prices[i - 1] < prices[i]) {
            sentiment_values[i] = sentiment_values[i - 1] * (0.1 * (prices[i] - prices[i-1])) + distribution(gen);
        } else {
            sentiment_values[i] = sentiment_values[i - 1] * (-0.1 * (prices[i] - prices[i-1])) + distribution(gen);
        }
        
    }

    return std::make_pair(prices, sentiment_values);

}
