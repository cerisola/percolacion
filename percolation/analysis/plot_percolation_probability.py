import importlib
import numpy as np
from scipy.integrate import simps
import matplotlib.pyplot as plt
import load_data
import common
importlib.reload(load_data)
importlib.reload(common)

save_figures = False

files_root_prefix = 'print/data/probability_sweep/vdbg/'
L = 64
file_name = load_data.get_probability_sweep_file_list(files_root_prefix, L=L)[0]
p, P, _, nsamples, _ = load_data.load_probability_sweep_file(file_name)

ci = '99.9'
stderr = common.binomial_sem(P, nsamples, ci=ci)
Pm = np.maximum(P - stderr, 0)
Pp = np.minimum(P + stderr, 1)

plt.ion()

plt.figure()
plt.plot(p, P, '-', color='royalblue', linewidth=1.0)
plt.fill_between(p, Pp, Pm, facecolor='royalblue', alpha=0.5)
plt.plot((0,1), (0.5,0.5), '--', color='orangered', linewidth=0.8)
plt.grid()
plt.show()

plt.ioff()

pc_mean = common.cdf_mean(P, p)
pc_std = common.cdf_std(P, p)
print('integration mean: {}'.format(pc_mean))
print('integration std: {}'.format(pc_std))

pc_median_min = p[(Pp >= 0.5).argmax()]
pc_median_max = p[(Pm >= 0.5).argmax()]
pc_median_err = (pc_median_max - pc_median_min)/2
pc_median_med = pc_median_min + pc_median_err
print('median min: {}'.format(pc_median_min))
print('median max: {}'.format(pc_median_max))
print('median med: {}'.format(pc_median_med))
print('median err: {}'.format(pc_median_err))

input()
