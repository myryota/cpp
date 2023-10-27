-- Для оптимизации запросов и ускорения работы с таблицами следует создавать индексы на полях, которые часто используются в условиях WHERE и JOIN, а также на полях по которым происходит группировка и сортировка.Для таблицы china.user создадим индекс на поле city, так как может потребоваться частый поиск по городу:

create index idx_user_city on china.user(city)

-- Для таблицы china.factory создадим индексы на поля city и product, так как так как может потребоваться частый поиск по городу и по продукту:

create index idx_factory_city on china.factory(city)
create index idx_factory_product on china.factory(product)

-- Для таблицы china.order создадим индекс на поле type, так как так как может потребоваться частый поиск по типу:

create index idx_order_type on china.order(type)

-- Для таблицы china.transport_company создадим индекс на полях city_export и city_entry, так как так как может потребоваться частый поиск по городам, куда и откуда доставляют товар:

create index idx_transport_city_export on china.transport_company(city_export)
create index idx_transport_city_entry on china.transport_company(city_entry)

-- Для таблицы china.storage создадим индекс на поле location, так как так как может потребоваться частый поиск по местоположению складов:

create index idx_storage_location on china.storage(location)
