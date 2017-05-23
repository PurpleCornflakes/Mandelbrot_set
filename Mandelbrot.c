#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 90
#define M 90


void C_mat_gen();
int ij2Index(int i, int j);
int * Index2ij(int index);
double h = 0.05;
int n_max = 3;
 
int main(int argc, char const *argv[])
{
	double x0 = -2.2, y0 = -2.2;
	double ***C_mat;
	FILE * file;
	if (argv[1]) file_name = argv[1];
	else {
		printf("Please add filename\n");
		return 1;
	}
	file = fopen()

	// initialize C_mat
	C_mat = (double ***) malloc(N*sizeof(double **));
	for(int i = 0; i < N; i++){
		C_mat[i] = (double **) malloc(M*sizeof(double *));
		for(int j=0; j<M; j++){
			C_mat[i][j] = (double *) malloc(2*sizeof(double));
		}
	}
	// generates C_mat
	C_mat_gen(C_mat, x0, y0);




	// printf("%d, %d, %d",ij2Index(1,1), Index2ij(6)[0],Index2ij(6)[1] );
}

void C_mat_gen(double *** C_mat, double x0, double y0)
{
	/* generates C matrix
	x0, y0: lower left coordinates
	N, M: dimensions of C matrix
	h: step size */
	double c[2];
	for(int i = 0; i<N; i++)
		for(int j = 0; j<M; j++){
			c[0] = x0 + j*h;
			c[1] = y0 + (N-1-i)*h;
			C_mat[i][j][0] = c[0];
			C_mat[i][j][1] = c[1];
		}
}

void OneIteration(double *** C_mat, int ** n)
{
	// static vars is initialized with zeros
	static double Z_mat[N][M][2];
	static int passed[N*M];
	static int iter_n;
	iter_n++;
	int i,j;
	for(i = 0; i<N; i++)
		for(j = 0; j<M; j++){
			if(passed[i*M+j]==1) continue;
			Z_mat[i][j][0] = C_mat[i][j][0] 
				+ Z_mat[i][j][0]*Z_mat[i][j][0] - Z_mat[i][j][1]*Z_mat[i][j][1];
			Z_mat[i][j][1] = C_mat[i][j][1] + 2*Z_mat[i][j][1]*Z_mat[i][j][0];
			if(norm(Z_mat[i][j]) >=2){
				passed[i*M+j] = 1;
				n[i][j] = iter_n;
			}
		}
}

double norm(double * vec)
{
	return pow(vec[0]*vec[0]+vec[1]*vec[1], 0.5);
}

void 2Darray_to_file(int ** n, FILE * file)
{
	for(int i = 0; i<N; i++)
		for(int j = 0; j<M; j++){
			if(j==M-1)
				fprintf(file, "%d\n", n[i][j]);
			else
				fprintf(file, "%d,", n[i][j]);
		}
}
















