import numpy as np
import numpy.linalg as la
import matplotlib.pyplot as plt
import itertools as it


def C_Mat_gen(x0, y0, N, M, h):
	'''
	generates C matrix
	'''
	C_mat = np.zeros([N, M, 2])
	for i in range(N):
		for j in range(M):
			C_mat[i,j]=np.array([x0+j*h,y0+(N-1-i)*h])

	return C_mat

def iterate(C_mat):
	'''
	C_mat: N*M*2 matrix
	'''
	passed = []
	N, M, d = C_mat.shape
	Z_mat = np.zeros([N, M, 2])
	while True:
		current_passed = []
		for i in range(N):
			for j in range(M):
				z0 = Z_mat[i,j]
				if (i,j) in passed:
					continue
				else:
					Z_mat[i,j] = np.array([z0[0]**2-z0[1]**2, 2*z0[0]*z0[1]]) + C_mat[i,j]
					if la.norm(Z_mat[i,j]) >= 2:
						passed.append((i,j))
						current_passed.append((i,j))
		yield current_passed

def draw_map(ax, C_mat, n_max=3):
	N, M, d = C_mat.shape
	color_mat = np.zeros([N,M,3])
	colors = it.cycle(plt.cm.rainbow(np.linspace(0,1,n_max)))
	c = next(colors)

	k = 0
	for current_passed in iterate(C_mat):
		k += 1 
		if k > n_max: break
		print("iteration times: {}".format(k))
		for i in range(N):
			for j in range(M):
				if (i,j) in current_passed:
					color_mat[i,j] = c[:3]
		c = next(colors)

	ax.imshow(color_mat, interpolation="nearest")



def main():
	fig, ax = plt.subplots()
	ax.set_xticks([])
	ax.set_yticks([])
	C_mat = C_Mat_gen(-2.2, -2.2, 90, 90, 0.05)
	draw_map(ax, C_mat, n_max=10)
	plt.savefig("n_max10.png", dpi=300)
	plt.show()

if __name__ == "__main__":
	main()




