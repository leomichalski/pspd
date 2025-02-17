# mysql server

```bash
docker run --name mysql -d -p 3306:3306 mysql/mysql-server
docker logs mysql
docker exec -it mysql bash
mysql -u root -p
ALTER USER 'root'@'localhost' IDENTIFIED BY 'mysql';
```

# Dump da database

```bash
mysqldump -u root -p mysql | tee dump.sql
```


# Restore em uma database diferente

```bash
mysql -u root -p
```

```sql
create database if not exists bla;
use bla;
source dump.sql;
```

# Restore em uma database diferente

```bash
mysql -u root -p
```

```sql
create database if not exists bla;
```

```bash
mysql -u root -p bla < dump.sql
```

# Views

```sql
help create view
```

```sql
create or replace view myview as (select 1);
```

# having

diferente do where, aplica no grupo em vez de em todas as tuplas

```sql
SELECT pe.company, count(product_name) AS n_products, avg(carbon_footprint_pcf) AS avg_carbon_footprint_pcf
FROM product_emissions AS pe
WHERE industry_group = 'Technology Hardware & Equipment'
GROUP BY pe.company, industry_group
HAVING avg(carbon_footprint_pcf)>100
ORDER BY n_products
```

# function

```
git clone https://github.com/leomichalski/pspd
sudo apt install xclip -y

a() {
    xclip -i -sel copy /home/alunos/pspd/README.md
}
```

# openmp

1

```
#include <stdio.h>
#include <omp.h>

#define TAM 8

int main() {
  int v[] = {0,1,2,3,4,5,6,7};
  int sum = 0;

  #pragma omp parallel for
  for (int i = 0; i < TAM; i++) {
    #pragma omp critical
    {
      sum += v[i];
    }
    //printf("thid=%d sum=%d\n", sum, omp_get_thread_num());
  }

  printf("sum=%d\n", sum);

  return 0;
}

```

2

```
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//#define TAM 3
#define TAM 2000000

int main() {
  int* v = (int*) malloc(TAM * sizeof(int));
  int query = 86;
  int ocurrence_qty = 0;
  int i;

  for (i = 0; i < TAM; i++) {
    v[i] = rand() % 100; // always same seed, good enough for this exercise
  }

  #pragma omp parallel for reduction(+:ocurrence_qty)
  for (i = 0; i < TAM; i++) {
    ocurrence_qty += v[i] == query;
  }

  printf("ocurrence_qty=%d\n", ocurrence_qty);
  // printf("v[0]=%d\n", v[0]);
  // printf("v[1]=%d\n", v[1]);
  // printf("v[2]=%d\n", v[2]);

  return 0;
}
```

# cuda

how cuda blocks work in add<<<1,N>>>( N, array1, array2, result )?

what's the difference between vecAdd and add in CUDA?


```
// Este código realiza a soma elemento a elemento de dois vetores 
// utilizando a GPU via CUDA. O tamanho do vetor (N) e o ID do 
// dispositivo GPU são especificados como argumentos na linha de 
// comando. Inicialmente, a memória para os vetores a, b e c é 
// alocada na CPU (host) e na GPU (device). Os vetores a e b são 
// preenchidos com valores específicos (a[i] = -i e b[i] = i * i),
//  e os dados são transferidos para a GPU. O kernel CUDA add é 
// lançado com N threads, onde cada thread soma os elementos 
// correspondentes de a e b, armazenando o resultado em c. 
// Após a execução do kernel, o vetor c é copiado de volta para a CPU, 
// e os resultados das somas são exibidos. O código também exibe o 
// nome do dispositivo GPU usado. Finalmente, a memória alocada na CPU e GPU é liberada.

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Convenience function for checking CUDA runtime API results
// can be wrapped around any runtime API call. No-op in release builds.

//  ./cuda/soma_vetor_cuda 10 0
inline
cudaError_t checkCuda(cudaError_t result)
{
#if defined(DEBUG) || defined(_DEBUG)
  if (result != cudaSuccess) {
    fprintf(stderr, "CUDA Runtime Error: %s\n", cudaGetErrorString(result));
    assert(result == cudaSuccess);
  }
#endif
  return result;
}

__global__ void add( int N, float *a, float *b, float *c ) {
    int tid = threadIdx.x;    // this thread handles the data at its thread id
    if (tid < N)
        c[tid] = a[tid] + b[tid];
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
      fprintf(stderr, "Syntax: %s <vector size N> <device id>\n", argv[0]);
      return EXIT_FAILURE;
    }

    int N = atoi(argv[1]);
    int devId = atoi(argv[2]);

    checkCuda( cudaSetDevice(devId) );

    float *a, *b, *c;
    // allocate the memory on the CPU
    a = (float *)malloc( N * sizeof (float));
    b = (float *)malloc( N * sizeof (float));
    c = (float *)malloc( N * sizeof (float));

    float *dev_a, *dev_b, *dev_c;
    // allocate the memory on the GPU
    checkCuda( cudaMalloc( (void**)&dev_a, N * sizeof(float) ) );
    checkCuda( cudaMalloc( (void**)&dev_b, N * sizeof(float) ) );
    checkCuda( cudaMalloc( (void**)&dev_c, N * sizeof(float) ) );

    // fill the arrays 'a' and 'b' on the CPU
    for (int i=0; i<N; i++) {
        a[i] = -i;
        b[i] = i * i;
    }

    // copy the arrays 'a' and 'b' to the GPU
    checkCuda( cudaMemcpy( dev_a, a, N * sizeof(float), cudaMemcpyHostToDevice ) );
    checkCuda( cudaMemcpy( dev_b, b, N * sizeof(float), cudaMemcpyHostToDevice ) );

    add<<<1,N>>>( N, dev_a, dev_b, dev_c );

    // copy the array 'c' back from the GPU to the CPU
    checkCuda( cudaMemcpy( c, dev_c, N * sizeof(float), cudaMemcpyDeviceToHost ) );  
    
    // display the results
    for (int i=0; i<N; i++) {
        printf( "%6.0f + %6.0f = %6.0f\n", a[i], b[i], c[i] );
    }

    // device properties
    cudaDeviceProp prop;
    checkCuda( cudaGetDeviceProperties(&prop, devId));
    printf("\bDevice: %s\n", prop.name);   

    // free the memory allocated on the CPU
    free(a); a=NULL;
    free(b); b=NULL;
    free(c); c=NULL;

    // free the memory allocated on the GPU
    checkCuda( cudaFree( dev_a ) );
    checkCuda( cudaFree( dev_b ) );
    checkCuda( cudaFree( dev_c ) );

    return 0;
}
```


# material alternativo

git clone https://github.com/yudi-azvd/pspd/
