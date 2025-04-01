-- rvvi2023_create for Oracle
-- 2025, db.cs.vsb.cz

drop table z_year_field_journal;
drop table z_field_ford;
drop table z_field_of_science;
drop table z_article_institution;
drop table z_institution;
drop table z_article_author;
drop table z_author;
drop table z_article;
drop table z_journal;

create table z_journal
(
  jid int,
  name nvarchar2(200) not null,
  issn varchar(10) null,
  eissn varchar(10) null,
  czech_or_slovak varchar(4) null,
  constraint z_journal_pk primary key(jid)
);

create table z_article
(
  aid int,
  jid int null,
  UT_WoS varchar(25) null,
  name nvarchar2(1000) not null,
  type nvarchar2(40) null,
  year int not null,
  author_count int null,
  institution_count int null,
  constraint z_article_pk primary key(aid),
  constraint z_article_jid_fk foreign key(jid) references z_journal
);

create table z_author
(
  rid int,
  name nvarchar2(200) not null,
  vedidk int null,
  vsbdpt int null,
  constraint z_author_pk primary key(rid)
);

create table z_article_author
(
  aid int not null,
  rid int not null,
  constraint z_article_author_pk primary key(aid, rid),
  constraint z_article_author_aid_fk foreign key(aid) references z_article,
  constraint z_article_author_rid_fk foreign key(rid) references z_author
);

create table z_institution
(
  iid int,
  name nvarchar2(1000) not null,
  reg_number varchar(20) null,
  street nvarchar2(500) null,
  postal_code varchar(10) null,
  town nvarchar2(200) null,
  legal_form nvarchar2(500) null,
  main_goal nvarchar2(2000) null,
  created date null,
  constraint z_institution_pk primary key(iid)
);

create table z_article_institution
(
  aid int not null,
  iid int not null,
  constraint z_article_institution_pk primary key(aid, iid),
  constraint z_article_institution_aid_fk foreign key(aid) references z_article,
  constraint z_article_institution_iid_fk foreign key(iid) references z_institution
);

create table z_field_of_science
(
  sid int,
  name nvarchar2(50) not null,
  constraint z_field_of_science_pk primary key(sid)
);

create table z_field_ford
(
  fid int,
  sid int not null,
  name nvarchar2(100) not null,
  constraint z_field_ford_pk primary key(fid),
  constraint z_field_ford_sid_fk foreign key(sid) references z_field_of_science
);

create table z_year_field_journal
(
  fid int,
  jid int,
  year int,
  article_count int null,
  ranking varchar(6) not null,
  constraint z_year_field_journal_pk primary key(fid, jid, year),
  constraint z_year_field_journal_fid_fk foreign key(fid) references z_field_ford,
  constraint z_year_field_journal_jid_fk foreign key(jid) references z_journal
);