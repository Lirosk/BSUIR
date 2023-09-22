drop table students;
create table students (
 id number, 
 name varchar2(40),
 group_id number
);

alter table students
add (
  constraint students_pk primary key (id)
);

drop table groups;
create table groups (
  id number,
	name varchar2(40),
	c_val number
);

alter table groups 
add (
  constraint groups_pk primary key (id)
);


drop sequence students_sequence;
create sequence students_sequence
start with 1
increment by 1;	


drop sequence groups_sequence;
create sequence groups_sequence
start with 1
increment by 1;
