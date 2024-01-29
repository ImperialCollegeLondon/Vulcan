#include <iostream>
#include <fstream>
#include "Stock_Market.hpp"

using namespace std;

int main() {

    Stock_Market stock_instance;
    auto stock_data = stock_instance.Simulate_GBM();
    auto stock_prices = stock_data.first;
    auto daily_return = stock_data.second;

    ofstream priceFile("prices.csv");

    for (int i = 0; i < stock_prices.size(); ++i) {
        std::cout << "Day " << i << ": Price = " << stock_prices[i] << ", " << "Daily return = " << daily_return[i] << std::endl;

        priceFile << i << " " <<  stock_prices[i] << std::endl;  
    }

    priceFile.close();

    Stock_Market household_instance;
    auto household_data = household_instance.Household_Spending(daily_return);
    auto household_incomes = household_data.first;
    auto return_on_investment = household_data.second;

    for (int i = 0; i < household_incomes.size(); ++i) {
        std::cout << "Household index: " << i << ", Household income = " << household_incomes[i] << ", Return on investment = " << return_on_investment[i] << std::endl;
    }

    Stock_Market sentiment_instance;
    auto sentiment_data = sentiment_instance.Investor_Sentiment(daily_return);
    auto sentiment_values = sentiment_data;
    
    for (int i = 0; i < sentiment_values.size(); ++i) {
        std::cout << "Sentiment " << i << ": " << sentiment_values[i] << std::endl;
    }

    return 0;
}



