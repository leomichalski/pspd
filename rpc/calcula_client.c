/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

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

void mul(CLIENT *clnt, int x, int y, int *result) {
    operandos ops;
    ops.x = x;
    ops.y = y;
    /* Chama o stub cliente criado pelo rpcgen */
    *result = *mul_100(&ops, clnt);
    if (result == (int *) NULL) {
        clnt_perror (clnt, "call failed");
        // fprintf(stderr, "Problema na chamada RPC\n");
        exit(0);
    }
}

int
main (int argc, char *argv[])
{
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
    int result_add;
    int result_sub;
    int result_mul;
    add(clnt, 1, 1, &result_add);
    sub(clnt, 1, 1, &result_sub);
    mul(clnt, 1, 1, &result_mul);

    printf("sum=%d; sub=%d; mul=%d;\n", result_add, result_sub, result_mul);

	/* PASSO 3: DESTRUIR CLIENTE */

// #ifndef    DEBUG
    clnt_destroy (clnt);
// #endif     /* DEBUG */
}
