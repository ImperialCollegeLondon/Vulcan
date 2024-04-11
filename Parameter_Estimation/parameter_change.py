from openpyxl import load_workbook
import numpy as np

def read_parameters(parameter_map, filename):
    print(f"Started reading file: {filename}")

    with open(filename, 'r') as file:
        for line in file:
            # Split the line into columns using comma as the separator
            columns = line.strip().split(',')
            # Get the variable name from the first column
            var_name = columns[0]
            # Get the variable value from the second column and convert it to float
            var_value = float(columns[1])

            # Insert the variable name and value into the parameter_map dictionary
            parameter_map[var_name] = var_value

    print(f"Finished reading and closed file: {filename}")
    
initialization_parameters = {}
main_loop_parameters = {}
randomness_parameters = {}

read_parameters(initialization_parameters, '../InitializationData/Initialization_Parameters.csv')
read_parameters(main_loop_parameters, '../InitializationData/Main_Loop_Parameters.csv')
read_parameters(randomness_parameters, '../InitializationData/Randomness_Parameters.csv')

upper = 0.1
lower = 100

# Initialization Parameters
household_init_res_wage_min = initialization_parameters["household_init_res_wage_min"]
household_init_res_wage_max = initialization_parameters["household_init_res_wage_max"]

household_init_unemployment_benefit = initialization_parameters['household_init_unemployment_benefit']
household_init_unemployment_benefit_min = max(0, household_init_unemployment_benefit * upper)
household_init_unemployment_benefit_max = household_init_unemployment_benefit * lower


household_init_minimum_wage = initialization_parameters['household_init_minimum_wage']
household_init_minimum_wage_min = max(0, household_init_minimum_wage * upper)
household_init_minimum_wage_max = household_init_minimum_wage * lower

firm_cons_init_inv_factor_min = initialization_parameters["firm_cons_init_inv_factor_min"]
firm_cons_init_inv_factor_max = initialization_parameters["firm_cons_init_inv_factor_max"]

firm_cons_init_target_inv_factor_min = initialization_parameters["firm_cons_init_target_inv_factor_min"]
firm_cons_init_target_inv_factor_max = initialization_parameters["firm_cons_init_target_inv_factor_max"]

firm_cons_init_production_current_ratio = initialization_parameters["firm_cons_init_production_current_ratio"]
firm_cons_init_production_current_ratio_min = max(0, firm_cons_init_production_current_ratio * upper)
firm_cons_init_production_current_ratio_max = firm_cons_init_production_current_ratio * lower

firm_cons_init_quantity_sold_ratio = initialization_parameters["firm_cons_init_production_current_ratio"]
firm_cons_init_quantity_sold_ratio_min = max(0, firm_cons_init_quantity_sold_ratio * upper)
firm_cons_init_quantity_sold_ratio_max = firm_cons_init_quantity_sold_ratio * lower

firm_cap_init_inv_factor_min = initialization_parameters["firm_cap_init_inv_factor_min"]
firm_cap_init_inv_factor_max = initialization_parameters["firm_cap_init_inv_factor_max"]

firm_cap_init_target_inv_factor_min = initialization_parameters["firm_cap_init_target_inv_factor_min"]
firm_cap_init_target_inv_factor_max = initialization_parameters["firm_cap_init_target_inv_factor_max"]

firm_cap_init_production_current_ratio = initialization_parameters["firm_cap_init_production_current_ratio"]
firm_cap_init_production_current_ratio_min = max(0, firm_cap_init_production_current_ratio * upper)
firm_cap_init_production_current_ratio_max = firm_cap_init_production_current_ratio * lower

firm_cap_init_quantity_sold_ratio = initialization_parameters["firm_cap_init_quantity_sold_ratio"]
firm_cap_init_quantity_sold_ratio_min = max(0, firm_cap_init_quantity_sold_ratio * upper)
firm_cap_init_quantity_sold_ratio_max = firm_cap_init_quantity_sold_ratio * lower


# Main Loop Parameters
household_targeted_savings_to_income_ratio = main_loop_parameters['household_targeted_savings_to_income_ratio']
household_targeted_savings_to_income_ratio_min = max(0, household_targeted_savings_to_income_ratio * upper)
household_targeted_savings_to_income_ratio_max = household_targeted_savings_to_income_ratio * lower

firm_cons_inv_depr_rate = main_loop_parameters['firm_cons_inv_depr_rate']
firm_cons_inv_depr_rate_min = max(0, firm_cons_inv_depr_rate * upper)
firm_cons_inv_depr_rate_max = firm_cons_inv_depr_rate * lower

firm_cons_productivity = main_loop_parameters['firm_cons_productivity']
firm_cons_productivity_min = max(0, firm_cons_productivity * upper)
firm_cons_productivity_max = firm_cons_productivity * lower

firm_cons_workers_per_machine = main_loop_parameters['firm_cons_workers_per_machine']
firm_cons_workers_per_machine_min = max(0, firm_cons_workers_per_machine * upper)
firm_cons_workers_per_machine_max = firm_cons_workers_per_machine * lower

firm_cons_inv_reaction_factor = main_loop_parameters['firm_cons_inv_reaction_factor']
firm_cons_inv_reaction_factor_min = max(0, firm_cons_inv_reaction_factor * upper)
firm_cons_inv_reaction_factor_max = firm_cons_inv_reaction_factor * lower

firm_cap_inv_depr_rate = main_loop_parameters['firm_cap_inv_depr_rate']
firm_cap_inv_depr_rate_min = max(0, firm_cap_inv_depr_rate * upper)
firm_cap_inv_depr_rate_max = firm_cap_inv_depr_rate * lower

firm_cap_productivity = main_loop_parameters['firm_cap_productivity']
firm_cap_productivity_min = max(0, firm_cap_productivity * upper)
firm_cap_productivity_max = firm_cap_productivity * lower

firm_cap_workers_per_machine = main_loop_parameters['firm_cap_workers_per_machine']
firm_cap_workers_per_machine_min = max(0, firm_cap_workers_per_machine * upper)
firm_cap_workers_per_machine_max = firm_cap_workers_per_machine * lower

firm_cap_inv_reaction_factor = main_loop_parameters['firm_cap_inv_reaction_factor']
firm_cap_inv_reaction_factor_min = max(0, firm_cap_inv_reaction_factor * upper)
firm_cap_inv_reaction_factor_max = firm_cap_inv_reaction_factor * lower

bank_inflation_reaction = main_loop_parameters['bank_inflation_reaction']
bank_inflation_reaction_min = max(0, bank_inflation_reaction * upper)
bank_inflation_reaction_max = bank_inflation_reaction * lower

bank_inflation_target = main_loop_parameters['bank_inflation_target']
bank_inflation_target_min = max(0, bank_inflation_target * upper)
bank_inflation_target_max = bank_inflation_target * lower

bank_inflation_target_monthly = main_loop_parameters['bank_inflation_target_monthly']
bank_inflation_target_monthly_min = max(0, bank_inflation_target_monthly * upper)
bank_inflation_target_monthly_max = bank_inflation_target_monthly * lower

bank_risk_premium = main_loop_parameters['bank_risk_premium']
bank_risk_premium_min = max(0, bank_risk_premium * upper)
bank_risk_premium_max = bank_risk_premium * lower

bank_max_interest_rate = main_loop_parameters['bank_max_interest_rate']
bank_max_interest_rate_min = max(0, bank_max_interest_rate * upper)
bank_max_interest_rate_max = bank_max_interest_rate * lower

# Randomness Parameters
firm_cons_rand_desired_inventory_factor_change = randomness_parameters["firm_cons_rand_desired_inventory_factor_change"]
firm_cons_rand_desired_inventory_factor_change_min = max(0, firm_cons_rand_desired_inventory_factor_change * upper)
firm_cons_rand_desired_inventory_factor_change_max = firm_cons_rand_desired_inventory_factor_change * lower

firm_cons_rand_wage_change = randomness_parameters["firm_cons_rand_wage_change"]
firm_cons_rand_wage_change_min = max(0, firm_cons_rand_wage_change * upper)
firm_cons_rand_wage_change_max = firm_cons_rand_wage_change * lower

firm_cap_rand_desired_inventory_factor_change = randomness_parameters["firm_cap_rand_desired_inventory_factor_change"]
firm_cap_rand_desired_inventory_factor_change_min = max(0, firm_cap_rand_desired_inventory_factor_change * upper)
firm_cap_rand_desired_inventory_factor_change_max = firm_cap_rand_desired_inventory_factor_change * lower

firm_cap_rand_wage_change = randomness_parameters["firm_cap_rand_wage_change"]
firm_cap_rand_wage_change_min = max(0, firm_cap_rand_wage_change * upper)
firm_cap_rand_wage_change_max = firm_cap_rand_wage_change * lower


def change_parameters():

    wb = load_workbook('/Users/ayman/Desktop/FYP_project/Vulcan/InitializationData/Simulation_Parameters_main.xlsx')

    Initialization_Parameters_wb = wb['Initialization_Parameters']
    Main_Loop_Parameters_wb = wb['Main_Loop_Parameters']
    Randomness_Parameters_wb = wb['Randomness_Parameters']

    Initialization_Parameters_wb.cell(row=29, column=2).value = str(np.random.uniform(household_init_res_wage_min, household_init_res_wage_max,1)) # household_init_res_wage_mean
    print(str(np.random.uniform(household_init_res_wage_min, household_init_res_wage_max,1)), np.random.uniform(household_init_res_wage_min, household_init_res_wage_max,1))
    Initialization_Parameters_wb.cell(row=33, column=2).value = str(np.random.uniform(household_init_unemployment_benefit, household_init_unemployment_benefit,1)) # household_init_unemployment_benefit
    Initialization_Parameters_wb.cell(row=34, column=2).value = str(np.random.uniform(household_init_minimum_wage_min, household_init_minimum_wage_max,1)) # household_init_minimum_wage
    Initialization_Parameters_wb.cell(row=54, column=2).value = str(np.random.uniform(firm_cons_init_inv_factor_min, firm_cons_init_inv_factor_max,1)) # firm_cons_init_inv_factor_mean
    Initialization_Parameters_wb.cell(row=58, column=2).value = str(np.random.uniform(firm_cons_init_target_inv_factor_min, firm_cons_init_target_inv_factor_max,1)) # firm_cons_init_target_inv_factor_mean
    Initialization_Parameters_wb.cell(row=62, column=2).value = str(np.random.uniform(firm_cons_init_production_current_ratio_min, firm_cons_init_production_current_ratio_max,1)) # firm_cons_init_production_current_ratio
    Initialization_Parameters_wb.cell(row=63, column=2).value = str(np.random.uniform(firm_cons_init_quantity_sold_ratio_min, firm_cons_init_quantity_sold_ratio_max,1)) # firm_cons_init_quantity_sold_ratio
    Initialization_Parameters_wb.cell(row=84, column=2).value = str(np.random.uniform(firm_cap_init_inv_factor_min, firm_cap_init_inv_factor_max,1)) # firm_cap_init_inv_factor_mean
    Initialization_Parameters_wb.cell(row=88, column=2).value = str(np.random.uniform(firm_cap_init_target_inv_factor_min, firm_cap_init_target_inv_factor_max,1)) # firm_cap_init_target_inv_factor_mean
    Initialization_Parameters_wb.cell(row=92, column=2).value = str(np.random.uniform(firm_cap_init_production_current_ratio_min, firm_cap_init_production_current_ratio_max,1)) # firm_cap_init_production_current_ratio
    Initialization_Parameters_wb.cell(row=93, column=2).value = str(np.random.uniform(firm_cap_init_quantity_sold_ratio_min, firm_cap_init_quantity_sold_ratio_max,1)) # firm_cap_init_quantity_sold_ratio
    
    Main_Loop_Parameters_wb.cell(row=11, column=2).value = str(np.random.uniform(household_targeted_savings_to_income_ratio_min, household_targeted_savings_to_income_ratio_max,1)) # household_targeted_savings_to_income_ratio
    Main_Loop_Parameters_wb.cell(row=15, column=2).value = str(np.random.uniform(firm_cons_inv_depr_rate_min, firm_cons_inv_depr_rate_max,1)) # firm_cons_inv_depr_rate
    Main_Loop_Parameters_wb.cell(row=16, column=2).value = str(np.random.uniform(firm_cons_productivity_min, firm_cons_productivity_max,1)) # firm_cons_productivity
    Main_Loop_Parameters_wb.cell(row=17, column=2).value = str(np.random.uniform(firm_cons_workers_per_machine_min, firm_cons_workers_per_machine_max,1)) # firm_cons_workers_per_machine
    Main_Loop_Parameters_wb.cell(row=19, column=2).value = str(np.random.uniform(firm_cons_inv_reaction_factor_min, firm_cons_inv_reaction_factor_max,1)) # firm_cons_inv_reaction_factor
    Main_Loop_Parameters_wb.cell(row=23, column=2).value = str(np.random.uniform(firm_cap_inv_depr_rate_min, firm_cap_inv_depr_rate_max,1)) # firm_cap_inv_depr_rate
    Main_Loop_Parameters_wb.cell(row=24, column=2).value = str(np.random.uniform(firm_cap_productivity_min, firm_cap_productivity_max,1)) # firm_cap_productivity
    Main_Loop_Parameters_wb.cell(row=25, column=2).value = str(np.random.uniform(firm_cap_workers_per_machine_min, firm_cap_workers_per_machine_max,1)) # firm_cap_workers_per_machine
    Main_Loop_Parameters_wb.cell(row=28, column=2).value = str(np.random.uniform(firm_cap_inv_reaction_factor_min, firm_cap_inv_reaction_factor_max,1)) # firm_cap_inv_reaction_factor
    Main_Loop_Parameters_wb.cell(row=32, column=2).value = str(np.random.uniform(bank_inflation_reaction_min, bank_inflation_reaction_max,1)) # bank_inflation_reaction
    Main_Loop_Parameters_wb.cell(row=33, column=2).value = str(np.random.uniform(bank_inflation_target_min, bank_inflation_target_max,1)) # bank_inflation_target
    Main_Loop_Parameters_wb.cell(row=34, column=2).value = str(np.random.uniform(bank_inflation_target_monthly_min, bank_inflation_target_monthly_max,1)) # bank_inflation_target_monthly
    Main_Loop_Parameters_wb.cell(row=35, column=2).value = str(np.random.uniform(bank_risk_premium_min, bank_risk_premium_max,1)) # bank_risk_premium
    Main_Loop_Parameters_wb.cell(row=40, column=2).value = str(np.random.uniform(bank_max_interest_rate_min, bank_max_interest_rate_max,1)) # bank_max_interest_rate

    Randomness_Parameters_wb.cell(row=10, column=2).value = str(np.random.uniform(firm_cons_rand_desired_inventory_factor_change_min, firm_cons_rand_desired_inventory_factor_change_max,1)) # firm_cons_rand_desired_inventory_factor_change
    Randomness_Parameters_wb.cell(row=12, column=2).value = str(np.random.uniform(firm_cons_rand_wage_change_min, firm_cons_rand_wage_change_max,1)) # firm_cons_rand_wage_change
    Randomness_Parameters_wb.cell(row=16, column=2).value = str(np.random.uniform(firm_cap_rand_desired_inventory_factor_change_min, firm_cap_rand_desired_inventory_factor_change_max,1)) # firm_cap_rand_desired_inventory_factor_change
    Randomness_Parameters_wb.cell(row=18, column=2).value = str(np.random.uniform(firm_cap_rand_wage_change_min, firm_cap_rand_wage_change_max,1)) # firm_cap_rand_wage_change
    

    wb.save('/Users/ayman/Desktop/FYP_project/Vulcan/InitializationData/Simulation_Parameters_main.xlsx')