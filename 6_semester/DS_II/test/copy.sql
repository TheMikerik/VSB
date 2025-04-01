declare 
  v_cnt int := 0;
  v_cntSum int := 0;
  v_start number := dbms_utility.get_time();
begin
  insert into z_field_of_science select * from rvvi2023.z_field_of_science;
  insert into z_field_ford select * from rvvi2023.z_field_ford;
  insert into z_journal select * from rvvi2023.z_journal;
  insert into z_year_field_journal select * from rvvi2023.z_year_field_journal;
  insert into z_institution select * from rvvi2023.z_institution;
  insert into z_author select * from rvvi2023.z_author;
  insert into z_article select * from rvvi2023.z_article;
  insert into z_article_institution select * from rvvi2023.z_article_institution;
  insert into z_article_author select * from rvvi2023.z_article_author;
 
  commit;

  select count(*) into v_cnt from z_year_field_journal;
  v_cntSum := v_cntsum + v_cnt;
  select count(*) into v_cnt from z_field_ford;
  v_cntSum := v_cntsum + v_cnt;
  select count(*) into v_cnt from z_field_of_science;
  v_cntSum := v_cntSum + v_cnt;
  select count(*) into v_cnt from z_article_institution;
  v_cntSum := v_cntSum + v_cnt;
  select count(*) into v_cnt from z_institution;
  v_cntSum := v_cntSum + v_cnt;
  select count(*) into v_cnt from z_article_author;
  v_cntSum := v_cntSum + v_cnt;
  select count(*) into v_cnt from z_author;
  v_cntSum := v_cntSum + v_cnt;
  select count(*) into v_cnt from z_article;
  v_cntSum := v_cntSum + v_cnt;
  select count(*) into v_cnt from z_journal;
  v_cntSum := v_cntSum + v_cnt;
  
  dbms_output.put_line('#Inserted records: ' || v_cntSum);
  dbms_output.put_line('Insert time: ' || round((dbms_utility.get_time-v_start)/100, 2) || 's');  
exception
  when others then
    dbms_Output.put_line(dbms_utility.format_error_stack());
    dbms_Output.put_line(dbms_utility.format_error_backtrace());  
    rollback;
end;