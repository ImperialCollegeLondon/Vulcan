#include "Capital_Firm_Agent.hpp"

// -------------- Constructors ---------



Capital_Firm_Agent::Capital_Firm_Agent(float float_vals[4], int int_vals[6]) : Firm_Agent::Firm_Agent(float_vals, int_vals)
{
    //identifier
    is_cons_firm = false;
    production_current = max(working_capital_inventory * cap_workers_per_machine * cap_productivity, employee_count_desired / cap_workers_per_machine * cap_productivity);
    inventory = production_current * desired_inventory_factor * Uniform_Dist_Float(0.5,1.5);
    quantity_sold = inventory *  init_quantity_sold_ratio; 
    average_sale_quantity = quantity_sold;
    
    cap_goods_on_market = new Capital_Good(this, good_price_current,inventory-quantity_sold, machine_lifespan);
    goods_on_market = cap_goods_on_market;
    // Put goods on Market
    //Send_Goods_To_Market();
}


//Copy constructor
Capital_Firm_Agent::Capital_Firm_Agent(Capital_Firm_Agent&){}

// Destructor
Capital_Firm_Agent::~Capital_Firm_Agent(){} 


// ------- Main Loop Methods-----------------

/* Function to loop through vector of capital goods the firm possesses,
mark down their value, and remove the ones with zero value, i.e. end of life
*/
/* void Capital_Firm_Agent::Depreciate_Capital(){

    for(auto i= capital_goods.begin(); i!=capital_goods.end(); i++){
        float original_price = (*i)->Get_Price();
        float current_val  =  (*i)->Get_Value();
        int depreciation_rate = (*i)->Get_Depreciation_Period();
        
        (*i)->Update_Value(current_val - original_price/depreciation_rate);

        if ((*i)->Get_Value() <= 0){capital_goods.erase(i);}
    }
    working_capital_inventory = int(capital_goods.size());
} */

/* Function to depreciate(i.e. destroy) a fraction of the firm's inventory of consumer goods
The depreciation rate is set exogenously in the initialization parameter for all firms
*/

void Capital_Firm_Agent::Depreciate_Good_Inventory(){
    inventory  = int(float(inventory)*(1.0-cap_good_inv_depr_rate));
}




/* Increment Firm inventory by the number of machines, productivity per machine,
*/
void Capital_Firm_Agent::Produce_Goods(){
    
    labor_utilization = min(float(working_capital_inventory*cons_workers_per_machine) / (float)employee_count , float(1.0));
    machine_utilization = min( float(employee_count/cons_workers_per_machine)/ (float)working_capital_inventory , float(1.0));
    
    // Check for negative values - debugging
    if (labor_utilization < 0 || machine_utilization < 0){
        cout << "Error: Labor or machine utilization is negative" << endl;
        labor_utilization = 0;
        machine_utilization = 0;
    }


    int production_max = working_capital_inventory * cap_productivity;
    
    production_current = min(int(production_max*labor_utilization), production_planned);

    inventory += production_current;
    inventory_factor = float(inventory) / float(average_sale_quantity);
    production_costs = production_current * cap_good_unit_cost;

    if ( production_current < 0){
        cout << "Error: Production current is negative" << endl;
        production_current = 0;
    }
    
    pPublic_Info_Board->Update_Capital_goods_production(production_current);
    pPublic_Info_Board->Update_Capital_goods_production_planned(production_planned);
}

/* Post Produced goods to market - only do this once at the beinning
*/
void Capital_Firm_Agent::Send_Goods_To_Market(){
    //cout << "Cap firm " << this <<" sending goods to market" << endl;
    pPublic_Info_Board->Send_Cap_Good_To_Market(cap_goods_on_market);

}

/* Update goods on market - Update the attributes of the goods referred by the pointer
cap_goods_on_market,  which should update the market as well */
void Capital_Firm_Agent::Update_Goods_On_Market(){
    cap_goods_on_market->Set_Quantity(inventory);
    cap_goods_on_market->Update_Price(good_price_current);
    cap_goods_on_market->Update_Value(good_price_current);
}


/* Update sentiment and post to public board*/
void Capital_Firm_Agent::Update_Sentiment(){
    Firm_Agent::Update_Sentiment();
    pPublic_Info_Board->Update_Cap_firm_sentiment_sum(sentiment);
}


/* Determine new production - call the base class method but update public
board accordingly*/




//------------------Non member functions---------------------------


