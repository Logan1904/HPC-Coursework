#include "ReactionDiffusion.h"

#include <mpi.h>
#include <cblas.h>
#include <iostream>

void ReactionDiffusion::TimeIntegrate(int rank, int size) {
    int X = (Nx*Ny) % size;
    int Y = (Nx*Ny - X)/ size;

    int length = Nx*Ny;

    int n_rows;

    if (rank < size-X) {
        n_rows = Y;
    } else {
        n_rows = Y+1;
    }

    int* count_recvs = new int[size]();
    int* displs = new int[size]();

    for (int i = 0; i < size; ++i) {
        if (i < size-X) {
            count_recvs[i] = Y;
        } else {
            count_recvs[i] = Y+1;
        }
    }

    for (int i = 1; i < size; ++i) {
        displs[i] = count_recvs[i-1] + displs[i-1];
    }

    int t = 0;
    while (t<Nt) {
        if (rank == 0) std::cout << t << std::endl;
        double* utmp = new double[n_rows]();
        double* vtmp = new double[n_rows]();

        cblas_dgemv(CblasRowMajor, CblasNoTrans, n_rows, length, 1.0, A, length, u, 1, 0.0, utmp, 1);
        cblas_dgemv(CblasRowMajor, CblasNoTrans, n_rows, length, 1.0, B, length, v, 1, 0.0, vtmp, 1);

        for (int row = 0; row < n_rows; ++row) {

            int glob_row;
            if (rank < size-X) {
               glob_row = rank*Y + row;
            } else {
               glob_row = (size-X)*Y + (rank-(size-X))*(Y+1) + row;
            }

            utmp[row] += dt*(eps*u[glob_row]*(1.0-u[glob_row])*(u[glob_row] - (1/a)*(v[glob_row]+b)));
            vtmp[row] += dt*(u[glob_row]*u[glob_row]*u[glob_row] - v[glob_row]);
        }

        MPI_Allgatherv(utmp, n_rows, MPI_DOUBLE, u, count_recvs, displs, MPI_DOUBLE, MPI_COMM_WORLD);
        MPI_Allgatherv(vtmp, n_rows, MPI_DOUBLE, v, count_recvs, displs, MPI_DOUBLE, MPI_COMM_WORLD);





        ++t;

    }
}