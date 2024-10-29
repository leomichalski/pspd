#include <stdio.h>
#include <stdlib.h>
#include "calcula.h"

void add(CLIENT *clnt, int x, int y, int *result) {
	operandos ops;
	ops.x = x;
	ops.y = y;
	/* Chama o stub cliente criado pelo rpcgen */
	*result = *add_100(&ops, clnt);
	if (result == (int *) NULL) {
        clnt_perror (clnt, "call failed");
		// fprintf(stderr, "Problema na chamada RPC\n");
		exit(0);
	}
}

void sub(CLIENT *clnt, int x, int y, int *result) {
	operandos ops;
	ops.x = x;
	ops.y = y;
	/* Chama o stub cliente criado pelo rpcgen */
	*result = *sub_100(&ops, clnt);
	if (result == (int *) NULL) {
        clnt_perror (clnt, "call failed");
		// fprintf(stderr, "Problema na chamada RPC\n");
		exit(0);
	}
}

int main (int argc, char *argv[]) {
	/* PASSO 1: CRIAR CLIENTE */
    CLIENT *clnt;
	char* host = "localhost";
// #ifndef DEBUG
    clnt = clnt_create (host, PROG, VERSAO, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
// #endif /* DEBUG */

	/* PASSO 2: FAZER ALGO */
    int result_1;
    int result_2;

	add(clnt, 1, 1, &result_1);
	sub(clnt, 1, 1, &result_2);

	printf("sum=%d; sub=%d;\n", result_1, result_2);

	/* PASSO 3: DESTRUIR CLIENTE */

// #ifndef    DEBUG
    clnt_destroy (clnt);
// #endif     /* DEBUG */

	// fprintf(stderr,"Uso: %s hostname num1 num2\n",argv[0]);
}

// SEM MODULARIZACAO
// int
// main (int argc, char *argv[])
// {
//     char *host;

//     if (argc < 2) {
//         printf ("usage: %s server_host\n", argv[0]);
//         exit (1);
//     }
//     host = argv[1];

//     CLIENT *clnt;
//     int  *result_1;
//     operandos  add_100_arg;
//     int  *result_2;
//     operandos  sub_100_arg;

// 	add_100_arg.x = 1;
// 	add_100_arg.y = 1;
// 	sub_100_arg.x = 1;
// 	sub_100_arg.y = 1;

// // #ifndef DEBUG
//     clnt = clnt_create (host, PROG, VERSAO, "udp");
//     if (clnt == NULL) {
//         clnt_pcreateerror (host);
//         exit (1);
//     }
// // #endif /* DEBUG */

//     result_1 = add_100(&add_100_arg, clnt);
//     if (result_1 == (int *) NULL) {
//         clnt_perror (clnt, "call failed");
//     }
//     result_2 = sub_100(&sub_100_arg, clnt);
//     if (result_2 == (int *) NULL) {
//         clnt_perror (clnt, "call failed");
//     }
// // #ifndef    DEBUG
//     clnt_destroy (clnt);
// // #endif     /* DEBUG */


// printf("sum=%d; sub=%d;\n", *result_1, *result_2);
// // fprintf(stderr,"Uso: %s hostname num1 num2\n",argv[0]);
// }
