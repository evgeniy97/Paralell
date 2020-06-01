#include <cstdlib>
//#include <iostream>
#include <math.h>
#include "mpi.h"
#include <stdio.h>

const int N = 4;

int main(int argc, char *argv[])
{
    int r, q, myid, numprocs;
    int i0;
    int *b, *c, *loc_a, *loc_c;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Status status;
    q = N / numprocs;
    b = new int[N * N];
    c = new int[N * N];
    loc_c = new int[N * N];
    loc_a = new int[q];
    for (int i = 0; i < N * N; i++)
    {
        c[i] = 0;
        loc_c[i] = 0;
    }
    if (myid == 0)
    {
        for (int j = 0; j < numprocs; j++)
        {
            for (r = 0; r < q * N; r++)
            {
                loc_a[r] = 1;
            }
            MPI_Send(&loc_a[0], q * N, MPI_INT, j, 0, MPI_COMM_WORLD);
        }
        for (int i = 0; i < N * N; i++)
        {
            b[i] = 1;
        }
    }
    MPI_Recv(&loc_a[0], q * N, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    for (r = 0; r < N; r++)
    {
        MPI_Bcast(&b[r * N], N, MPI_INT, 0, MPI_COMM_WORLD);
        i0 = myid * q;
        for (int i = 0; i < q; i++)
        {
            for (int j = 0; j < N; j++)
            {
                loc_c[r * N + i0] += loc_a[i * N + j] * b[r * N + j];
            }
            i0++;
        }
        MPI_Reduce(loc_c, c, N * N, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    if (myid == 0)
    {
        FILE *f = fopen("result.txt", "w");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fprintf(f, "%d\t", c[j * N + i]);
            }
            fprintf(f, "\n");
        }
        fclose(f);
    }
    return 0;
    MPI_Finalize();
}