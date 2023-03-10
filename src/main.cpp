#include <iostream>
#include <chrono>
#include <fstream>
#include <Windows.h>
#include <string>

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
#include "TimeLoop.hpp"

using namespace std;


int main()
{

    // Time program
     auto start = std::chrono::high_resolution_clock::now();


    cout << "************* Program has started" <<endl;

    std::ofstream output_file("../DataLogs/SimulationOutput.txt"); // create output file
    std::streambuf* old_cout_buf = std::cout.rdbuf(); // save old cout buffer
    std::cout.rdbuf(output_file.rdbuf()); // redirect cout to file

    


    //  ------------------ STEP 0 INITIALIZATION --------------------- 
    cout << "*****************Initialization Phase begun*********" << endl;

    // Allocate memory
    Public_Info_Board* pPublic_Board_1 = new Public_Info_Board();
    Job_Market* pJob_Market_1 = new Job_Market();
    Bank_Agent* pBank_1 = new Bank_Agent(pPublic_Board_1);
    Consumer_Goods_Market* pConsumer_Goods_Market_1 = new Consumer_Goods_Market();
    Capital_Goods_Market* pCapital_Goods_Market_1 = new Capital_Goods_Market();

    vector<Household_Agent*> *pHousehold_vector = new vector<Household_Agent*>();
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector = new vector<Consumer_Firm_Agent*>();
    vector<Capital_Firm_Agent*> *pCapital_Firm_vector = new vector<Capital_Firm_Agent*>();

    Initialize_Households_Firms_Jobs(pHousehold_vector, pConsumer_Firm_vector, pCapital_Firm_vector,
    pPublic_Board_1, pJob_Market_1, pConsumer_Goods_Market_1, pCapital_Goods_Market_1, pBank_1);


    // Create vector housing all firms
    std::vector<Firm_Agent*> *pAll_Firms_vector = new vector<Firm_Agent*>();

    // Copy pointers from consumer_firms to combined_firms
    std::copy(pConsumer_Firm_vector->begin(), pConsumer_Firm_vector->end(), std::back_inserter(*pAll_Firms_vector));

    // Copy pointers from capital_firms to combined_firms
    std::copy(pCapital_Firm_vector->begin(), pCapital_Firm_vector->end(), std::back_inserter(*pAll_Firms_vector));


    

    // STEP 0.15: Save all Household and Firm properties to a csv file to check success of initialization
    cout << "Step 0.15: Log initial Household and Firm data" << endl;
    Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, pPublic_Board_1);



    //  -------- STEP 1 MAIN LOOP -------------------
    cout << "\n***************** Main Loop begun" << endl;
    global_date = 1;

    for ( int i = 0; i < n_loops; i++){
        Time_Step_1(pHousehold_vector, pConsumer_Firm_vector, pCapital_Firm_vector, pAll_Firms_vector,
        pPublic_Board_1, pJob_Market_1, pConsumer_Goods_Market_1, pCapital_Goods_Market_1, pBank_1);
        cout << "Time step " << i << " completed - Logging data now" << endl;
        Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, pPublic_Board_1);
        global_date++;
    }

    cout << "----------------------"<<endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    std::cout << "Execution time: " <<  elapsed_seconds << " s" << std::endl;
    std::cout << "Program ran for " << n_loops << " timesteps with " << n_households << " households, " << n_consumer_firms<< " consumer firms and " << n_capital_firms << " capital firms." << std::endl;


    std::cout.rdbuf(old_cout_buf);
    cout << "Program end :-)\n";



    // Log short description of Simulation
/*     string file_name= "Simulation_H_" + to_string(n_households) + "_Cons_" + to_string(n_consumer_firms) +"_Cap_" + to_string(n_capital_firms) + ".txt";
    cout  << "File name: " << file_name << endl;
    ofstream file( "DataLogs/" + file_name );
    file << "Ran simulation with n_households = " << n_households << "n_consumer_firms = " << 
    n_consumer_firms << "n_capital_firms = " << n_capital_firms << endl;
    file.close();
 */
    

    return 0;
}

