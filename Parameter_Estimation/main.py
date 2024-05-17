import os
import numpy as np
import multiprocessing
from Parameter_Estimation.parameter_change import change_parameters, initialize_parameters
from Parameter_Estimation.model_simulation import run_model_simulation
from InitializationData.Initialization_Data_Prep import process_excel_file, delete_logs
from Parameter_Estimation.model_data import data_study

def setup_environment():
    # Change directory within Python's environment
    os.chdir("/Users/ayman/Desktop/FYP_project/Vulcan/src")
    os.system("make")
    # Optionally, change back if needed
    os.chdir("/Users/ayman/Desktop/FYP_project/Vulcan")
    print("MAKEMAKEMAKE")
    initialize_parameters()
    
# Define lock globally
lock = multiprocessing.Lock()

def run_simulation(m, s):
    global lock
    # Avoid different processes trying to access the excel file at the same time
    lock.acquire()
    try:
        change_parameters(m, s)
        process_excel_file("/Users/ayman/Desktop/FYP_project/Vulcan/Parameter_Estimation/Simulation_Parameters_main.xlsx", m, s, "/Users/ayman/Desktop/FYP_project/Vulcan/InitializationData")
    finally:
        lock.release()
        
    run_model_simulation()
    print("RUN")
    
    data = data_study(m, s)
    return m, s, *data

def main():
    setup_environment()
    delete_logs()

    M, S = 2, 2  # number of models, number of scenarios
    number_of_processes = multiprocessing.cpu_count()

    with multiprocessing.Pool(processes=number_of_processes) as pool:
        results = pool.starmap(run_simulation, [(m, s) for m in range(M) for s in range(S)])

    # Example of data processing
    for result in results:
        m, s, unemployment_rate, consumer_inflation, GDP_growth_nominal, GDP_growth_real = result
        print(f"Model {m}, Scenario {s}, Unemployment Rate: {unemployment_rate}")

if __name__ == '__main__':
    main()

    


"""def plot_data(X, Y_data, title):
    fig, ax = plt.subplots()
    for s in range(np.shape(Y_data)[2]):
        for m in range(np.shape(Y_data)[0]):
            ax.plot(X, Y_data[m, :, s], label='s = %s')
            ax.legend() 
            ax.set_title(title)
            ax.set_xlabel('Time')
            ax.set_ylabel('Value')
        
Time = np.arange(51, 201)

plot_data(Time, Y_unemployment_rate, "Unemployment Rate Over Time")
plot_data(Time, Y_consumer_inflation, "Consumer Inflation Over Time")
plot_data(Time, Y_GDP_growth_nominal, "Nominal GDP Growth Over Time")
plot_data(Time, Y_GDP_growth_real, "Real GDP Growth Over Time")


plt.show()"""