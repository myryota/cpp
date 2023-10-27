-- 1 Хранимая процедура для удаления заказа по его ID:

create procedure china.delete_order(order_id int)
as
$$ delete from china.order where id = order_id $$ language sql

-- 2 Процедура для обновления поля "price_one" в таблице "china.factory" по ID фабрики:

create procedure china.updatefactoryprice
    (factoryid int, newprice float)
as
$$
    update china.factory set price_one = newprice where id = factoryid
$$ language sql
