#include "Stock_Market.hpp"

#include <vector>
#include <random>
#include <cmath>
#include <iostream>


// Constructor to initialise variables
Stock_Market::Stock_Market(){
    initial_price = 100;    // Initial price
    mu = 0.5;               // Drift  £/day
    sigma = 2;              // Volatility  £/sqrt(s)
    num_of_days = 200;      // Number of days to predict for
}

// Function to simulate geometric brownian motion
std::pair<std::vector<double>, std::vector<double>> Stock_Market::Simulate_GBM(){

    // Initialise opening and closing prices arrays
    std::vector<double> opening_prices(num_of_days);
    std::vector<double> closing_prices(num_of_days);

    // Generate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generate random numbers following normal distribution
    std::normal_distribution<double> distribution(0.0, 1.0);

    double dt = 1.0 ; // Timestep days

    // Set the day 0 opening and closing prices to a random number
    opening_prices[0] = initial_price;
    closing_prices[0] = initial_price + 1; 


    // Iterate through the number of days to predict for
    for (int i = 1; i < num_of_days; ++i) {

        // Calculate drift
        double drift = mu; // Constant value mu

        // Calculate random factor (Wiener process)
        double dW = distribution(gen) * sigma * sqrt(dt);

        // Calculate price change 
        double price_change = drift + dW;

        opening_prices[i] = opening_prices[i-1] + (price_change);  
        closing_prices[i] = opening_prices[i];
        
    }

    return std::make_pair(opening_prices, closing_prices);

}