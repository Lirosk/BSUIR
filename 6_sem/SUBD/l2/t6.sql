delete from groups;
delete from students;

insert into groups (id, name, c_val) values (1, '2', 0);

insert into students (id, name, group_id) values (1, '2', 1);

select * from groups;
select * from students;
