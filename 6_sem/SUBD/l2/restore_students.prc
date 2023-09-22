create or replace procedure restore_students(t_start in timestamp,
                                             t_end   in timestamp) is
begin
  for i in (select *
              from students_logs
             where timestamp_of_change >= t_start
               and timestamp_of_change <= t_end) loop
    if i.action = 'UPDATE' then
      update students
         set name = i.name, group_id = i.group_id
       where id = i.id;
    elsif i.action = 'DELETE' then
      insert into students
        (id, name, group_id)
      values
        (i.id, i.name, i.group_id);
    end if;
  end loop;
end restore_students;
/
