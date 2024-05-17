import pandas as pd
import os
import glob
from csv import writer

# Delete files in DataLogs directory
def delete_logs():  
    files = glob.glob('../DataLogs/*')
    for f in files:
        os.remove(f)

def process_excel_file(filename, m, s, directory):
    xls = pd.read_excel(filename, sheet_name=None, engine='openpyxl')

    for sheet_name, data in xls.items():
        print("Now working on sheet name: ", sheet_name)
        
        # Ensure directory exists
        os.makedirs(directory, exist_ok=True)
        
        # Define the path for the CSV file
        if sheet_name != "Consumer_Firm_Sectors":
            # Remove rows with missing values in the second column
            data = data.dropna(subset=[data.columns[1]])
            data = data[pd.to_numeric(data.iloc[:, 1], errors='coerce').notnull()] # Keep only rows with numeric values in the second column
            csv_path = os.path.join(directory, f"{sheet_name}_{m}_{s}.csv")
            data.to_csv(csv_path, index=False, header=False)
        else:
            data.iloc[:, 0] = data.iloc[:, 0].str.replace(' ', '_') # Replace spaces with underscores
            csv_path = os.path.join(directory, f"{sheet_name}_{m}_{s}.csv")
            data.to_csv(csv_path, index=False)
    
    row_m = ["m", m]
    row_s = ["s", s]     
    with open('Initialization_Parameters.csv', 'a') as f_object:
        writer_object = writer(f_object)
        writer_object.writerow(row_m)
        writer_object.writerow(row_s)
        f_object.close()


def process_excel_file_initial(filename, directory):
    xls = pd.read_excel(filename, sheet_name=None, engine='openpyxl')

    for sheet_name, data in xls.items():
        print("Now working on sheet name: ", sheet_name)
        
        # Ensure directory exists
        os.makedirs(directory, exist_ok=True)
        
        # Define the path for the CSV file
        if sheet_name != "Consumer_Firm_Sectors":
            # Remove rows with missing values in the second column
            data = data.dropna(subset=[data.columns[1]])
            data = data[pd.to_numeric(data.iloc[:, 1], errors='coerce').notnull()] # Keep only rows with numeric values in the second column
            csv_path = os.path.join(directory, f"{sheet_name}.csv")
            data.to_csv(csv_path, index=False, header=False)
        else:
            data.iloc[:, 0] = data.iloc[:, 0].str.replace(' ', '_') # Replace spaces with underscores
            csv_path = os.path.join(directory, f"{sheet_name}.csv")
            data.to_csv(csv_path, index=False)
        
"""process_excel_file("Simulation_Parameters_main.xlsx")"""