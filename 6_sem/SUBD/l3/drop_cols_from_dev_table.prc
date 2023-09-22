create or replace procedure drop_cols_from_dev_table(dev_schema_name in varchar,
                                        prod_schema_name in varchar,
                                        tab_name in varchar) as
query_string varchar(200);
begin
    query_string := 'ALTER TABLE ' ||  prod_schema_name || '.' || lower(tab_name);
    for missing_col in (select distinct column_name
                        from all_tab_columns where owner = prod_schema_name
                        and table_name = tab_name  and (table_name, column_name) not in
                        (select table_name, column_name from all_tab_columns where owner = dev_schema_name)) loop
    query_string := query_string || ' DROP COLUMN ' || missing_col.column_name;
    end loop;
    dbms_output.put_line('Executing:');
    dbms_output.put_line(query_string);
    EXECUTE IMMEDIATE query_string;
end;
/
