

# mysql server

docker exec -it mysql bash


# Dump da database
mysqldump -u root -p mysql | tee dump.sql


# Restore em uma database diferente
mysql -u root -p

create database if not exists bla;
use bla;
source dump.sql;

# Restore em uma database diferente
mysql -u root -p

create database if not exists bla;

mysql -u root -p bla < dump.sql

# Views

help create view

create view myview as (select 1);
