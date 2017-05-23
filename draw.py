import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from subprocess import check_output
import itertools as it


true_color = False
(N, M) = (450, 450)


def static_draw(ax, n_max=10):
	h = 0.01
	x0 = -2.2
	y0 = -2.2
	# result = check_output(["gcc Mandelbrot.c -o mand"])
	result = check_output(["./mand", str(n_max), str(h), str(x0), str(y0)])
	n = np.loadtxt("result.csv", delimiter=",", dtype=int)
	n_max = np.max(n)
	if true_color:
		colors = plt.cm.rainbow(np.linspace(0,1,n_max+1)) 
		color_mat = np.zeros([N,M,3])
		for i in range(N):
			for j in range(M):
				color_mat[i,j] = colors[n[i,j]][:3] if true_color else colors[n[i,j]]
	else:
		color_mat = n
	ax.set_xticks([])
	ax.set_yticks([])
	ax.imshow(color_mat, cmap="gray", interpolation="nearest")



def iter_animate(fig, ax, iter_times = 10):
	extent = [-2.2, 2.2, -2.2, 2.2]
	color_mat = np.zeros([N,M,3]) 
	if true_color:
		colors = plt.cm.rainbow(np.linspace(0,1,iter_times+1))
	gray_scale = np.linspace(0, 1, iter_times+1)
	img = ax.imshow(color_mat, cmap="gray", interpolation="nearest", extent=extent)
	text = ax.text(1.1, 2.3, "")
	h = 0.01
	x0 = -2.2
	y0 = -2.2

	def init():
		pass
	def update(data):
		n, i = data
		text.set_text("iteration times = {}".format(i+1))
		for i in range(N):
			for j in range(M):
				color_mat[i,j] = colors[n[i,j]][:3] \
					if true_color else gray_scale[n[i,j]]
		img.set_data(color_mat)
		return (text, img)
		
	def data_gen():
		for i in range(iter_times):
			# result = check_output(["gcc Mandelbrot.c -o mand"])
			result = check_output(["./mand", str(i), str(h), str(x0), str(y0)])
			n = np.loadtxt("result.csv", delimiter=",", dtype=int)
			yield (n, i)


	anim = animation.FuncAnimation(fig, update, data_gen, init_func=init, interval=1000)
	anim.save('Mandelbrot.gif', writer='imagemagick', fps=500)
	plt.show()

if __name__=="__main__":
	fig, ax = plt.subplots()
	# static_draw(ax, n_max=20)
	iter_animate(fig, ax, iter_times=20)
