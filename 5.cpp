#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define N 1000

float A[N][N];
float B[N][N];
float C[N][N];

int main() 
{
    int i,j,k;
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 
    omp_set_num_threads(omp_get_num_procs());
    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
	{
            A[i][j] = 2;
            B[i][j] = 2;
	}
    gettimeofday(&tv1, &tz);
    double s = 1.; 
    #pragma omp parallel for reduction(+:s) num_threads(4)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

/*
    printf("Matrix C\n");
    for (int i = 0; i < N; i++){
        for (int j =0; j < N; j++){
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }
*/
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);
}