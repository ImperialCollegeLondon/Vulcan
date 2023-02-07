#include <iostream>

#include "Initialization_Parameters.hpp"

#include "Public_Info_Board.hpp"
#include "Household_Agent.hpp"
#include "Job.hpp"
#include "Job_Market.hpp"
#include "Firm_Agent.hpp"
#include "Loan.hpp"
#include "General_Good.hpp"
#include "Consumer_Firm_Agent.hpp"
#include "Capital_Firm_Agent.hpp"
#include "Initialization_Functions.hpp"
#include "Random_Functions.hpp"
#include "Data_Logging.hpp"

using namespace std;
int main()
{

    cout << "************* Program has started" <<endl;
    global_date = 0;



    //  ------------------ STEP 0 INITIALIZATION --------------------- 
    cout << "*****************Initialization Phase begun" << endl;

    // STEP 0.10: Initalize Public Board, Job Market, Bank
    
    Public_Info_Board* pPublic_Board_1 = new Public_Info_Board();
    Job_Market* pJob_Market_1 = new Job_Market();
    Bank_Agent* pBank_1 = new Bank_Agent(pPublic_Board_1);
    pPublic_Board_1->Set_Job_Market(pJob_Market_1);
    pPublic_Board_1->Set_Bank(pBank_1);

    cout << "Public Board at address: " << pPublic_Board_1 << " initialized" <<endl;
    cout << "Job Market at address: " << pJob_Market_1 << " initialized" <<endl;
    cout << "Bank at address: " << pBank_1 << " initialized" <<endl;


    int n_promised_jobs = 0;  // Debugging variable to keep track of # jobs to be assigned


    //------- STEP 0.11: Initialize Households and Firms
    
    Household_Agent * Household_array = (Household_Agent*)malloc(sizeof(Household_Agent) * n_households);
    Initialize_Households(Household_array, pPublic_Board_1, n_households); 
    Consumer_Firm_Agent * Cons_Firm_array = (Consumer_Firm_Agent*)malloc(sizeof(Consumer_Firm_Agent) * n_consumer_firms);
    Initialize_Consumer_Firms( Cons_Firm_array, pPublic_Board_1, n_consumer_firms, &n_promised_jobs);
    Capital_Firm_Agent * Cap_Firm_array = (Capital_Firm_Agent*)malloc(sizeof(Capital_Firm_Agent) * n_capital_firms);
    Initialize_Capital_Firms(Cap_Firm_array, pPublic_Board_1, n_capital_firms, &n_promised_jobs);
    

    //----------- STEP 0.13: Initialize job market
    cout << "Initializing job Market -  " << " Firms are seeking " << n_promised_jobs << " jobs" << endl;
    Initialize_Job_Market(Cons_Firm_array,Cap_Firm_array,Household_array,pPublic_Board_1);


    int n = 100;
    cout << " Household at position " << n << " has job :" <<  Household_array[n].Get_Employment_Status() << endl;
    n = 9900;
    cout << " Household at position " << n << " has job :" <<  Household_array[n].Get_Employment_Status() << endl;
    n = 9990;
    cout << " Household at position " << n << " has job :" <<  Household_array[n].Get_Employment_Status() << endl;
    

    // STEP 0.14 Assign firm owners - Todo later, minor thing

    // STEP 0.15: Save all Household and Firm properties to a csv file to check success of initialization
    Log_Household_Properties(Household_array, n_households);
    Log_Cons_Firm_Properties(Cons_Firm_array, n_consumer_firms);
    Log_Cap_Firm_Properties(Cap_Firm_array, n_capital_firms);


    //  -------- STEP 1 MAIN LOOP -------------------
    cout << "*****************Main Loop begun" << endl;
    // Timestep t= 0.0

    // STEP 1.1: Update Inflation Rate and Interest rate 
    // STEP 1.2: Depreciate Firm's Capital Goods
    // STEP 1.3: Depreciate Firm's Good Inventories
    // STEP 1.4: Layoff workers with expired contracts
    // STEP 1.5: Random experimentation - randomly tweak firm and household parameters
    // STEP 1.61: Firms assess past period's sales data
    // STEP 1.62: Firms pay dividend
    // STEP 1.63: Firms set new price and production targets
    // STEP 1.64: Firms set wage offers, labor target, and finance expected wage bill
    // STEP 1.71: Households update reservation wages
    // STEP 1.72: Labor market matching process
    // STEP 1.8: Firms make investment decisions and finance these
    
    // -- t= 0.5

    // STEP 1.91: Firms produce their goods
    // STEP 1.92: Households receive wage and make saving/consumption plans
    // STEP 1.93: Consumer good market commences
    // STEP 1.94: Investment good market commences


    // Timestep t=1












    // STEP 1.0: Update Inflation Rate and Interest rate 








    // STEP 1.1: Update Households , Firm
    // Households(n+1/2) =f [InfoBoard(n)] 
    // Firms(n+1/2)      = f[InfoBoard(n)] 

    // STEP 1.2: Add Jobs/Goods/Capital from Firms  (Job/interaction)      
    // JobMarket(n+1/2)  = f(Firms(n+1/2))
    // Sort the job
    // GoodMarket ...
    
    // STEP 1.3: Update Household  based on Markets
    // Households(n+1) = f(JobMarket(n+1/2), Household(n+1/2))
    // JobMarket(n+1)  = f(Firms(n+1))
    

    // Update InfoBoard (done automatically)
    // InfoBoard(n+1) = JobMarket(n+1),CapitalGoodMarket(n+1),CapitalGoodMarket(n+1)


    cout << "Program end :-)\n";
    return 0;
}

