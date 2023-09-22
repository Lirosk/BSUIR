declare 
  cur SYS_REFCURSOR;
  student_id number;
  student_name varchar(1000);
begin
  open cur for 'select id, name from students';
  
  fetch cursor to
  
  close cur;
end;
