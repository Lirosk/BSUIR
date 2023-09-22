create or replace trigger groups_on_delete
  after delete
  on groups 
  for each row
begin
  delete from students where students.group_id = :old.id;
end groups_on_delete;
/
