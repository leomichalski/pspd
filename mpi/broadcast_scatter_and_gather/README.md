# MPI

## Setup e execução

Clonar este repositório.

```bash
git clone git@github.com:leomichalski/pspd.git
```

Ir para a pasta "pspd/mpi".

```bash
cd pspd/mpi/scatter_and_gather
```

### Setup e execução no Debian.

É necessário ter MPICH ou OpenMPI instalado.

```bash
# Instalar o MPICH no Debian.
sudo apt install mpich

# Instalar o OpenMPI no Debian.
sudo apt install libopenmpi-dev
```

#### Compilar código MPI.

```bash
mpicc -o main.o main.c
```

#### Executar binário MPI.

```bash
# -np: number of processes
mpirun -np 4 ./main.o
```

### Setup e execução em um cluster Kubernetes.

É necessário ter um cluster Kubernetes e o MPI Operator instalado.

#### (opcional) Configuração mais simples possível do MPI Operator v0.6.0.

```bash
kubectl apply --server-side -f https://raw.githubusercontent.com/kubeflow/mpi-operator/v0.6.0/deploy/v2beta1/mpi-operator.yaml
```

#### (opcional) Criar namespace para rodar os MPIJobs.

```bash
kubectl create namespace mpi-jobs
```

#### Criar ConfigMap a partir de arquivo `main.c` no namespace adequado.

```bash
kubectl -n mpi-jobs create configmap main-mpi-job --from-file main.c
```

#### Aplicar o MPIJob no namespace adequado.

```bash
kubectl -n mpi-jobs apply -f main-mpi-job.yaml
```
