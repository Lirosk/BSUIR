create or replace trigger students_on_change
  after insert or update or delete
  on students 
  for each row
declare
  id number;
		name varchar(40);
		group_id number;
		timestamp_of_change timestamp;
		action varchar2(30);
begin
  timestamp_of_change := current_timestamp;

  if INSERTING then
		   id := :new.id;
					name := :new.name;
					group_id := :new.group_id;
					action := 'INSERT';
		else
		   id := :old.id;
					name := :old.name;
					group_id := :old.group_id;
					
					if UPDATING then
					   action := 'UPDATE';
					else
					   action := 'DELETE';
					end if;
		end if;
		
		insert into students_logs (
		       id,
									name,
									group_id,
									timestamp_of_change,
									action)
		values (
		       id,
         name,
         group_id,
         timestamp_of_change,
         action);
end students_on_change;
/
