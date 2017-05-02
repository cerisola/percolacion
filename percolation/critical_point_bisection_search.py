import subprocess

#v4
L = [4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 24, 28, 32, 36, 40, 44, 48, 52,
    56, 60, 64, 72, 80, 88, 96, 104, 112, 124, 128, 144, 160, 176, 192, 208,
    224, 240, 256, 288, 320, 352, 384, 416, 448, 480, 512]
N = 66000
precision = 16

for l in L:
    print("Searching critical point for L = {} ...".format(l))
    subprocess.run(['build/percolation_critical_point_bisection_search', str(l), str(N), str(precision)])

print("Finished.")
