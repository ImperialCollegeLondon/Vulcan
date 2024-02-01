#include "Stock_Market.hpp"

#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <tuple>


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

    // Household
    household_number = 10;       // n_households in main code
    percent_invest = 0.15;

    // Initialise number of days to simulate for
    num_of_days = 100;      // Number of days to predict for

    // Autoregressive model
    weight = 0.5;
    learning_rate = 0.01;
    loss = 0.0;
  
}

// class AutoregressiveModel {
//     float weight;
//     float learningrate;
// }

/*Function to simulate geometric brownian motion
*/ 
std::pair<std::vector<double>, std::vector<double>> Stock_Market::Simulate_GBM(){

    // Initialise prices array
    std::vector<double> prices(num_of_days);
    // Intialise daily price return array
    std::vector<double> daily_price_return(num_of_days);


    // Generate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generate random numbers following normal distribution
    std::normal_distribution<double> distribution(0.0, 1.0);

    double dt = 1.0 ; // Timestep days

    // Set the day 0 opening and closing prices to a random number
    prices[0] = initial_price;


    // Iterate through the number of days to predict for
    for (int i = 1; i < num_of_days; ++i) {

        // Calculate drift
        double drift = mu;

        // Calculate random factor (Wiener process)
        double dW = distribution(gen) * sigma * sqrt(dt);

        // Calculate price change 
        double price_change = drift + dW;
        // Calculate next day price
        prices[i] = prices[i-1] + (price_change);  

        // Calculate daily return and append to array
        double daily_return_percentage = (price_change / prices[i - 1]);
        daily_price_return[i] = daily_return_percentage;

    }

    return std::make_pair(prices, daily_price_return);

}

/*Function to calculate the ROI of a households income after investing on the stock
*/
std::pair<std::vector<double>, std::vector<double>> Stock_Market::Household_Spending(const std::vector<double> daily_price_return){

    // Create array to store household incomes
    std::vector<double> household_incomes(household_number);
    std::vector<double> total_value_of_investment(household_number);
    std::vector<double> return_on_investment(household_number);

    // Generate random household incomes between 500 and 1000
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(500, 1000);

    // Initalise the total return
    double tot_return = 0.0;

    // Sum the daily price return values to get the total return
    for (double price_return : daily_price_return) {
        tot_return += price_return;
    }

    for (int i = 0; i < household_number; ++i) {

        // Generate a random income number between 500 and 1000
        household_incomes[i] = distribution(gen);

        // Calculate the total value of the investment after x days
        total_value_of_investment[i] = (0.15 * household_incomes[i]) * (1 + tot_return);

        // Calculate return on investment
        return_on_investment[i] = total_value_of_investment[i] - (percent_invest * household_incomes[i]); // Add this to consumption_budget in Household_Agent.cpp

    }

    return std::make_pair(household_incomes, return_on_investment);
}

/*Function that calculates investor sentiment based on whether stock price goes up or down
*/ 
std::vector<double> Stock_Market::Investor_Sentiment(const std::vector<double> daily_price_return){

    // Initialise investor sentiment array
    std::vector<double> sentiment_values(num_of_days, sentiment);

    // Generate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generate random numbers following normal distribution
    std::normal_distribution<double> distribution(0.0, 1.0);

    // Set intial sentiment to the defined value
    sentiment_values[0] = sentiment;

    for (int i = 1; i < daily_price_return.size(); ++i) {
        if (daily_price_return[i] > 0) {
            sentiment_values[i] = sentiment_values[i - 1] + (1 * daily_price_return[i]);
        } else {
            sentiment_values[i] = sentiment_values[i - 1] - (1 * daily_price_return[i]);
        }
    }

    return sentiment_values;

}

void Stock_Market::Train_AR_model(const std::vector<double> prices, const std::vector<double> sentiment_values, int epochs){
    int n = prices.size();
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (int i = 0; i < n; ++i) {
            // Predicted sentiment at each step
            double sentiment_prediction = weight * (prices[i] - prices[i - 1]);
            // Loss is calculated using Mean Squared Error
            loss += sentiment_prediction * sentiment_prediction;
            // Gradient is 2 * MSE * weight
            double gradient = 2 * sentiment_prediction * (prices[i] - prices[i - 1]);
            weight -= learning_rate * gradient;
        }
    }
}

std::vector<double> Stock_Market::Predict_Sentiment(const std::vector<double> prices, double weight) {
    
    //Initalise predicted sentiment vector
    std::vector<double> predicted_sentiment(prices.size());
    predicted_sentiment[0] = 1;

    // Generate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generate random numbers following normal distribution
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int i = 1; i < prices.size(); ++i) {
        double sentiment_prediction = weight * (prices[i] - prices[i - 1]) + distribution(gen);
        predicted_sentiment[i] = sentiment_prediction;
    }

    return predicted_sentiment;
}
