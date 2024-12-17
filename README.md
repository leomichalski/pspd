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
