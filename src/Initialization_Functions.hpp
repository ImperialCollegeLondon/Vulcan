
#ifndef INITIALIZATION_FUNCTIONS_HPP
#define  INITIALIZATION_FUNCTIONS_HPP


#include <iostream>
#include <vector>

#include "Firm_Agent.hpp"
#include "Consumer_Firm_Agent.hpp"
#include "Capital_Firm_Agent.hpp"
#include "Household_Agent.hpp"
#include "Public_Info_Board.hpp"
#include "Initialization_Parameters.hpp"
#include "Random_Functions.hpp"


using namespace std;

// Functions to initialize households and firms

void Initialize_Consumer_Firms(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, Public_Info_Board* pPublic_Board, int size, int* promised_jobs);
void Post_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size);
void Check_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size);

void Initialize_Capital_Firms(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, Public_Info_Board* pPublic_Board, int size, int* promised_jobs);
void Post_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size);
void Check_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size);

void Initialize_Households(vector<Household_Agent*> *pHousehold_vector, Public_Info_Board* pPublic_Board, int size);
void Initialize_Household_Jobs(vector<Household_Agent*> *pHousehold_vector,  int size);




// Function to set up Job market at t=0
void Initialize_Job_Market(vector<Household_Agent*> *pHousehold_vector,
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Public_Info_Board* pPublic_Info_Board);



#endif