create or replace trigger groups_on_insert
  before insert
  on groups 
  for each row
declare
  n number;
begin
  if :new.id is null then
    select groups_sequence.nextval
    into :new.id
    from dual;
  end if; 
  
  select count(*)
  into n
  from groups 
  where id = :new.id;
  
  if n > 0 then
    raise_application_error(-20001, 'Record with given id is exists.');
  end if;
	
	select count(*)
	into n
	from groups
	where name = :new.name;
	
	if n > 0 then
    raise_application_error(-20001, 'Group with given name is exists.');
  end if;
end groups_on_insert;
/
