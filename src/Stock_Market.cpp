#include "Stock_Market.hpp"

#include <vector>
#include <random>
#include <cmath>

// Constructor to initialise variables
Stock_Market::Stock_Market(){
    initial_price = initial_price; // Initial price
    mu = mu;  // Drift
    sigma = sigma; // Volatility
    num_of_days = num_of_days; // Number of days to predict for
}

// Function to simulate geometric brownian motion
std::pair<std::vector<double>, std::vector<double>> Simulate_GBM(){

    // Initialise opening and closing prices arrays
    std::vector<double> opening_prices(num_of_days);
    std::vector<double> closing_prices(num_of_days);

    // Set the first value of the array to the initial price
    opening_prices[0] = initial_price;

    // Generate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generate random numbers following normal distribution
    std::normal_distribution<double> distribution(0.0, 1.0);

    // Initialise timestep
    double dt = 1.0 / 252.0;

    // Iterate through the number of days to predict for
    for (int i = 1; i < num_of_days; ++i) {
        // Calculate percentage change between previous days' opening and closing prices
        double percentage_change = (closing_prices[i - 1] - opening_prices[i - 1]) / opening_prices[i - 1];
        // Calculate drift
        double drift = mu * dt * percentage_change;
        // Calculate random factor
        double random_factor = sigma * sqrt(dt);
        // Initialise Weiner process variable
        double dW = distribution(gen);
        // Calculate price change 
        double price_change = drift + random_factor * dW;

        // Calculate and append the vectors with the most recent opening and closing prices
        opening_prices[i] = opening_prices[i - 1] * exp(price_change);
        closing_prices[i] = opening_prices[i] * (1 + distribution(gen));
    }

    return std::make_pair(opening_prices, closing_prices);

}