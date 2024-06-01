import pandas as pd
import os
import glob

# Delete files in DataLogs directory
files = glob.glob('../DataLogs/*')
for f in files:
    os.remove(f)


"""files = glob.glob('../InitializationData/*.csv')
for f in files:
    os.remove(f)
"""
def process_excel_file(filename):
    xls = pd.read_excel(filename, sheet_name=None, engine='openpyxl')

    for sheet_name, data in xls.items():
        print("Now working on sheet name: ", sheet_name)
        if sheet_name != "Consumer_Firm_Sectors":
            # Remove rows with missing values in the second column
            data = data.dropna(subset=[data.columns[1]])
            data = data[pd.to_numeric(data.iloc[:, 1], errors='coerce').notnull()] # Keep only rows with numeric values in the second column
            data.to_csv(f"../InitializationData/{sheet_name}.csv", index=False, header=False)
        else:
            data.iloc[:, 0] = data.iloc[:, 0].str.replace(' ', '_') # Replace spaces with underscores
            data.to_csv(f"../InitializationData/{sheet_name}.csv", index=False)
            
def process_excel_file_init(filename):
    xls = pd.read_excel(filename, sheet_name=None, engine='openpyxl')

    for sheet_name, data in xls.items():
        print("Now working on sheet name: ", sheet_name)
        if sheet_name != "Consumer_Firm_Sectors":
            # Remove rows with missing values in the second column
            data = data.dropna(subset=[data.columns[1]])
            data = data[pd.to_numeric(data.iloc[:, 1], errors='coerce').notnull()] # Keep only rows with numeric values in the second column
            data.to_csv(f"../InitializationData/{sheet_name}_init.csv", index=False, header=False)
        else:
            data.iloc[:, 0] = data.iloc[:, 0].str.replace(' ', '_') # Replace spaces with underscores
            data.to_csv(f"../InitializationData/{sheet_name}_init.csv", index=False)
        
 
process_excel_file("../InitializationData/Simulation_Parameters_main.xlsm")

print("INITIALIZEDDDDDDD")