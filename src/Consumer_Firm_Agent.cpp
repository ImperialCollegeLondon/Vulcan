#include "Consumer_Firm_Agent.hpp"

#include <iostream>

/* Constructors and Destructor
*/
Consumer_Firm_Agent::Consumer_Firm_Agent(float float_vals[4], int int_vals[6]): Firm_Agent::Firm_Agent(float_vals,int_vals)
{
    is_cons_firm = true;

    workers_per_machine = cons_workers_per_machine;
    output_per_machine = cons_productivity;
    unit_good_cost = cons_good_unit_cost;

    production_current = max(working_capital_inventory * cons_workers_per_machine * cons_productivity,employee_count_desired / cons_workers_per_machine * cons_productivity);
    inventory = production_current * desired_inventory_factor * Uniform_Dist_Float(0.5,1.5);
    quantity_sold = inventory *  init_quantity_sold_ratio; 
    average_sale_quantity = quantity_sold;

    cons_goods_on_market = new Consumer_Good(this, good_price_current,inventory-quantity_sold);
    goods_on_market = cons_goods_on_market;
    //Send_Goods_To_Market();
    sector_id = 1;
}


//Copy constructor
Consumer_Firm_Agent::Consumer_Firm_Agent(Consumer_Firm_Agent&){}

// Destructor
Consumer_Firm_Agent::~Consumer_Firm_Agent(){} 
//------------------------------------------------------------

// ------- Main Loop Methods-----------------


/* Function to depreciate(i.e. destroy) a fraction of the firm's inventory of consumer goods
The depreciation rate is set exogenously in the initialization parameter for all firms
*/
void Consumer_Firm_Agent::Depreciate_Good_Inventory(){
    inventory  = int(float(inventory)*(1.0-cons_good_inv_depr_rate));
}


/* Increment Firm inventory by the number of machines, productivity per machine,
*/
void Consumer_Firm_Agent::Produce_Goods(){

   Firm_Agent::Produce_Goods();
    // Update the public info board

    pPublic_Info_Board->Update_Consumer_Goods_Production(sector_id, production_current);
    pPublic_Info_Board->Update_Consumer_Goods_Production_Planned(sector_id, production_planned);
}


/* Post Produced goods to market - Only do this in initialization period
*/
void Consumer_Firm_Agent::Send_Goods_To_Market(){
    //cout << "cons firm " << this << " sending goods to market" << endl;
    pPublic_Info_Board->Send_Cons_Good_To_Market(cons_goods_on_market);
}

/* Update the goods object via the stored pointer, the market already contains this pointer
*/
void Consumer_Firm_Agent::Update_Goods_On_Market(){
    goods_on_market->Update_Price(good_price_current);
    goods_on_market->Set_Quantity(inventory);
}



/* Update sentiment and post to public board*/
void Consumer_Firm_Agent::Update_Sentiment(){
    Firm_Agent::Update_Sentiment();
    pPublic_Info_Board->Update_Cons_firm_sentiment_sum(sentiment);
}


/* Function that receives pointer to the sector struct and assigns the firm to that sector
Needs to update: 
*/
void Consumer_Firm_Agent::Assign_Sector(Consumer_Firm_Sector* pSector_Struct){

    // Update the sector of the firm
    sector_id = pSector_Struct->sector_id;

    // Update the sector of the consumer goods the firm is producing
    cons_goods_on_market->Set_Sector_ID(pSector_Struct->sector_id);

    // Update any other necessary variables



}


//--------------------------------------------------------------   
//----- NonClass Functions  


