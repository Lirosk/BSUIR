delete from table1;
delete from table2;
delete from table3;

delete from table1_audit;
delete from table2_audit;
delete from table3_audit;

insert into table1 (id, char_column) values (1, 'str');
insert into table2
  (id, date_column, table1_fk)
values
  (1, SYSTIMESTAMP, 1);
insert into table3 (id, num_column, table2_fk) values (1, 42, 1);

UPDATE table1 SET char_column = 'str2' WHERE id = 1;
UPDATE table2 SET date_column = SYSTIMESTAMP WHERE id = 1;
UPDATE table3 SET num_column = 43 WHERE id = 1;

DELETE FROM table1;
DELETE FROM table2;
DELETE FROM table3;

/

select * from table1;
select * from table2;
select * from table3;

select * from table1_audit;
select * from table2_audit;
select * from table3_audit;

declare
  restore_to timestamp := TO_TIMESTAMP('25.05.22 13:05:45');
begin
  restore_package.restore_data(restore_to);
  --restore_package.restore_data(10800);
end;