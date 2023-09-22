create or replace trigger students_on_insert
  before insert on students
  for each row
declare
  n number;
begin
  if :new.id is null then
		select students_sequence.nextval
		into :new.id
		from dual;
	end if;	
	
	select count(*)
	into n
	from students 
	where id = :new.id;
	
	if n > 0 then
		raise_application_error(-20001, 'Record with given id is exists.');
	end if;
	
end students_on_insert;
/
