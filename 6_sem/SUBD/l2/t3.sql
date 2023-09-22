delete from students;
delete from groups;

insert into groups(id, name, c_val)
values (1, '1', 2);

insert into students (name, group_id)
values ('1', 1);

insert into students (name, group_id)
values ('2', 1);


delete from groups;

select * from students;
select * from groups;

delete from groups where id = 1;
