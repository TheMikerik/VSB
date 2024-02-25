select *
from COURSE
join RUC0066.TEACHER T on COURSE.TEACHER_LOGIN = T.LOGIN
where T.fname = 'Jerry' AND T.LNAME = 'Jordon'




select st.FNAME, st.LNAME, st.EMAIL, st.LOGIN, COUNT(*) as pocet_kurzu
from STUDENT ST
left join RUC0066.STUDENTCOURSE S on ST.LOGIN = S.STUDENT_LOGIN
where ST.EMAIL like '%@vsb.cz'
group by st.FNAME, st.LNAME, st.EMAIL, st.LOGIN



with tab as (
    select t.LNAME, t.LOGIN, c2.CODE
    from TEACHER t
    left join COURSE C2 on t.LOGIN = C2.TEACHER_LOGIN
)


select *
from tab
where cnt = (select max(cnt) from tab)


delete from STUDENTCOURSE
where COURSE_CODE in (
    select c2.CODE
    from COURSE c2
    left join teacher t on c2.TEACHER_LOGIN = t.LOGIN
    where t.FNAME = 'Carl' AND t.LNAME = 'Artis'
    )



select *
from STUDENT s
where s.DATE_OF_BIRTH >= to_date('1997-02-03','YYYY-MM-DD')



SELECT
    EXTRACT(YEAR FROM DATE_OF_BIRTH ) AS rok_narozeni,
    EXTRACT(MONTH FROM DATE_OF_BIRTH) AS mesic_narozeni,
    EXTRACT(DAY FROM DATE_OF_BIRTH) AS den_narozeni
FROM
    STUDENT;


SELECT UPPER(fname) || ' ' || UPPER(lname)
from teacher