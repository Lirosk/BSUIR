delete from students;
delete from groups;

insert into students (name, group_id)
values ('s1', 1);

insert into students (name, group_id)
values ('s2', 1);

insert into students (id, name, group_id)
values (2, 's3', 1);

select * from students;


insert into groups (name, c_val)
values ('1', 1);

insert into groups (name, c_val)
values ('2', 2);

insert into groups (name, c_val)
values ('2', 3);

select * from groups;
