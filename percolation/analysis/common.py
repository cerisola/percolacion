import numpy as np
import scipy.stats as stats
import scipy.integrate as integrate


Z_normal = { None: 1, '90': 1.644854, '95': 1.959964, '99': 2.575829, '99.9': 3.290527, '99.99': 3.890592 }


# % Generic % #
def mean(v):
    return np.mean(v)


def var(v):
    return np.var(v, ddof=1)


def std(v):
    return np.std(v, ddof=1)


def sem(v, ci=None):
    Z = Z_normal[ci]
    return Z*stats.sem(v)


def cdf_mean(F, x):
    return (1 - integrate.simps(y=F, x=x))


def cdf_var(F, x):
    return (2*integrate.simps(y=x*(1-F), x=x) - cdf_mean(F, x)**2)


def cdf_std(F, x):
    return np.sqrt(cdf_var(F, x))


# % Binomial Distribution Aux % #
def binomial_var(p, n):
    return n*p*(1-p)


def binomial_std(p, n):
    return np.sqrt(n*p*(1 - p))


def binomial_sem(p, n, ci=None):
    Z = Z_normal[ci]
    return Z*np.sqrt(p*(1 - p)/n)
