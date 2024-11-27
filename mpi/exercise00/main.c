// #include <sys/time.h>
#include <stdio.h>
#include <mpi.h>
// #include <sys/types.h>
#include <unistd.h>

#define MANAGER 0
// #define WORKER positive numbers except 0

#define TAG 0
// MPI_ANY_TAG

char texto_base[] = "abcdefghijklmnopqrstuvwxyz 1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int main(int argc, char *argv[]) {
    int texto_base_idx = 0;
    int iteration_num = 300;
    int iteration_idx;
    int worker_idx;

    MPI_Status status;
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == MANAGER) {
        iteration_idx = 0;
        while (iteration_idx < iteration_num) {
            for (worker_idx = 1; worker_idx < size; worker_idx++) {
                MPI_Send(&texto_base_idx, 1, MPI_INT, worker_idx, TAG, MPI_COMM_WORLD);
                MPI_Recv(&texto_base_idx, 1, MPI_INT, worker_idx, TAG, MPI_COMM_WORLD, &status);
                iteration_idx++;
                // Lidar com o caso de o numero de iteracoes ser maior do que o tamanho do texto_base
                texto_base_idx %= sizeof(texto_base);
                // Printar uma nova linha sempre que o texto base acabar
                if (texto_base_idx == 0) {
                    printf("\n");
                    fflush(stdout);
                    // Dormir para dar tempo de o escalonador de processos realizar o print
                    usleep(10000);
                }
            }
        }
        // Enviar um texto_base_idx negativo como sinal para parar cada um dos workers
        texto_base_idx = -1;
        for (worker_idx = 1; worker_idx < size; worker_idx++) {
            MPI_Send(&texto_base_idx, 1, MPI_INT, worker_idx, TAG, MPI_COMM_WORLD);
        }
        // Printar uma nova linha antes de fechar tudo
        if (texto_base_idx != 0) {
            printf("\n");
        }
    } else {
        while (1) {
            MPI_Recv(&texto_base_idx, 1, MPI_INT, MANAGER, TAG, MPI_COMM_WORLD, &status);
            if (texto_base_idx < 0) {
                break;
            }
            printf("%c", texto_base[texto_base_idx]);
            fflush(stdout);
            // Dormir para dar tempo de o escalonador de processos realizar o print
            usleep(10000);
            texto_base_idx++;
            MPI_Send(&texto_base_idx, 1, MPI_INT, MANAGER, TAG, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
