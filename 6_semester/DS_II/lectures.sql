

BEGIN
  INSERT INTO Student (login, fname, lname, email,
    grade, date_of_birth)
  VALUES ('abc123', 'Petr', 'Novak', 'petr.novak@vsb.cz',
    1, TO_DATE('1992/05/06', 'yyyy/mm/dd'));
END;