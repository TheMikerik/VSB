select distinct p.id_organ, o.prijmeni
from dbo.poslanec p
join dbo.osoba o on p.id_osoba = o.id_osoba
join dbo.zarazeni z on o.id_osoba = z.id_osoba
where o.prijmeni = 'Babiš'

--------------

select o.prijmeni, id_organ, id_kandidatka
from dbo.poslanec p
join dbo.osoba o on p.id_osoba = o.id_osoba
where id_organ = 173
order by id_kandidatka ASC

----------------------


select
    *
from
    organ o
    join dbo.hlasovani h on o.id_organ = h.id_organ
    join dbo.zmatecne_hlasovani_poslanec zhp on h.id_hlasovani = zhp.id_hlasovani
    join osoba s on zhp.id_osoba = s.id_osoba
where
    o.id_organ between 165 and 173
group by
    s.id_osoba, jmeno, prijmeni, o.id_organ