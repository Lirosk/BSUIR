
select * from mytable;

begin
  delete from MyTable;

  for n in 0 .. 10 loop
    insert into MyTable (id, val) values (n, n);
  end loop;

  for c in (select * from MyTable) loop
    dbms_output.put_line(c.id || ' ' || c.val);
  end loop;
end;
