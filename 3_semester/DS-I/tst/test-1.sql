-- 1) idk nemam xd
-- 2) Vyberte vsechny osoby, ktere se narodily po roce 1990 a pro ne pocty kolikrat byli predsedy a v kolika byli klubec
-- 3) Vyberte vsechny osoby, ktere byly ve strane ANO a nikdy nemeli funcki ministra

---2
select o.id_osoba, o.jmeno, o.prijmeni,(
    select count(*)
    from osoba o1
    join zarazeni z1 on o1.id_osoba = z1.id_osoba
    join funkce f on z1.id_of = f.id_funkce AND z1.cl_funkce = 1
    where o.id_osoba = o1.id_osoba AND
        f.nazev_funkce_cz like '%předseda%'
) as pocet_predseda, (
    select count(*)
    from osoba o1
    join zarazeni z on o1.id_osoba = z.id_osoba
    join organ org on z.id_of = org.id_organ AND z.cl_funkce = 0
    where o.id_osoba = o1.id_osoba AND
        org.nazev_organu_cz like '%klub%'
) as pocet_klubu
from osoba o
where year(o.narozeni) > 1990

---3
select distinct o.id_osoba, o.jmeno, o.prijmeni
from osoba o
where exists(
    select 1
    from osoba o1
    join zarazeni z on o1.id_osoba = z.id_osoba
    join organ org on z.id_of = org.id_organ AND z.cl_funkce = 0
    where org.zkratka = 'ANO' AND
    o1.id_osoba = o.id_osoba
) AND not exists(
    select 1
    from osoba o2
    join zarazeni z on o2.id_osoba = z.id_osoba
    join funkce f on z.id_of = f.id_funkce AND z.cl_funkce = 1
    where f.nazev_funkce_cz like '%ministr%' AND
    o2.id_osoba = o.id_osoba
)
order by o.id_osoba