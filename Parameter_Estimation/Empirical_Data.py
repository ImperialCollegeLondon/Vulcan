import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def interpolate(df):
    original_index = np.arange(len(df))
    new_index = np.linspace(0, len(df) - 1, 2 * len(df) - 1)
    interpolated_series = np.interp(new_index, original_index, df['Value'])
    df_interpolated = pd.DataFrame(interpolated_series, columns=['Value'])
    return df_interpolated

def UK_Empirical_Data(filename):
    df = pd.read_csv(f'../Parameter_Estimation/DATA/{filename}.csv')
    Empirical = df[df['Country Name'] == 'United Kingdom']
    Empirical = Empirical.drop(columns=['Country Name', 'Country Code', 'Indicator Name', 'Indicator Code'])
    Empirical = Empirical.melt(var_name='Year', value_name='Value')
    Empirical = Empirical.dropna()
    if filename == "Unemployment_Rate":
        Empirical = interpolate(Empirical)
    Empirical = Empirical.tail(60)
    Empirical.to_csv(f'../Parameter_Estimation/DATA/UK_{filename}_Empirical.csv', index=False)
    print(filename, pd.read_csv(f'../Parameter_Estimation/DATA/UK_{filename}_Empirical.csv').shape)
    return Empirical['Value'].values
    

"""df = UK_Empirical_Data("Unemployment_Rate")
df = UK_Empirical_Data("Consumer_Inflation")
df = UK_Empirical_Data("GDP_growth_nominal")"""



