#ifndef CENTRAL_BANK_HPP
#define CENTRAL_BANK_HPP

class Public_Info_Board;
#include "Initialization_Parameters.hpp"
#include "Public_Info_Board.hpp"

#include <queue>
#include <iostream>
#include <vector>

using namespace std;
class Central_Bank{

    public:
    // Constructor
    Central_Bank(Public_Info_Board* pPublic_Info_Board); 

    // Inflation and Interest Rate Policies
    void Update_Inflation();
    void Update_Interest_Rate();

    // Loan repayments
    void Check_Loans();

    // Getters
    float Get_Interest_Rate() {return r_rate;}

    // Printing and debugging
    friend std::ostream& operator<<(std::ostream& os, const Bank_Agent& obj);
    std::vector<std::pair<std::string, float>>* Log_Data();

    protected:
    Public_Info_Board* pPublic_Board;
    queue<float> cons_inflation_history; 
    queue<float> cap_inflation_history; 
    queue<float> interest_rate_history; 

    // Interest rates 
    float r_rate;
    float r_reaction; // How much the interest rate changes in response to inflation
    float risk_premium; // How much to increase interest rate per leverage ratio above threshold
 
    // Inflation
    float cons_inflation_current; // Inflation (trailing 12m)
    float cons_inflation_previous; // Inflation previous (i.e. last month) (trailing 12m)
    float cons_inflation_target; // Inflation (next 12m target)
    float cons_inflation_past_month; // Inflation Month on Month

    // Manufacturer inflation
    float cap_inflation_current; // Inflation (trailing 12m)
    float cap_inflation_previous; // Inflation previous (trailing 12m)
    //float cap_inflation_target; // Inflation (next 12m target) - No capital inflation target yet
    float cap_inflation_past_month; // Inflation MoM
    
    int current_date;

};

#endif // CENTRAL_BANK_HPP