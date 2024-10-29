## Setup (ubuntu 24.04)

```bash
sudo apt install -y rpcbind libtirpc-dev libnsl-dev
```

## Escrever arquivo (IDF) de nome calcula.x com seguinte conteúdo

```c
struct operandos {
    int x;
    int y;
};
program PROG {
    version VERSAO {
        int ADD(operandos) = 1;
        int SUB(operandos) = 2;
    } = 100;
} = 55555555;
```

## Gerar os arquivos

```bash
rpcgen -a calcula.x
```

## Compilar calcula_client e calcula_server

Obs: pode ser q o caminho "/usr/include/tirpc" seja diferente no seu PC

```bash
make -f Makefile.calcula LDLIBS="-ltirpc" CFLAGS=-I/usr/include/tirpc
```
