import numpy as np
import matplotlib.pyplot as plt
import sys

n = np.loadtxt("result.csv", delimiter=",", dtype=int)
n_max = int(sys.argv[1])
true_color = True
N, M = n.shape
color_mat = np.zeros([N,M,3]) if true_color else np.zeros([N,M])
colors = plt.cm.rainbow(np.linspace(0,1,n_max+1)) \
	if true_color else np.linspace(0,1,n_max+1)

for i in range(N):
	for j in range(M):
		color_mat[i,j] = colors[n[i,j]][:3]

plt.imshow(n, cmap="gray", interpolation="nearest")
plt.show()
