create or replace procedure own_insert(id_insert  in number,
                                       val_insert in number) is
begin
  insert into MyTable (id, val) values (val_insert, val_insert);
end own_insert;
/