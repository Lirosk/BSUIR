create or replace procedure own_delete(id_where in number) is
begin
  delete from MyTable where id = id_where;
end own_delete;
/
