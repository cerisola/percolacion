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


def fit_cluster_size_density(size, count, L):
    density = clusters.cluster_densities(count, L)

    #idx_min = np.argmax(size > 6)
    #idx_max = np.argmax(density < 100)
    idx_min = np.argmax(size > 0)
    idx_max = np.argmax(size > L*0.5)
    if (idx_max - idx_min) < 3:
        idx_min = 0
        idx_max = 10
        if idx_max > size.size:
            return np.nan, np.nan, np.nan, np.nan
    slope, intercept, _, _, std_err = linregress(np.log(size[idx_min:idx_max]),
                                                 np.log(density[idx_min:idx_max]))
    expected = slope*np.log(size) + intercept
    idx_expected_max = size.size-1#idx_max
    ddof = size[0:idx_expected_max].size - 2
    chi2 = np.sum((np.log(density[0:idx_expected_max]) - expected[0:idx_expected_max])**2)/ddof
    return slope, intercept, std_err, chi2


def fit_cluster_size_density_list(size, count, L, p_occupation, p_occupation_min=0.3, p_occupation_max=0.7):
    data = [fit_cluster_size_density(size[i], count[i], L[i])
           if p_occupation[i] > p_occupation_min and p_occupation[i] < p_occupation_max
           else (np.nan, np.nan, np.nan, np.nan) for i in range(p_occupation.size)]
    slope = np.array([d[0] for d in data])
    intercept = np.array([d[1] for d in data])
    stderr = np.array([d[2] for d in data])
    chi2 = np.array([d[3] for d in data])
    return slope, intercept, stderr, chi2


def plot_cluster_size_density(size, count, L, p_occupation, plot_fit=True):
    density = clusters.cluster_densities(count, L)
    plt.figure()
    plt.title('Cluster size density for L = {}, p = {:.3f}'.format(L, p_occupation))
    plt.loglog(size, density, '-o', markersize=3.0, linewidth=0.8, label='observations')
    if plot_fit:
        slope, intercept, _, _ = fit_cluster_size_density(size, count, L)
        plt.loglog(size, np.exp(intercept)*size**slope, '--', label='power law fit')
    plt.grid()
    plt.xlabel('s')
    plt.ylabel('$n_s(p)$')
    plt.legend()
    plt.show()


def plot_cluster_size_density_list_chi2(size, count, L, p_occupation, plot_fit_results=True):
    slope, intercept, _, chi2 = fit_cluster_size_density_list(size, count, L, p_occupation)
    plt.figure()
    plt.title('$\chi^2$ test for L = {}'.format(L[0]))
    plt.semilogy(p_occupation, chi2, 'o', markersize=3.0)
    plt.grid()
    plt.ylabel('$\chi^2$')
    plt.xlabel('$p$')
    plt.legend()
    plt.show()

    if plot_fit_results:
        plt.figure()
        plt.title('$\\tau$ fits for L = {}'.format(L[0]))
        plt.plot(p_occupation, slope, 'o', markersize=3.0)
        plt.grid()
        plt.ylabel('$\\tau$')
        plt.xlabel('$p$')
        plt.legend()
        plt.show()

        plt.figure()
        plt.title('intercept fits for L = {}'.format(L[0]))
        plt.plot(p_occupation, intercept, 'o', markersize=3.0)
        plt.grid()
        plt.ylabel('intercept')
        plt.xlabel('$p$')
        plt.legend()
        plt.show()


save_figures = False

if not save_figures:
    plt.ion()

L = 64
files_root_prefix = 'print/data/probability_sweep/v5/'
files = load_data.get_cluster_statistics_file_list(files_root_prefix, L=L)
for idx in [120, 240, 360, 480, 600, 720]:
    size, count, _, L, p_occupation = load_data.load_cluster_statistics_file(files[idx])
    plot_cluster_size_density(size, count, L, p_occupation)
size, count, _, L, p_occupation = load_data.load_cluster_statistics_file_list(files)
plot_cluster_size_density_list_chi2(size, count, L, p_occupation, True)

if not save_figures:
    plt.ioff()
