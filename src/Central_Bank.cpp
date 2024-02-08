# include "Central_Bank.hpp"

//----------Constructor  ------  

/* Initialize the Central Bank with a public board pointer
Initialize the inflation and interest rate wih preset global parameters
Initialize everything else to zero
*/

Central_Bank::Central_Bank(Public_Info_Board* pPublic_Info_Board){

    this->pPublic_Board = pPublic_Info_Board;

    // Interest rate 
    r_rate = bank_init_interest_rate; // preset Global param
    risk_premium = bank_risk_premium; // preset Global param
    r_reaction = bank_inflation_reaction; // preset Global param

    // Inflation
    cons_inflation_target = bank_inflation_target; // preset Global param
    cons_inflation_past_month = bank_inflation_target_monthly; // preset Global param
    cons_inflation_previous = 1.0;

    // Initialize cons_inflation_history
    for(int i = 0; i < 12; i++){
        cons_inflation_previous *= bank_inflation_target_monthly; // preset Global param
        cons_inflation_history.push(bank_inflation_target_monthly);
    }

    cons_inflation_current = cons_inflation_previous;

    // Manufacturer inflation - start  off same as consumer inflation
    float cap_inflation_target = bank_inflation_target; // not actually used
    cap_inflation_past_month = bank_inflation_target_monthly; // preset Global param
    cap_inflation_previous = 1.0;

    for(int i = 0; i < 12;i++){
        cap_inflation_previous *= bank_inflation_target_monthly; // preset Global param
        cap_inflation_history.push(bank_inflation_target_monthly);
    }

    current_date = 0;
}

// --------- Inflation and Interest Rate Policies

/* Function to update consumer and capital price levels and inflation rate data
    First make public board update its price and inflation records
    Then get the latest inflation figures from the public board
*/
void Central_Bank::Update_Inflation(){
    // Set current to previous
    cons_inflation_previous = cons_inflation_current;
    cap_inflation_previous = cap_inflation_current;
    // Make public board update stuff
    pPublic_Board->Update_Consumer_Price_Level();
    pPublic_Board->Update_Capital_Price_Level();
    // Get the updated data
    cons_inflation_past_month = pPublic_Board->Get_Consumer_Inflation();
    cap_inflation_past_month = pPublic_Board->Get_Capital_Inflation();
    // Update inflation to match trailing 12m
    cons_inflation_current = cons_inflation_previous / cons_inflation_history.front() * cons_inflation_past_month;
    cap_inflation_current = cap_inflation_previous / cap_inflation_history.front() * cap_inflation_past_month;

    if(cons_inflation_current < 0){
        cout << "ERROR: Bank_Agent::Update_Inflation() - cons_inflation_current < 0" << endl;
    }

    // Update inflation_histories
    cons_inflation_history.pop();
    cons_inflation_history.push(cons_inflation_past_month);

    cap_inflation_history.pop();
    cap_inflation_history.push(cap_inflation_past_month);
}


/* Function to update interest rate based on new inflation data
 To be called after calling Update_Inflation_Rate()
 Use a simple taylor rule from the Jamel Paper
*/
void Central_Bank::Update_Interest_Rate(){

    float inflation_overshoot = max(cons_inflation_current - cons_inflation_target, float(0.0));

    float r_current = r_rate;

    // Set interest rate proportional to inflation overshoot
    r_rate = max(float(r_reaction* inflation_overshoot), float(0.01)); // minimum interest rate of 1%

    // Impose maximum increase limit
    if (r_rate > r_current + bank_max_interest_rate_change){
        r_rate = r_current + bank_max_interest_rate_change;
    }
    // Check for max interest rate limit
    r_rate = min(r_rate, bank_max_interest_rate) ; // maximum interest rate of 40%

    // Update historical records
    interest_rate_history.push(r_rate);
}

// ------- Printing and Logging Methods

/* String stream operator overload*/
std::ostream& operator<<(std::ostream& os, const Bank_Agent& obj) {
    os << "r_rate " << obj.r_rate << std::endl;
    //os << "r_reaction " << obj.r_reaction << std::endl;
    //os << "risk_premium " << obj.risk_premium << std::endl;
    //os << "cons_inflation_target " << obj.cons_inflation_target << std::endl;
    os << "cons_inflation_current " << obj.cons_inflation_current << std::endl;
    //os << "cons_inflation_previous " << obj.cons_inflation_previous << std::endl;
    //os << "cons_inflation_past_month " << obj.cons_inflation_past_month << std::endl;
    //os << "cap_inflation_current " << obj.cap_inflation_current << std::endl;
    //os << "cap_inflation_previous " << obj.cap_inflation_previous << std::endl;
    //os << "cap_inflation_past_month " << obj.cap_inflation_past_month << std::endl;
    os << "date " << obj.current_date << std::endl;
    return os;
}

/* Log data function */
vector<pair<string, float> >* Bank_Agent::Log_Data() {
        current_date = global_date;
        auto result = new vector<std::pair<string, float> >();

        // Get the names and values of all member variables
        std::stringstream ss;
        ss << *this;
        string line;
        while (std::getline(ss, line)) {
            string name;
            float value;
            std::stringstream(line) >> name >> value;
            result->emplace_back(name, value);
        }

        return result;
}

