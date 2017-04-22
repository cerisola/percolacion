import importlib
import numpy as np
from scipy.stats import linregress
import matplotlib.pyplot as plt
import load_data
import common
import clusters
importlib.reload(load_data)
importlib.reload(common)
importlib.reload(clusters)


def fit_beta_percolating_cluster_strength(size, count, percolated, L, p_occupation):
    strength = clusters.percolating_cluster_strength_list(size, percolated, L)
    idx_positive = np.where(strength > 0)[0]
    idx_min = 0
    idx_max = 30
    slope, intercept, _, _, std_err = linregress(np.log(p_occupation[idx_positive][idx_min:idx_max]),
                                                 np.log(strength[idx_positive][idx_min:idx_max]))
    expected = slope*np.log(p_occupation[idx_positive][idx_min:idx_max]) + intercept
    ddof = strength[idx_positive][idx_min:idx_max].size - 2
    chi2 = np.sum((np.log(strength[idx_positive][idx_min:idx_max]) - expected)**2)/ddof
    return slope, intercept, std_err, chi2


def plot_percolating_cluster_strength(size, count, percolated, L, p_occupation):
    strength = clusters.percolating_cluster_strength_list(size, percolated, L)
    plt.figure()
    plt.title('Percolating cluster strength for L = {}'.format(L[0]))
    plt.plot(p_occupation, strength, 'o', markersize=2.0)
    plt.grid()
    plt.xlabel('$p$')
    plt.ylabel('$P_{\infty}$')
    plt.show()

    idx_positive = np.where(strength > 0)[0]
    plt.figure()
    plt.title('Percolating cluster strength for L = {} (log scale)'.format(L[0]))
    plt.loglog(p_occupation[idx_positive], strength[idx_positive], 'o', markersize=2.0)
    plt.grid()
    plt.xlabel('$p$')
    plt.ylabel('$P_{\infty}$')
    plt.show()


def plot_beta_fit(size, count, percolated, L, p_occupation):
    strength = clusters.percolating_cluster_strength_list(size, percolated, L)
    slope, intercept, _, _ = fit_beta_percolating_cluster_strength(size, count, percolated, L, p_occupation)
    idx_positive = np.where(strength > 0)
    plt.figure()
    plt.title('$\\beta$ fit for L = {} [$beta$ = {:.2f}]'.format(L[0], slope))
    plt.loglog(p_occupation[idx_positive], strength[idx_positive], 'o', markersize=2.0, label='observations')
    plt.loglog(p_occupation[idx_positive], np.exp(intercept)*p_occupation[idx_positive]**slope, '-', label='fit')
    plt.grid()
    plt.xlabel('$p$')
    plt.ylabel('$P_{\infty}$')
    plt.ylim((0, 1.1*np.max(strength[idx_positive])))
    plt.show()


save_figures = False

if not save_figures:
    plt.ion()

L = 512
files_root_prefix = 'print/data/probability_sweep/v5/'
files = load_data.get_cluster_statistics_file_list(files_root_prefix, L=L)
size, count, percolated, L, p_occupation, _ = load_data.load_cluster_statistics_file_list(files)
plot_percolating_cluster_strength(size, count, percolated, L, p_occupation)
plot_beta_fit(size, count, percolated, L, p_occupation)

if not save_figures:
    plt.ioff()
