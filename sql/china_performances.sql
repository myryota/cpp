-- 1 Представление china.logist_view:

create view china.logist_view as
select id, name, '***' as phone_number, city from china.logist;

-- 2 Представление china.user_view:

create view china.user_view as
select id, name, '***' as phone_numder, city from china.user;

-- 3 Представление china.order_view:

create view china.order_view as
select id, type, amount, price_all, weight_all from china.order;

-- 4 Представление china.orderstatview:

create view china.orderstatview as
select o.type, sum(o.amount) as totalamount,
sum(o.price_all) as totalprice, avg(o.weight_all) as avgweight,
tc.city_export, tc.city_entry
from china.order o
join china.transport_company tc on o.id = tc.id
group by o.type, tc.city_export, tc.city_export

-- 5 Представление china.factorycityview:

create view china.factorycityview as
select f.product, f.city, count(*) as factories_count,
avg(f.price_one) as avg_price, avg(f.weight_one) as avg_weight
from china.factory f
group by f.product, f.city;

-- 6 Представление china.user_logist_view:

create view china.user_logist_view as
select u.name as user_name, l.name as logist_name,
count(*) as orderscount, sum(o.amount) as totalamount
from china.order o
join china.user u on o.id = u.id
join china.logist l on o.id = l.id
