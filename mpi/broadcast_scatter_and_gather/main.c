#include <stdio.h>
#include <mpi.h>
//#include <sys/types.h>
#include <unistd.h>

#define MANAGER 0
// #define WORKER others

#define TAG 0
// MPI_ANY_TAG

int main(int argc, char *argv[]) {
    /* ********************************************************************** */
    // INICIALIZACAO

    const int DATA_LEN = 100;
    int data[DATA_LEN];
    int data_idx;

    int MULTIPLY_FACTOR;

    // MPI related vars
    MPI_Status status;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (DATA_LEN % size > 0) {
        // TODO: printar no stderr
        printf("Erro: %d precisa ser divisivel pelo numero de processos, pois %d eh a quantidade de elementos no vetor a ser distribuido entre os processos.", DATA_LEN, DATA_LEN);
        // TODO: retornar valor adequado
        return -1;
    }
    const int STEP2_SHARD_LEN = (int) DATA_LEN / size;
    int step2_shard[STEP2_SHARD_LEN];
    int step2_shard_idx;

    /* ********************************************************************** */
    // STEP 0: Simular leitura de dados pelo processo manager

    if (rank == MANAGER) {
        MULTIPLY_FACTOR = 2;
        for (data_idx = 0; data_idx < DATA_LEN; data_idx++) {
            data[data_idx] = data_idx;
        }
    }

    /* ********************************************************************** */
    // STEP 1: fazer broadcast do numero pelo qual o vetor vai ser multiplicado

    MPI_Bcast(&MULTIPLY_FACTOR, 1, MPI_INT, MANAGER, MPI_COMM_WORLD);
    // // Esperar todos os processos terem o numero MULTIPLY_FACTOR para seguir para o proximo passo
    // MPI_Barrier(MPI_COMM_WORLD);

    /* ********************************************************************** */
    // STEP 2: scatter, fazer alguma coisa, depois gather

    MPI_Scatter(data, STEP2_SHARD_LEN, MPI_INT, step2_shard, STEP2_SHARD_LEN, MPI_INT, MANAGER, MPI_COMM_WORLD);
    // Multiplicar cada numero pelo MULTIPLY_FACTOR.
    for (step2_shard_idx = 0; step2_shard_idx < STEP2_SHARD_LEN; step2_shard_idx++) {
        step2_shard[step2_shard_idx] = step2_shard[step2_shard_idx] * MULTIPLY_FACTOR;
        // printf("rank: %d; step2_shard[%d]: %d\n", rank, step2_shard_idx, step2_shard[step2_shard_idx]);
    }
    MPI_Gather(step2_shard, STEP2_SHARD_LEN, MPI_INT, data, STEP2_SHARD_LEN, MPI_INT, MANAGER, MPI_COMM_WORLD); 

    /* ********************************************************************** */
    // STEP 3: mostrar resultados

    // Esperar todos os processos terminarem antes de mostrar os resultados
    MPI_Barrier(MPI_COMM_WORLD);
    // Mostrar resultados
    if (rank == MANAGER) {
        for (data_idx = 0; data_idx < DATA_LEN; data_idx++) {
            printf("data[%d]: %d\n", data_idx, data[data_idx]);
        }
    }

    /* ********************************************************************** */
    // FINALIZACAO

    MPI_Finalize();
    return 0;
}
