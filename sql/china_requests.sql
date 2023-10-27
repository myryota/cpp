-- Запросы INSERT:
-- 1 Добавить новую фабрику:
insert into china.factory (id, city, phone_number, product, price_one, weight_one) values (11, 'Шанхай',
'+861234567890', 'Рубашки', 1200, 0.5);

-- 2 Добавить новый заказ:
insert into china.order (id, type, amount, price_all, weight_all) values (12, 'Рубашки', 100, 120000, 50);

-- 3 Добавить новую транспортную компанию:
insert into china.transport_company (id, price_for_kg, city_export, city_entry, delivery_time) values (11,
350, 'Шанхай', 'Москва', 25);

-- 4 Добавить новый склад:
INSERT INTO china.storage (id, location, rent) VALUES (12, 'Нанкин', 80);

-- 5 Добавить нового логиста:
INSERT INTO china.logist (id, name, phone_number, city) VALUES (11, 'Катя', '+861234567891', 'Шанхай');

-- 6 Добавить нового пользователя:
INSERT INTO china.user (id, name, phone_number, city) VALUES (12, 'Иван', '+79123456788', 'Сочи');

-- 7 Добавить новую фабрику:
INSERT INTO china.factory (id, city, phone_number, product, price_one, weight_one) VALUES (12, 'Харбин',
'+861234567892', 'Джинсы', 1500, 0.8);

-- 8 Добавить новый заказ:
INSERT INTO china.order (id, type, amount, price_all, weight_all) VALUES (13, 'Джинсы', 50, 75000, 40);

-- 9 Добавить новую транспортную компанию:
INSERT INTO china.transport_company (id, price_for_kg, city_export, city_entry, delivery_time) VALUES (12,
300, 'Харбин', 'Санкт-Петербург', 40);
10 Добавить новый склад:
INSERT INTO china.storage (id, location, rent) VALUES (13, 'Харбин', 90);


--  Запросы SELECT:
-- 1 Получить список всех заказов:
SELECT * FROM china.order;

-- 2 Получить список всех пользователей из города Москва:
SELECT * FROM china.user WHERE city='Москва';

-- 3 Получить информацию о транспортных компаниях, осуществляющих доставку в город Пекин:
SELECT * FROM china.transport_company WHERE city_entry='Пекин';

-- 4 Получить список всех складов:
SELECT * FROM china.storage;

-- 5 Получить информацию о фабриках, расположенных в городе Чунцина:
SELECT * FROM china.factory WHERE city='Чунцина';

-- 6 Получить список всех логистов:
SELECT * FROM china.logist;

-- 7 Получить информацию о транспортных компаниях, цены на доставку которых не превышают 300:
SELECT * FROM china.transport_company WHERE price_for_kg<=300;

-- 8 Получить список всех пользователей:
SELECT * FROM china.user;

-- 9 Получить информацию о складах, аренда которых не превышает 100:
SELECT * FROM china.storage WHERE rent <= 100;

-- 10 Получить список всех фабрик:
SELECT * FROM china.factory;

--  Запросы UPDATE:

-- 1 Изменить цену за килограмм транспортной компании с id=3 на 200:
UPDATE china.transport_company SET price_for_kg=200 WHERE id=3;

-- 2 Изменить город для пользователя с id=1 на 'Санкт-Петербург':
UPDATE china.user SET city='Санкт-Петербург' WHERE id=1;

-- 3 Изменить номер телефона для логиста с id=5 на '+8615026861770':
UPDATE china.logist SET phone_number='+8615026861770' WHERE id=5;

-- 4 Изменить продукт для фабрики с id=6 на 'Футболки':
UPDATE china.factory SET product='Футболки' WHERE id=6;

-- 5 Изменить количество товара в заказе с id=2 на 50:
UPDATE china.order SET amount=50 WHERE id=2;

-- 6 Изменить город для транспортной компании с id=5 на 'Новосибирск':
UPDATE china.transport_company SET city_entry='Новосибирск' WHERE id=5;

-- 7 Изменить арендную плату для склада с id=4 на 110:
UPDATE china.storage SET rent=110 WHERE id=4;

-- 8 Изменить цену за единицу товара для фабрики с id=10 на 2000:
UPDATE china.factory SET price_one=2000 WHERE id=10;

-- 9 Изменить время доставки для транспортной компании с id=2 на 45:
UPDATE china.transport_company SET delivery_time=45 WHERE id=2;

-- 10 Изменить имя для логиста с id=9 на 'Какаши':
UPDATE china.logist SET name='Какаши' WHERE id=9;

--  Запросы DELETE:

-- 1 Удалить пользователя с id=3:
DELETE FROM china.user WHERE id=3;

-- 2 Удалить заказ с id=7:
DELETE FROM china.order WHERE id=7;

-- 3 Удалить склад с id=5:
DELETE FROM china.storage WHERE id=5;

-- 4 Удалить транспортную компанию с id=8:
DELETE FROM china.transport_company WHERE id=8;

-- 5 Удалить фабрику с id=4:
DELETE FROM china.factory WHERE id=4;

-- 6 Удалить логиста с id=6:
DELETE FROM china.logist WHERE id=6;

-- 7 Удалить пользователя с именем 'Холси':
DELETE FROM china.user WHERE name='Холси';

-- 8 Удалить заказы, в которых количество товара меньше 30:
DELETE FROM china.order WHERE amount<30;

--9 Удалить транспортные компании, цены на доставку которых превышают 400:
DELETE FROM china.transport_company WHERE price_for_kg>400;

--10 Удалить склады, арендная плата которых превышает 120:
DELETE FROM china.storage WHERE rent>120;


-- Осмысленные `SELECT`-запросы с использованием `GROUP BY + HAVING`:

-- 1 Вывести города, в которых находятся склады, с суммарной арендной платой более 100:
SELECT location, SUM(rent) as total_rent
FROM china.storage
GROUP BY location
HAVING SUM(rent) > 100;

-- 2 Вывести типы товаров и среднюю цену за единицу для каждого типа, у которых количество товара в заказе более 30:
SELECT type, AVG(price_all/amount) as avg_price
FROM china.order
GROUP BY type
HAVING SUM(amount) > 30;

-- 3 Вывести типы товаров и количество заказов на них, у которых суммарный вес более 6кг:
SELECT type, COUNT(*) as total_orders
FROM china.order
GROUP BY type
HAVING SUM(weight_all) > 10;

-- 4 Вывести города, в которых находятся фабрики, производящие товары с суммарным весом более 0.5кг(по 1 вещи из каждой фабрики):
SELECT city, SUM(weight_one) as total_weight
FROM china.factory
GROUP BY city
HAVING SUM(weight_one) > 0.5;

-- 5 Вывести города, в которых находятся склады, с минимальной арендной платой не более 50:
SELECT location, MIN(rent) as min_rent
FROM china.storage
GROUP BY location
HAVING MIN(rent) <= 70;

-- 6 Вывести города, в которых находятся склады, с наибольшей средней арендной платой:
SELECT location, AVG(rent) as avg_rent
FROM china.storage
GROUP BY location
ORDER BY avg_rent DESC
LIMIT 3;

--  Осмысленные `SELECT`-запросы с использованием `ORDER`:

-- 1 Вывести список пользователей, отсортированный по алфавиту:
SELECT * FROM china.user ORDER BY name ASC;

-- 2 Вывести список фабрик, отсортированный по городам:
SELECT * FROM china.factory ORDER BY city ASC;

-- 3 Вывести список складов, отсортированный по возрастанию номеров:
SELECT * FROM china.storage ORDER BY id ASC;

-- 4 Вывести список логистов, отсортированный по номерам телефонов:
SELECT * FROM china.logist ORDER BY phone_number ASC;

-- 5 Вывести список заказов, отсортированный по убыванию количества:
SELECT * FROM china.order ORDER BY amount DESC;

-- 6 Вывести список транспортных компаний, отсортированный по возрастанию цены за килограмм:
SELECT * FROM china.transport_company ORDER BY price_for_kg ASC;

--  Осмысленные `SELECT`-запросы с использованием `PARTITION BY + ORDER BY`:

-- 1 Вывести среднюю стоимость товара для каждого города, используя разбиение по городам и сортировку по возрастанию стоимости:
SELECT city, AVG(price_one) OVER (PARTITION BY city ORDER BY price_one ASC) AS avg_price
FROM china.factory;
-- 2 Вывести максимальный вес товара для каждого типа товара, используя разбиение по типу товара и сортировку по убыванию веса:
SELECT type, MAX(weight_all) OVER (PARTITION BY type ORDER BY weight_all DESC) AS max_weight
FROM china.order;
-- 3 Вывести минимальную цену за килограмм для каждой транспортной компании, используя разбиение городам отправления и сортировку по возрастанию цены:
SELECT id, MIN(price_for_kg) OVER (PARTITION BY city_export ORDER BY price_for_kg ASC) AS min_price
FROM china.transport_company;

-- 4 Вывести суммарный доход для каждого склада, используя разбиение по городам и сортировку по возрастанию
дохода:
SELECT id, SUM(rent) OVER (PARTITION BY location ORDER BY rent ASC) AS total_income
FROM china.storage;

-- 5 Вывести максимальную цену за единицу товара для каждого города, используя разбиение по городам и
сортировку по убыванию цены:
SELECT city, MAX(price_one) OVER (PARTITION BY city ORDER BY price_one DESC) AS max_price
FROM china.factory;

--6 Вывести среднюю цену продукта для каждого города, сгруппированных по городу и отсортированных по
убыванию средней цены.
SELECT city, product, price_one,
AVG(price_one) OVER (PARTITION BY city ORDER BY price_one DESC) AS avg_price
FROM china.factory
ORDER BY city, avg_price DESC;


--  Осмысленные `SELECT`-запросы с использованием `<func>` - все 3 типа функций - агрегирующие, ранжирующие, смещения:
-- 1 Вывести список городов и среднюю стоимость аренды склада в каждом городе, а также максимальную и
минимальную стоимость аренды склада в этом городе.
SELECT location, AVG(rent) OVER (PARTITION BY location) AS avg_rent,
MAX(rent) OVER (PARTITION BY location) AS max_rent,
MIN(rent) OVER (PARTITION BY location) AS min_rent
FROM china.storage;

-- 2 Вывести список фабрик и среднюю цену за килограмм продукта, производимого на этой фабрике, а также
максимальную и минимальную цену за килограмм на всех фабриках.
SELECT id, product, AVG(price_one) OVER (PARTITION BY id) AS avg_price,
MAX(price_one) OVER () AS max_price,
MIN(price_one) OVER () AS min_price
FROM china.factory;

-- 3 Вывести список заказов, отсортированный по общей стоимости заказа в порядке убывания, а также добавить
столбец с суммарной стоимостью всех заказов до текущего.
SELECT id, type, amount, price_all, weight_all,
SUM(price_all) OVER (ORDER BY price_all DESC) AS total_price
FROM china.order
ORDER BY price_all DESC;

-- 4 Вывести список транспортных компаний и их цены за килограмм для грузов из Пекина, отсортированный по
возрастанию цены, а также добавить номер строки каждой компании в отсортированном списке.
SELECT id, price_for_kg, ROW_NUMBER() OVER (ORDER BY price_for_kg) AS row_num
FROM china.transport_company
WHERE city_export = 'Пекин'
ORDER BY price_for_kg;

-- 5 Вывести список складов и их арендную плату, отсортированный по убыванию арендной платы, а также добавить номер строки каждого склада в отсортированном списке.
SELECT id, location, rent, ROW_NUMBER() OVER (ORDER BY rent DESC) AS row_num
FROM china.storage
ORDER BY rent DESC;
