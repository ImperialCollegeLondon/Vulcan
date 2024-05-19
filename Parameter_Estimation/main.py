import os 
import numpy as np
import parameter_change
import model_data
import matplotlib.pyplot as plt

os.system("python3 /Users/ayman/Desktop/FYP_project/Vulcan/Parameter_Estimation/parameter_change.py")

os.system('cd /Users/ayman/Desktop/FYP_project/Vulcan/src')   
os.system("make")

initialization_parameters = {}
main_loop_parameters = {}
randomness_parameters = {}

S = 3
M = 5
t0 = 50
T = 150

Y_unemployment_rate = np.zeros((S,T,M))
Y_consumer_inflation = np.zeros((S,T,M))
Y_GDP_growth_nominal  = np.zeros((S,T,M))
Y_GDP_growth_real = np.zeros((S,T,M))

for m in range(M):
    
    for s in range(S):
    
        os.system('python3 /Users/ayman/Desktop/FYP_project/Vulcan/InitializationData/Initialization_Data_Prep.py')
        os.system('python3 /Users/ayman/Desktop/FYP_project/Vulcan/Parameter_Estimation/model_simulation.py')
        
        unemployment_rate, consumer_inflation, GDP_growth_nominal, GDP_growth_real = model_data.data_study()
        
        Y_unemployment_rate[s,:,m] = unemployment_rate.tail(T).values
        Y_consumer_inflation[s,:,m] = consumer_inflation.tail(T).values
        Y_GDP_growth_nominal[s,:,m] = GDP_growth_nominal.tail(T).values
        Y_GDP_growth_real [s,:,m] = GDP_growth_real.tail(T).values
        
        print(m, s)
        
    parameter_change.change_parameters()
    
print(np.shape(Y_GDP_growth_real))



def plot_data(X, Y_data, title):
    fig, ax = plt.subplots()
    for m in range(M):
        for s in range(S):
            ax.plot(X, Y_data[s, :, m])
            ax.set_title(title)
            ax.set_xlabel('Time')
            ax.set_ylabel('Value')
        
Time = np.arange(51, 201)

plot_data(Time, Y_unemployment_rate, "Unemployment Rate Over Time")
plot_data(Time, Y_consumer_inflation, "Consumer Inflation Over Time")
plot_data(Time, Y_GDP_growth_nominal, "Nominal GDP Growth Over Time")
plot_data(Time, Y_GDP_growth_real, "Real GDP Growth Over Time")

plt.show()