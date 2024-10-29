struct operandos {
    int x;
    int y;
};
program PROG {
    version VERSAO {
        int ADD(operandos) = 1;
        int SUB(operandos) = 2;
        int MUL(operandos) = 3;
    } = 100;
} = 55555555;
