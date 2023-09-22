create or replace function insert_gen(id_val in number) return varchar is
  val_val number;
begin
  select val
    into val_val
    from MyTable
   where id = id_val
     and rownum = 1;

  RETURN utl_lms.format_message('insert into MyTable(id, val) values (%s, %s);',
                                to_char(id_val),
                                to_char(val_val));
end insert_gen;
/
