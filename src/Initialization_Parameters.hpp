#ifndef INITIALIZATION_PARAMETERS_HPP
#define INITIALIZATION_PARAMETERS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <map>
#include <variant>
#include <queue>
#include <numeric>
#include <vector>
#include <tuple>

#include <random>
#include <algorithm>

typedef unsigned long ulong;
typedef unsigned int uint;

using namespace std;

//Declare the initialization_parameter maps
extern map<string, float> initialization_parameters;
extern map<string, float> main_loop_parameters;
extern map<string, float> randomness_parameters;

// Declare functions for reading and assigning simulation parameters
void Read_Parameters(map<string, float>& parameter_map, const char* filename);

void Assign_All_Parameters(map<string, float>& initialization_parameters,
map<string, float>& main_loop_parameters, map<string, float>& randomness_parameters);

void Print_Parameter_Map(map<string, float>& parameter_map);

vector<string> split(const string &s, char delimiter);


//-------------------- Simulation Size Parameters ---------------
extern int global_date; 
extern int n_loops;
extern int n_households;
extern int n_consumer_firms;
extern int n_capital_firms;
extern int n_firms;

extern int sector_count;


//--------------- Household parameters ---------------
// --- Household initialization parameters
// Below values are used to generate distributions of initial parameters for households
// Propensity to consume financial wealth, c_f
extern float household_init_c_f_mean;
extern float household_init_c_f_std;
extern float household_init_c_f_min;
extern float household_init_c_f_max;
// Propensity to consume excess money : c_excess_money
extern float household_init_c_excess_mean ;
extern float household_init_c_excess_std ;
extern float household_init_c_excess_min ;
extern float household_init_c_excess_max ;
// Savings propensity - optimist : saving_propensity_optimist 
extern float household_init_s_optimist_mean;
extern float household_init_s_optimist_std ;
extern float household_init_s_optimist_min ;
extern float household_init_s_optimist_max ;
// Savings propensity - pessimist : // saving_propensity_pessimist
extern float household_init_s_pessimist_mean;
extern float household_init_s_pessimist_std ;
extern float household_init_s_pessimist_min ;
extern float household_init_s_pessimist_max ;
// Starting wealth : wealth
extern float household_init_wealth_mean;
extern float household_init_wealth_std ;
extern float household_init_wealth_min ;
extern float household_init_wealth_max ;
// Maximum tolerable unemployment duration
extern float household_init_unemp_tolerance_mean;
extern float household_init_unemp_tolerance_std;
extern float household_init_unemp_tolerance_min;
extern float household_init_unemp_tolerance_max;
// Reservation Wage:
extern float household_init_res_wage_mean;
extern float household_init_res_wage_std;
extern float household_init_res_wage_min;
extern float household_init_res_wage_max;

// Wage parameters
extern int household_init_unemployment_benefit;
extern int household_init_minimum_wage;

// ---- Household dynamic parameters
extern float household_n_res_wage_decrease; // Household reservation wages are updated with *1-n_uniform*this_value
extern float household_targeted_savings_to_income_ratio;

// --- Household randomness parameters
extern float household_rand_sentiment_adoption;
extern float household_rand_sector_spending_weight_change;
extern float household_rand_emission_sensitivity_change;
extern float household_rand_job_search;

//---------------------------------------------

// ---- Parameters for all Firms ------------
extern int standard_employment_contract_length;
extern float firm_tax_rate;
// Below parameters define lower and upper bound of a uniform distribution 
// that forces machine purchases on companies

//---------------------------------------------

//---- Consumer Firm parameters----------------------
// --- Consumer Firm initialization parameters
// Starting total asset
extern float firm_cons_init_cash_mean;
extern float firm_cons_init_cash_std;
extern float firm_cons_init_cash_min;
extern float firm_cons_init_cash_max;
// Starting wage offers
extern float firm_cons_init_wage_offer_mean;
extern float firm_cons_init_wage_offer_std;
extern float firm_cons_init_wage_offer_min;
extern float firm_cons_init_wage_offer_max;
// Starting desired employees
extern float firm_cons_init_worker_demand_mean;
extern float firm_cons_init_worker_demand_std;
extern float firm_cons_init_worker_demand_min;
extern float firm_cons_init_worker_demand_max;
// Initial good price
extern float firm_cons_init_good_price_mean;
extern float firm_cons_init_good_price_std;
extern float firm_cons_init_good_price_min;
extern float firm_cons_init_good_price_max;
// Good inventory
extern float firm_cons_init_inv_factor_mean;
extern float firm_cons_init_inv_factor_std;
extern float firm_cons_init_inv_factor_min;
extern float firm_cons_init_inv_factor_max;
// Desired inventory factor ( characteristic)
extern float firm_cons_init_target_inv_factor_mean;
extern float firm_cons_init_target_inv_factor_std;
extern float firm_cons_init_target_inv_factor_min;
extern float firm_cons_init_target_inv_factor_max;

// Other inits (not randomised)
extern float firm_cons_init_production_current_ratio;
extern float firm_cons_init_quantity_sold_ratio;
extern float firm_cons_init_emissions_per_unit;
extern float firm_cons_init_dividend_ratio_optimist;
extern float firm_cons_init_dividend_ratio_pessimist;

// --- Consumer Firm dynamic parameters
extern float firm_cons_inv_depr_rate;
extern float firm_cons_productivity; // # units produced per worker machine pairing
extern int firm_cons_workers_per_machine;
extern float firm_cons_good_unit_cost;
extern float firm_cons_inv_reaction_factor;
extern float firm_cons_fixed_price_change;
extern float firm_cons_fixed_wage_change;

// --- Consumer Firm randomness parameters
extern float firm_cons_rand_dividend_change;
extern float firm_cons_rand_sentiment_adoption;
extern float firm_cons_rand_desired_inventory_factor_change;
extern float firm_cons_rand_price_change_upper_limit;
extern float firm_cons_rand_wage_change;



//---------------------------------------------

// Consumer Firm Sectors
struct Consumer_Firm_Sector {
    string sector_name;
    int sector_id; // unique id for this sector
    float weighing; // % of consumption that goes to this sector
    float inv_depr_rate;
    int output_per_machine;
    float good_unit_cost;
    float emission_per_unit; // NEWLY ADDED
    float emission_sensitivity_mean; // NEWLY ADDED
    int emission_allowance;

    Consumer_Firm_Sector(string p_name, int p_sector_id, float p_weighing, float p_inv_depr_rate, int p_output_per_machine, 
    float p_good_unit_cost, float p_emissions_per_unit, 
    float p_emission_sensitivity_mean, int p_emission_allowance)
    : sector_name(p_name), sector_id(p_sector_id), weighing(p_weighing),
    inv_depr_rate(p_inv_depr_rate), output_per_machine(p_output_per_machine), good_unit_cost(p_good_unit_cost), emission_per_unit(p_emissions_per_unit), 
    emission_sensitivity_mean(p_emission_sensitivity_mean), emission_allowance(p_emission_allowance)
    {}
};

//---------------------------------------------

//---- Capital Firm parameters----------------------

// --- Capital Firm initialization parameters
// Starting total asset
extern float firm_cap_init_cash_mean;
extern float firm_cap_init_cash_std;
extern float firm_cap_init_cash_min;
extern float firm_cap_init_cash_max;
// Starting wage offers
extern float firm_cap_init_wage_offer_mean;
extern float firm_cap_init_wage_offer_std;
extern float firm_cap_init_wage_offer_min;
extern float firm_cap_init_wage_offer_max;
// Starting desired employees
extern float firm_cap_init_worker_demand_mean;
extern float firm_cap_init_worker_demand_std;
extern float firm_cap_init_worker_demand_min;
extern float firm_cap_init_worker_demand_max;
// Initial good price
extern float firm_cap_init_good_price_mean;
extern float firm_cap_init_good_price_std;
extern float firm_cap_init_good_price_min;
extern float firm_cap_init_good_price_max;
// Good inventory
extern float firm_cap_init_inv_factor_mean;
extern float firm_cap_init_inv_factor_std;
extern float firm_cap_init_inv_factor_min;
extern float firm_cap_init_inv_factor_max;
// Desired inventory factor ( characteristic)
extern float firm_cap_init_target_inv_factor_mean;
extern float firm_cap_init_target_inv_factor_std;
extern float firm_cap_init_target_inv_factor_min;
extern float firm_cap_init_target_inv_factor_max;

// Other inits (not randomised)
extern float firm_cap_init_production_current_ratio;
extern float firm_cap_init_quantity_sold_ratio;
extern float firm_cap_init_emissions_per_unit;
extern float firm_cap_init_dividend_ratio_optimist;
extern float firm_cap_init_dividend_ratio_pessimist;

// --- Capital Firm dynamic parameters
extern float firm_cap_inv_depr_rate;
extern float firm_cap_productivity; // # units produced per worker machine pairing
extern int firm_cap_workers_per_machine;
extern int firm_cap_machine_lifespan;
extern float firm_cap_good_unit_cost;
extern float firm_cap_inv_reaction_factor;
extern float firm_cap_fixed_price_change;
extern float firm_cap_fixed_wage_change;





// --- Capital Firm randomness parameters
extern float firm_cap_rand_dividend_change;
extern float firm_cap_rand_sentiment_adoption;
extern float firm_cap_rand_desired_inventory_factor_change;
extern float firm_cap_rand_price_change_upper_limit;
extern float firm_cap_rand_wage_change;


//---------------------------------------------

//--------- Bank parameters --------------
// Bank Initialization parameters
extern float bank_init_interest_rate;

// Bank Dynamic parameters
extern float bank_inflation_reaction;
extern float bank_inflation_target; // yearly inflation target
extern float bank_inflation_target_monthly; // monthly inflation target
extern float bank_risk_premium; // added yearly interest rate to charge per leverage ratio above threshold
extern int bank_short_term_loan_length;
extern int bank_long_term_loan_length;
extern float bank_leverage_ratio_lower_threshold;
extern float bank_leverage_ratio_upper_threshold;
extern float bank_max_interest_rate;
extern float bank_max_interest_rate_change;

//---------------------------------------------

// --- CO2 Metrics parameters
// CO2 Emission sensitivites initialization for households
extern float emission_sensitivity_min;
extern float emission_sensitivity_max;
extern float emission_sensitivity_std;
extern float emission_sensitivity_threshold; 

// Bank Emission Lending Penalty Parameters
extern float bank_emission_penalty_max;
extern bool bank_total_emission_penalty;
extern bool bank_unit_emission_penalty;
extern float bank_unit_emission_lower_thr;
extern float bank_unit_emission_upper_thr;
extern float bank_total_emission_lower_thr;
extern float bank_total_emission_upper_thr;

// -- Emission allowance parameters
// Initial allowances and unit price
extern long emission_init_total_allowance;
extern float emission_init_unit_price;
// Constant changes in allowance and unit price
extern float emission_total_allowance_change;
extern float emission_unit_price_change;

//---------------------------------------------
#endif