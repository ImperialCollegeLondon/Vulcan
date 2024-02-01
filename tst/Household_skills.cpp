#include "Household_Skills.hpp"

#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <tuple>

// Constructor to intialise variables
Household_Skills::Household_Skills(){
    // Variables
    initial_skill = 1;
    initial_productivity = 1;
    productivity_factor = 0.1;  // Adjusts how much productivity scales with skill
    skill_volatility = 0.2;     // Volatility in skill due to external factors
    time_step = 1;              // Per day

    days = 10;

}

void Update_Skill_Level() {
    std::vector<double> household_index(10);
    std::vector<double> initial_skill_level(10);
    std::vector<double> final_skill_level(10);

    // Generate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generate random numbers following normal distribution
    std::normal_distribution<double> distribution(0.0, 1.0);


}



