import importlib
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
import load_data
import common
importlib.reload(load_data)
importlib.reload(common)


def plot_percolation_probability_statistics(mean, std, sem, L, ci='', ci_style='none'):
    plt.figure()
    if ci_style == 'errorbar':
        plt.errorbar(L, mean, yerr=sem, fmt='-o', label='mean ({}% CI)'.format(ci))
    elif ci_style == 'area':
        plt.plot(L, mean, '-o', markersize=4.0, label='mean')
        plt.fill_between(L, mean + sem, mean - sem, alpha=0.5, label='{}% CI'.format(ci))
    else:
        plt.plot(L, mean, '-o', markersize=4.0, label='mean')
    plt.grid()
    plt.xlabel('L')
    plt.ylabel('$p_{\mathrm{avg}}$ via bisection')
    plt.legend()
    plt.show()

    plt.figure()
    plt.loglog(L, std, '-o', markersize=4.0, label='mean-std')
    plt.loglog(L, sem, '-o', markersize=4.0, label='mean-sem')
    plt.grid()
    plt.xlabel('L')
    plt.ylabel('$p_{\mathrm{avg}}$ err')
    plt.legend()
    plt.show()


def plot_bisection_search_results(p_percolation, L, ntrials):
    plt.figure()
    plt.title('Bisection search of $p_c$ for L = {}, avg over {} trials'.format(L, ntrials))
    plt.plot(p_percolation, 'o', markersize=2.0)
    plt.grid()
    plt.xlabel('iter')
    plt.ylabel('p')
    plt.show()


def plot_bisection_search_histogram(p_percolation, L, ntrials):
    plt.figure()
    plt.title('Bisection search results histogram for L = {}'.format(L))
    plt.hist(p_percolation, bins=90)
    plt.show()


def plot_bisection_search_histogram_list(p_percolation, L, ntrials, cumulative=False):
    plt.figure()
    plt.title('Bisection search results histogram')
    for idx in range(L.size):
        plt.hist(p_percolation[idx], bins=20, cumulative=cumulative,
                 histtype='bar', linewidth=1.2, alpha=0.8, label='L = {}'.format(L[idx]))
    plt.legend()
    plt.show()


save_figures = False
ci = '99.99'

if not save_figures:
    plt.ion()

files_root_prefix = 'print/data/critical_bisection_search/v4/'
files = load_data.get_bisection_critical_search_file_list(files_root_prefix)
p_percolation, L, ntrials = load_data.load_bisection_critical_search_file_list(files)

mean = common.listmap(common.mean, p_percolation)
var = common.listmap(common.var, p_percolation)
std = np.sqrt(var)
sem = common.listmap(common.sem, p_percolation, args={'ci': ci})

plot_percolation_probability_statistics(mean, std, sem, L, ci=ci, ci_style='area')
plot_bisection_search_results(p_percolation[4], L[4], ntrials[4])

idx_hist = [9, 22, 30]
plot_bisection_search_histogram_list([p_percolation[idx] for idx in idx_hist], L[idx_hist], ntrials[idx_hist])

if not save_figures:
    plt.ioff()
