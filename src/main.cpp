#include <iostream>
#include "Public_Info_Board.hpp"
#include "Household_Agent.hpp"




int main()
{
    // Parameter list //
    int n_households = 100;
    int n_consumer_firms = 10;
    int n_capital_firms = 5;

    int job_market_size = n_households/5;





    //Public_Info_Board* pPublic_Info_Board = new Public_Info_Board();

    Household_Agent* Household_1 = new Household_Agent(1000, 10, false, false, 500, 0.4,0.2);

    Household_1->Print();


    
    

    std::cout << "Hello World :-)\n";
    return 0;
}

