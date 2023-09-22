create or replace procedure own_update(id_where in number,
                                       val_set  in number) is
begin
  update MyTable set val = val_set where id = id_where;
end own_update;
/
