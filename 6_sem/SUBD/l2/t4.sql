drop table students_logs;
create table students_logs (
 id number,
	name varchar(40),
	group_id number,
	timestamp_of_change timestamp,
	action varchar(30)
);

-- students_on_change

insert into students (name, group_id)
values ('1', 1);

update students set
group_id = 2
where group_id = 1;

delete from students;

select * from students;

select * from students_logs;

