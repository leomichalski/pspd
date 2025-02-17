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

# material alternativo

git clone https://github.com/yudi-azvd/pspd/
