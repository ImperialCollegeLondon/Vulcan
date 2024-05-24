import numpy as np 
from scipy.stats import gaussian_kde
from parameter_change import set_parameters

def multiply_list(L):
    product = 1
    for x in L:
        product = product * x
    return product

def Likelihood(Y1, Y2, Y3, Y1_emp, Y2_emp, Y3_emp, Theta):
    M = np.shape(Y1)[2]
    S = np.shape(Y1)[0]
    T = np.shape(Y1)[1]

    
    likelihoods = np.zeros((S,M))
    
    empirical_stacked_array = np.vstack((Y1_emp, Y2_emp, Y3_emp))

    for m in range(M):
        stacked_array = np.stack((Y1[:,:,m], Y2[:,:,m], Y3[:,:,m]), axis=2)
        
        
        for s in range(S):
            
            kde_values = []
            yt = stacked_array[s, :, :]
            kde_values.append(yt)
        
            kde_values = np.array(kde_values).T
            kde_values = np.squeeze(kde_values) 
            kde = gaussian_kde(kde_values)

            kde_values = kde.evaluate(empirical_stacked_array)
            kde_values = np.where(kde_values == 0, np.finfo(float).eps, kde_values)
            log_likelihood = np.sum(np.log(kde_values))
            likelihoods[s, m] = log_likelihood
    
    AVG_likelihood = np.mean(likelihoods, axis=0)
    
    likelihood_params = []
    
    for i in range(M):
        likelihood_params.append((AVG_likelihood[i], Theta[i]))

    return likelihood_params
    

def max_likelihood_params(likelihood_params):
    max_tuple = max(likelihood_params, key=lambda x: x[0])
    Theta_max_ll = max_tuple[1]
    set_parameters(Theta_max_ll)
    
    
    