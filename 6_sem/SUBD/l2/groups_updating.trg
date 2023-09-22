create or replace trigger groups_updating
  after insert or update or delete on students
  for each row
declare
  n number;
begin
  if inserting then
    select count(*) into n from groups where groups.id = :new.group_id;
  
    if n > 0 then
    
      update groups
         set groups.c_val = groups.c_val + 1
       where groups.id = :new.group_id;
    
    end if;
  
  elsif updating then
    select count(*) into n from groups where groups.id = :old.group_id;
  
    if n > 0 then
    
      update groups
         set groups.c_val = groups.c_val - 1
       where groups.id = :old.group_id;
    
    end if;
  
    select count(*) into n from groups where groups.id = :new.group_id;
  
    if n > 0 then
    
      update groups
         set groups.c_val = groups.c_val + 1
       where groups.id = :new.group_id;
    
    end if;
  
  elsif deleting then
    select count(*) into n from groups where groups.id = :old.group_id;
  
    if n > 0 then
    
      update groups
         set groups.c_val = groups.c_val - 1
       where groups.id = :old.group_id;
    
    end if;
  
  end if;
end groups_updating;
/
