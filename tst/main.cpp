#include <iostream>
#include <fstream>
#include "Stock_Market.hpp"

using namespace std;

int main() {
    Stock_Market stock_instance;
    auto stock_data = stock_instance.Simulate_GBM();
    auto stock_prices = stock_data.first;
    auto sentiments = stock_data.second;

    ofstream priceFile("prices.csv");
    ofstream sentimentFile("sentiments.csv");

    for (int i = 0; i < stock_prices.size(); ++i) {
        std::cout << "Day " << i << ": Price = " << stock_prices[i] << ", Sentiment = " << sentiments[i] << std::endl;

        priceFile << i << " " <<  stock_prices[i] << std::endl;
        sentimentFile << i << "," << sentiments[i] << std::endl;
    }

    priceFile.close();
    sentimentFile.close();

    return 0;
}



