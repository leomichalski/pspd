#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("rank: %d; size (nprocs): %d; pid: %d; ppid: %d.\n", rank, size, getpid(), getppid());

    MPI_Finalize();
    return 0;
}
