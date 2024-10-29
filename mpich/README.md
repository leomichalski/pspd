# MPICH

Vamos usar o MPICH, não o OpenMPI.

## Setup

```bash
sudo apt install mpich
```

## Compilar código MPI

```bash
mpicc -o main.o main.c
```

#### Executar binário MPI

```bash
# -np: number of processes
mpirun -np 8 ./main.o
```
