import numpy as np 
from scipy.stats import gaussian_kde
from parameter_change import set_parameters
import matplotlib.pyplot as plt

def multiply_list(L):
    product = 1
    for x in L:
        product = product * x
    return product


def Likelihood(Y1, Y2, Y1_emp, Y2_emp, Theta):
    M = np.shape(Y1)[2]  
    S = np.shape(Y1)[0] 
    T = np.shape(Y1)[1]  
    
    likelihoods = np.zeros((S, M, 2))
    
    Y1_emp_joint = np.vstack((Y1_emp[:-1], Y1_emp[1:]))
    Y2_emp_joint = np.vstack((Y2_emp[:-1], Y2_emp[1:]))
    #Y3_emp_joint = np.vstack((Y3_emp[:-1], Y3_emp[1:]))
    
    for m in range(M):
     
        stacked_array_1 = np.stack((Y1[:, :-1, m], Y2[:, :-1, m]), axis=2)*100
        stacked_array_2 = np.stack((Y1[:, 1:, m], Y2[:, 1:, m]), axis=2)*100
        
        for s in range(S):
            log_likelihoods = []
            
            for yi in range(2):
                yt_joint = []
                yt_joint.append(np.array([0.1, 0.1]))
                
                
                for t in range(1, T):
                    yt_joint.append(np.hstack((stacked_array_1[s, t-1, yi], stacked_array_2[s, t-1, yi])))
                
                yt_joint = np.array(yt_joint).T 
                print("yt", yt_joint)
                
                
                kde = gaussian_kde(yt_joint)
                
                if yi == 0:
                    kde_values = kde(Y1_emp_joint)
                elif yi == 1:
                    kde_values = kde(Y2_emp_joint)
                #else:
                    #kde_values = kde(Y3_emp_joint)
                
                kde_values = np.where(kde_values == 0, np.finfo(float).eps, kde_values)
                
                log_likelihood = np.sum(np.log(kde_values))
                log_likelihoods.append(log_likelihood)
            
            likelihoods[s, m, 0] = log_likelihoods[0]
            likelihoods[s, m, 1] = log_likelihoods[1]
    
    AVG_likelihood_1 = np.mean(likelihoods[:,:,0], axis=0)
    AVG_likelihood_2 = np.mean(likelihoods[:,:,1], axis=0)
    
    likelihood_params = [(AVG_likelihood_1[i], AVG_likelihood_2[i], Theta[i]) for i in range(M)]
    
    #plot_joint_density_Y1(Y1, Y1_emp, likelihood_params, 0, 0)
    
    return likelihood_params



def max_likelihood_params(likelihood_params):
    max_tuple_1 = max(likelihood_params, key=lambda x: x[0])
    max_tuple_2 = max(likelihood_params, key=lambda x: x[1])
    Theta_max_ll_1 = max_tuple_1[2]
    Theta_max_ll_2 = max_tuple_2[2]
    return Theta_max_ll_1, Theta_max_ll_2



def plot_joint_density_Y1(Y1, Y1_emp, likelihood_params, sample_index, model_index):

    T = Y1.shape[1]

    y1 = Y1[sample_index, :, model_index]


    y1_joint = np.vstack((y1[:-1], y1[1:])).T
    Y1_emp_joint = np.vstack((Y1_emp[:-1], Y1_emp[1:])).T

    kde_y1 = gaussian_kde(y1_joint.T)

    x_min, x_max = y1.min(), y1.max()
    y_min, y_max = y1.min(), y1.max()

    x_grid, y_grid = np.mgrid[x_min:x_max:100j, y_min:y_max:100j]
    grid_coords = np.vstack([x_grid.ravel(), y_grid.ravel()])

    z1 = np.reshape(kde_y1(grid_coords), x_grid.shape)

    plt.figure(figsize=(10, 8))
    plt.imshow(np.rot90(z1), extent=[x_min, x_max, y_min, y_max], cmap='viridis')
    plt.plot(y1[:-1], y1[1:], 'k.', markersize=8, markerfacecolor='white', markeredgecolor='black')
    plt.title(f'Joint Density of Y1 (Sample {sample_index}, Model {model_index})')
    plt.xlabel('Y1(t-1)')
    plt.ylabel('Y1(t)')

    avg_likelihood, theta_param = likelihood_params[model_index]


    plt.colorbar(label='Density')
    plt.show()

