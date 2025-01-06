create table flights(
    id integer primary key AUTOINCREMENT,
    origin Text not null,
    destination Text not null,
    duration integer not null
);
insert  into flights
(origin,destination,duration)
values("newyork","annaba",400);