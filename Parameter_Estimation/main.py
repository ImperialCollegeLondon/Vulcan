import os 
import numpy as np
import parameter_change
import model_data
import matplotlib.pyplot as plt
import pandas as pd
import Empirical_Data 
from Likelihood_Estimation import Likelihood, max_likelihood_params
from data_plotting import plot_data_3D, plot_data

UK_Consumer_Inflation_Empirical = Empirical_Data.UK_Empirical_Data("Consumer_Inflation")
UK_GDP_Growth_Empirical = Empirical_Data.UK_Empirical_Data("GDP_growth_nominal")
UK_Unemployment_Rate_Empirical = Empirical_Data.UK_Empirical_Data("Unemployment_Rate")
os.system("python3 /Users/ayman/Desktop/FYP_project/Vulcan/Parameter_Estimation/parameter_change.py")

os.system('cd /Users/ayman/Desktop/FYP_project/Vulcan/src')   
os.system("make")

S = 10
M = 20
t0 = 20
T = 80
Theta = np.zeros((M, 29))

Y_unemployment_rate = np.zeros((S,T-t0,M))
Y_consumer_inflation = np.zeros((S,T-t0,M))
Y_GDP_growth_nominal  = np.zeros((S,T-t0,M))

for m in range(M):
    
    for s in range(S):
    
        os.system('python3 /Users/ayman/Desktop/FYP_project/Vulcan/InitializationData/Initialization_Data_Prep.py')
        os.system('python3 /Users/ayman/Desktop/FYP_project/Vulcan/Parameter_Estimation/model_simulation.py')
        
        unemployment_rate, consumer_inflation, GDP_growth_nominal= model_data.data_study()
        
        Y_unemployment_rate[s,:,m] = unemployment_rate.tail(T-t0).values
        Y_consumer_inflation[s,:,m] = consumer_inflation.tail(T-t0).values
        Y_GDP_growth_nominal[s,:,m] = GDP_growth_nominal.tail(T-t0).values
        
        print(m, s)
        
    params = parameter_change.change_parameters()
    Theta[m,:] = params
    
    
likelihood_params = Likelihood(Y_consumer_inflation, Y_unemployment_rate, Y_GDP_growth_nominal, UK_Consumer_Inflation_Empirical, UK_GDP_Growth_Empirical, UK_Unemployment_Rate_Empirical, Theta)
Theta_max_likelihood = max_likelihood_params(likelihood_params)
max_likelihood_params(likelihood_params)

os.system('python3 /Users/ayman/Desktop/FYP_project/Vulcan/InitializationData/Initialization_Data_Prep.py')
os.system('python3 /Users/ayman/Desktop/FYP_project/Vulcan/Parameter_Estimation/model_simulation.py')
unemployment_rate, consumer_inflation, GDP_growth_nominal= model_data.data_study()
        
Y_unemployment_rate_max_ll = unemployment_rate.tail(T-t0).values
Y_consumer_inflation_max_ll = consumer_inflation.tail(T-t0).values
Y_GDP_growth_nominal_max_ll = GDP_growth_nominal.tail(T-t0).values      
        
Time = np.arange(21, 81)

plot_data(Time, Y_unemployment_rate_max_ll, UK_Unemployment_Rate_Empirical, "Unemployment Rate Over Time")
plot_data(Time, Y_consumer_inflation_max_ll, UK_Consumer_Inflation_Empirical, "Consumer Inflation Over Time")
plot_data(Time, Y_GDP_growth_nominal_max_ll, UK_GDP_Growth_Empirical, "Nominal GDP Growth Over Time")

"""plot_data_3D(Time, Y_unemployment_rate_max_ll, "Unemployment Rate Over Time", M, S)
plot_data_3D(Time, Y_consumer_inflation_max_ll, "Consumer Inflation Over Time", M, S)
plot_data_3D(Time, Y_GDP_growth_nominal_max_ll, "Nominal GDP Growth Over Time", M, S)"""

plt.show()