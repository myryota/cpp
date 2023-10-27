create table if not exists china.logist(
id int not primary key,
name varchar(50) not null,
phone_number varchar(50) not null,
city varchar(50) not
);

create table if not exists china.user(
id int not primary key,
name varchar(50) not null,
phone_number varchar(50) not null,
city varchar(50) not
);

create table if not exists china.factory(
id int not primary key,
city varchar(50) not null,
phone_number varchar(50) not null,
product varchar(50)
price_one float not null,
weight_one float not
);

create table if not exists china.order(
id int not primary key,
type varchar(50) not null,
amount varchar(50) not null,
price_all float not null,
weight_all float not
);

create table if not exists china.transport_company(
if int not primary key,
price_for_kg float not null,
city_export varchar(50) not null,
city_entry varchar(50) not null,
delivery_time int
);

create table china.storage (
id int not primary key,
location varchar(50),
rent int
);
