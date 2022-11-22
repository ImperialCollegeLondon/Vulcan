/* This header file includes the class declarations for the
financial sector agents, i.e. banks. 
For simplicity the model will include only one bank that handles
the credit origination.

*/
class Financial_Sector_Agent{

    public:

    Financial_Sector_Agent(); //Constructor
    Financial_Sector_Agent(Financial_Sector_Agent&); //Copy constructor
    ~Financial_Sector_Agent(); //Destructor


    private:
    // --- Outflows --
    int deposit_outflows;
    int loan_issuance;
    int debt_payments;
    int tax_payments;


    // --- Inflow Variables
    int deposit_inflow;
    int loan_installment_repayments;
    int interest_repayments;
    //int new_debt_issuance; // may exclude this


    // --- State Variables
    int total_deposits;
    int total_assets;
    int total_liabilities;
    int cash_on_hand;

    int total_credit_issuance;
    
    // -- Constants
    int capital_ratio;






};