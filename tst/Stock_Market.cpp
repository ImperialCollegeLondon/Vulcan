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
    num_of_days = 200;       // Number of days to predict for
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

    // Initialise timestep
    double dt = 1.0 ;/// 252.0;


    // Set the first value of the array to the initial price
    opening_prices[0] = initial_price - mu * dt;
   // closing_prices[0] = initial_price  distribution(gen)*sigma;
    closing_prices[0] = initial_price ; 


    // Iterate through the number of days to predict for
    for (int i = 1; i < num_of_days; ++i) {

        // Calculate percentage change between previous days' opening and closing prices
        double percentage_change = (closing_prices[i - 1] - opening_prices[i - 1]) / opening_prices[i - 1];
        // opening prioces is teh same as closing price
        opening_prices[i] = closing_prices[i-1];

        // Calculate drift
        double drift = mu * dt ;//* percentage_change;


       // drift = closing_prices[i - 1] - opening_prices[i - 1];

        std::cout << "drift=" << drift << std:: endl;
                
     std::cout << "percentage_change=" << percentage_change << std:: endl;

        // Calculate random factor (Wiener process)
       // double random_factor = sigma * sqrt(dt);
        // Initialise Weiner process variable
        double dW = distribution(gen)* sqrt(dt);
        std::cout << "dW = " << dW << std:: endl;

        // Calculate price change 
        double price_change = drift+ sigma*dW;

        std::cout << "price change =" << price_change << std:: endl;


        // Calculate and append the vectors with the most recent opening and closing prices
        
        // dp = drift&*dt + diffusion* d W
        closing_prices[i] = opening_prices[i] + price_change;  


      std::cout << " diffprice  " << closing_prices[i]- opening_prices[i] << std::endl;

       std::cout <<  " open " << opening_prices[i] << " close " <<  closing_prices[i] << std::endl;


      //  opening_prices[i] = closing_prices[i - 1] * exp(price_change);

      //  closing_prices[i] = std::max(opening_prices[i] * (1 + distribution(gen)), 0.0);
        
    }

    return std::make_pair(opening_prices, closing_prices);

}