import importlib
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
import load_data
import common
importlib.reload(load_data)
importlib.reload(common)


def percolation_probability_statistics(p_bisection_results, ci='99.9'):
    mean = np.array([common.mean(p) for p in p_bisection_results])
    std = np.array([common.std(p) for p in p_bisection_results])
    sem = np.array([common.sem(p) for p in p_bisection_results])
    ci = np.array([common.sem(p, ci) for p in p_bisection_results])
    return mean, std, sem, ci


def plot_percolation_probability_statistics(p_bisection_results, L, ntrials, ci='99.9', ci_style='none'):
    mean, std, sem, ci = percolation_probability_statistics(p_bisection_results, ci=ci)

    plt.figure()
    if ci_style == 'errorbar':
        plt.errorbar(L, mean, yerr=ci, fmt='-o', label='mean')
    elif ci_style == 'area':
        plt.plot(L, mean, '-o', markersize=4.0, label='mean')
        plt.fill_between(L, mean + ci, mean - ci, alpha=0.5)
    else:
        plt.plot(L, mean, '-o', markersize=4.0, label='mean')
    plt.grid()
    plt.xlabel('L')
    plt.ylabel('$p_{\mathrm{avg}}$ via bisection')
    plt.legend()
    plt.show()

    plt.figure()
    plt.loglog(L, std, '-o', markersize=4.0, label='mean-std')
    plt.loglog(L, ci, '-o', markersize=4.0, label='mean-ci')
    plt.grid()
    plt.xlabel('L')
    plt.ylabel('$p_{\mathrm{avg}}$ err')
    plt.legend()
    plt.show()


def plot_bisection_search_results(p_bisection_results, L, ntrials):
    plt.figure()
    plt.title('Bisection search of $p_c$ for L = {}, avg over {} trials'.format(L, ntrials))
    plt.plot(p_bisection_results, 'o', markersize=2.0)
    plt.grid()
    plt.xlabel('iter')
    plt.ylabel('p')
    plt.show()


def plot_bisection_search_histogram(p_bisection_results, L, ntrials):
    plt.figure()
    plt.title('Bisection search results histogram for L = {}'.format(L))
    plt.hist(p_bisection_results, bins=90)
    plt.show()


def plot_bisection_search_histogram_list(p_bisection_results, L, ntrials, cumulative=False):
    plt.figure()
    plt.title('Bisection search results histogram')
    for idx in range(L.size):
        plt.hist(p_bisection_results[idx], bins=20, cumulative=cumulative,
                 histtype='bar', linewidth=1.2, alpha=0.8, label='L = {}'.format(L[idx]))
    plt.legend()
    plt.show()


save_figures = False

if not save_figures:
    plt.ion()

files_root_prefix = 'print/data/critical_bisection_search/v2/'
files = load_data.get_bisection_critical_search_file_list(files_root_prefix)
p_bisection_results, L, ntrials = load_data.load_bisection_critical_search_file_list(files)
plot_percolation_probability_statistics(p_bisection_results, L, ntrials, ci_style='area')

plot_bisection_search_results(p_bisection_results[4], L[4], ntrials[4])

idx_hist = [9, 22, 30]
plot_bisection_search_histogram_list([p_bisection_results[idx] for idx in idx_hist], L[idx_hist], ntrials[idx_hist])

if not save_figures:
    plt.ioff()
