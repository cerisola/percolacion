import subprocess

#v9
L = [4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 24, 28, 32, 36, 40, 44, 52, 56,
    64, 72, 80, 88, 96, 104, 112, 128, 144, 160, 176, 192, 208, 224, 240, 256,
    288, 320, 352, 384, 416, 448, 480, 512]
N = 500
pcenter = 0.59
decay = 4.5
grid_rounding = 6
minrepetitions = 1000
target_error = 0.005
ci = '99.00'
maxtime = 1520

for l in L:
    print("Performing probability sweep for L = {} ...".format(l))
    subprocess.run(['build/percolation_probability_sweep',
                   str(l), str(N), str(pcenter), str(decay), str(grid_rounding),
                   str(minrepetitions), str(target_error), ci, str(maxtime)])

print("Finished.")
