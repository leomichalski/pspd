#include <stdio.h>
#include <mpi.h>
//#include <sys/types.h>
#include <unistd.h>

#define CONSUMER 0
// #define PRODUCER others

#define TAG 0
// MPI_ANY_TAG

int main(int argc, char *argv[]) {
    MPI_Status status;

    const int STRING_MSG_LEN = 256;
    char string_msg[STRING_MSG_LEN];

    int number_msg;

    const int NUMBER_VEC_LEN = 3;
    int number_vec_msg[NUMBER_VEC_LEN];
    int number_vec_idx;

    int rank, size;

    MPI_Init(&argc, &argv);

    // A diferenca do rank para o PID eh que
    // o PID pode ser o mesmo em maquinas diferentes,
    // ja o rank sempre vai ser unico para cada processo.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Size eh a quantidade de processos.
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("rank: %d; size (nprocs): %d; pid: %d; ppid: %d.\n", rank, size, getpid(), getppid());

    if (rank == CONSUMER) {
        int producer;
        for (producer = 1; producer < size; producer++) {
            MPI_Recv(string_msg, STRING_MSG_LEN, MPI_CHAR, producer, TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&number_msg, 1, MPI_INT, producer, TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&number_vec_msg, NUMBER_VEC_LEN, MPI_INT, producer, TAG, MPI_COMM_WORLD, &status);
            printf("CONSUMER: Received string: \"%s\". Received number: %d.", string_msg, number_msg);
            printf(" Received number_vec: {");
            for (number_vec_idx = 0; number_vec_idx < NUMBER_VEC_LEN; number_vec_idx++) {
                printf("%d, ", number_vec_msg[number_vec_idx]);
            }
            printf("}.\n");

            sprintf(string_msg, "Hello, Producer %d!", producer);
            MPI_Send(string_msg, STRING_MSG_LEN, MPI_CHAR, producer, TAG, MPI_COMM_WORLD);;
        }
    } else {
        number_msg = rank;
        for (number_vec_idx = 0; number_vec_idx < NUMBER_VEC_LEN; number_vec_idx++) {
            number_vec_msg[number_vec_idx] = rank;
        }
        MPI_Send("Hello, Consumer!", STRING_MSG_LEN, MPI_CHAR, CONSUMER, TAG, MPI_COMM_WORLD);;
        MPI_Send(&number_msg, 1, MPI_INT, CONSUMER, TAG, MPI_COMM_WORLD);;
        MPI_Send(&number_vec_msg, NUMBER_VEC_LEN, MPI_INT, CONSUMER, TAG, MPI_COMM_WORLD);
        MPI_Recv(string_msg, STRING_MSG_LEN, MPI_CHAR, CONSUMER, TAG, MPI_COMM_WORLD, &status);
        printf("PRODUCER %d: Received string: \"%s\".\n", rank, string_msg);
    }

    MPI_Finalize();
    return 0;
}
