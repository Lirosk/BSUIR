drop table students;
drop table groups;


create table students (
  id number,
		name varchar2(50),
		group_id number
);

alter table students 
add (
  constraint students_pk primary key (id)
);

create table groups (
  id number,
		name varchar(50),
		c_val number
);

alter table groups
add (
  constraint groups_pk primary key (id)
);


insert into groups (id, name, c_val) values (1, '1', 1);
insert into groups (id, name, c_val) values (2, '2', 3);

insert into students (id, name, group_id) values (1, '1_1', 1);
insert into students (id, name, group_id) values (2, '2_2', 2);
insert into students (id, name, group_id) values (3, '3_2', 2);
insert into students (id, name, group_id) values (4, '4_2', 2);
insert into students (id, name, group_id) values (5, '5_3', 3);
insert into students (id, name, group_id) values (6, '6_3', 3);

select * from groups;
select * from students;


create table students2
(
  id number,
  name varchar(1000),
  group_id number
);

select * from students2;

insert into students2 (id, name, group_id) values (-1, '-1', -1);
insert into students2 (id, name, group_id) values (-2, '-2', -2);
insert into students2 (id, name, group_id) values (-3, '-3', -3);

