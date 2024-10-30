# MPI

## Setup do MPICH

```bash
sudo apt install mpich
```

## Setup do OpenMPI

Em vez do MPICH, é possível utilizar o OpenMPI.

```bash
sudo apt install libopenmpi-dev
```

## Compilar código MPI

```bash
mpicc -o main.o main.c
```

#### Executar binário MPI

```bash
# -np: number of processes
mpirun -np 4 ./main.o
```
