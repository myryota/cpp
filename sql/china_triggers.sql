-- 1 Первый триггер реагирует на изменение таблицы china.factory и обновлять соответствующие данные в таблице china.order если цена или вес одного продукта изменяется, то соответствующие изменения должны быть учтены в заказах, которые включают этот продукт:

create or replace function update_order()
returns trigger as $$
begin
    update china.order o
    set price_all = o.amount * f.price_one,
        weight_all = o.amount * f.weight_one
    from china.factory f
    where o.type = f.product and o.price_all <> 0.amount * f.price_one;
    return new;
end;
$$ language plpgsql;

create trigger update_order_trigger
after update on china.factory
from each row
execute function update_order();

-- 2 В таблице china.order при добавлении amount, price_one и weight_one автоматически добавляются price_all и weight_all

create or replace function calculate_order_totals()
returns trigger as $$
begin
    new.price_all = new.price_one * new.amount
    new.weight_all = new.weight_one * new.amount
    return new
end;
$$ language plpgsql;
create trigger order_totals_trigger
before insert on china.order
for each row execute function calculate_order_totals();
