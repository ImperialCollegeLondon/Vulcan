import numpy as np
import matplotlib.pyplot as plt

def plot_data_3D(X, Y_data, title, M, S):
    fig, ax = plt.subplots()
    for m in range(M):
        for s in range(S):
            ax.plot(X, Y_data[s, :, m])
            ax.set_title(title)
            ax.set_xlabel('Time')
            ax.set_ylabel('Value')
            
def plot_data(X, Y_data, Y_emp, title):
    fig, ax = plt.subplots()
    ax.plot(X, Y_data)
    ax.plot(X, Y_emp)
    ax.set_title(title)
    ax.set_xlabel('Time')
    ax.set_ylabel('Value')