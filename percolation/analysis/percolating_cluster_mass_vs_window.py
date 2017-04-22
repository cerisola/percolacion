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


def fit_tau_percolating_cluster_density(size, count, L, percolated):
    density = clusters.percolating_cluster_density_list(size, percolated, L)
    #idx_min = 0
    #idx_max = idx_min + 5
    idx_max = L.size - 5
    idx_min = idx_max - 15
    slope, intercept, _, _, std_err = linregress(np.log(L[idx_min:idx_max]),
                                                 np.log(density[idx_min:idx_max]))
    expected = slope*np.log(L) + intercept
    ddof = L.size - 2
    chi2 = np.sum((density[idx_min:idx_max] - expected[idx_min:idx_max])**2)/ddof
    return slope, intercept, std_err, chi2


def plot_percolating_cluster_density(size, count, percolated, L, p_occupation, fit=False):
    density = clusters.percolating_cluster_density_list(size, percolated, L)
    plt.figure()
    plt.loglog(L, density, 'o', markersize=2.0, label='observations')
    if fit:
        slope, intercept, _, _ = fit_tau_percolating_cluster_density(size, count, L, percolated)
        plt.loglog(L, np.exp(intercept)*(L)**slope, '--', label='fit')
        plt.ylim((0.9*np.min(density), 1.1*np.max(density)))
        plt.title('Percolating cluster intensity for p = {:.3f} [D = {:.3f}]'.format(p_occupation[0], slope))
    else:
        plt.title('Percolating cluster intensity for p = {:.3f}'.format(p_occupation[0]))
    plt.grid()
    plt.xlabel('L')
    plt.ylabel('$\\rho$')
    plt.show()


save_figures = False

if not save_figures:
    plt.ion()

ps = ['5.94005015659441e-01', '5.95363769444837e-01', '5.93435228204981e-01',
      '6.04711615093004e-01', '6.20011576127848e-01', '6.32215979380573e-01']
p = ps[-5]
files_root_prefix = 'print/data/probability_sweep/v5/'
files = load_data.get_cluster_statistics_file_list(files_root_prefix, p_occupation=p)
size, count, percolated, L, p_occupation, _ = load_data.load_cluster_statistics_file_list(files)
plot_percolating_cluster_density(size, count, percolated, L, p_occupation, True)

if not save_figures:
    plt.ioff()
