#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 450
#define M 450


void C_mat_gen();
void OneIteration();
double norm();
void array_to_file();
 
int main(int argc, char const *argv[])
{
	int n_max = atoi(argv[1]);//?atoi(argv[1]):10;
	double h = atof(argv[2]);//?atof(argv[2]):(4.5/N);
	double x0 = atof(argv[3]);//?atof(argv[3]):-2.2;
	double y0 = atof(argv[4]);//?atof(argv[4]):-2.2;
	double ***C_mat;
	int ** n;
	char * filename;
	filename = "result.csv";
	FILE * file;


	file = fopen(filename, "w");



	// initialize C_mat
	C_mat = (double ***) malloc(N*sizeof(double **));
	for(int i = 0; i < N; i++){
		C_mat[i] = (double **) malloc(M*sizeof(double *));
		for(int j=0; j<M; j++){
			C_mat[i][j] = (double *) malloc(2*sizeof(double));
		}
	}

	n = (int **) malloc(N*sizeof(int *));
	for(int i = 0; i < N; i++){
		n[i] = (int *) malloc(M*sizeof(int));
		for(int j = 0; j<M; j++)
			n[i][j] = 0;
	}
	// array_to_file(n, file);
	// generates C_mat
	C_mat_gen(C_mat, x0, y0, h);

	for(int i = 0; i<n_max; i++){
		printf("Iteration times: %d\n", i+1);
		OneIteration(C_mat, n);
		// array_to_file(n, file);
	}
	array_to_file(n, file);
	fclose(file);
}

void C_mat_gen(double *** C_mat, double x0, double y0, double h)
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
	double z0,z1;
	int i,j;
	iter_n += 1;
	for(i = 0; i<N; i++)
		for(j = 0; j<M; j++){
			if(passed[i*M+j]==1) continue;
			z0 = Z_mat[i][j][0];
			z1 = Z_mat[i][j][1];
			Z_mat[i][j][0] = C_mat[i][j][0] + z0*z0 - z1*z1;
			Z_mat[i][j][1] = C_mat[i][j][1] + 2*z0*z1;
			if(norm(Z_mat[i][j]) >= 2.0){
				passed[i*M+j] = 1;
				n[i][j] = iter_n;
			}
		}
}

double norm(double * vec)
{
	return pow(vec[0]*vec[0]+vec[1]*vec[1], 0.5);
}

void array_to_file(int ** n, FILE * file)
{
	for(int i = 0; i<N; i++)
		for(int j = 0; j<M; j++){
			if(j==M-1)
				fprintf(file, "%d\n", n[i][j]);
			else
				fprintf(file, "%d,", n[i][j]);
		}
}
















