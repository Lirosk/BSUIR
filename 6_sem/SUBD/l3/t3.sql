create or replace procedure create_or_replace_object(dev_schema_name in varchar,
                                                     prod_schema_name in varchar,
                                                     object_type in varchar,
                                                     object_name in varchar) as
query_string varchar(200) := '';
begin
    IF object_type = 'PROCEDURE' or object_type = 'FUNCTION' THEN
        FOR src IN (SELECT line, text FROM all_source WHERE owner = dev_schema_name AND name = object_name) 
        LOOP
            IF src.line = 1 THEN
                query_string := 
                'CREATE OR REPLACE ' || replace(src.text, '    ' || lower(object_name), prod_schema_name || '.' || lower(object_name));
            ELSE
                query_string := query_string || src.text;
            END IF;
        END LOOP;
        dbms_output.put_line('Executing:');
        dbms_output.put_line(query_string);
        EXECUTE IMMEDIATE query_string;
    ELSIF object_type = 'TABLE' THEN
        query_string := 'CREATE TABLE ' ||  prod_schema_name || '.' || lower(object_name) || '(';
        FOR col IN (SELECT dev_table.column_name name, dev_table.data_type type, char_length FROM all_tab_columns dev_table
                    where dev_table.owner = dev_schema_name and dev_table.table_name = object_name) LOOP
        IF col.type = 'VARCHAR2' THEN
            query_string := query_string || lower(col.name) || ' ' || col.type || '('|| col.char_length || '), ';
        ELSE
            query_string := query_string || lower(col.name) || ' ' || col.type || ', ';
        END IF;
        END LOOP;
        query_string := SUBSTR(query_string, 1, length(query_string) - 2);
        query_string := query_string || ')';
        dbms_output.put_line('Executing:');
        dbms_output.put_line(query_string);
        EXECUTE IMMEDIATE query_string;
    END IF;
end;
/

create or replace procedure delete_object(prod_schema_name in varchar,
                                                     object_type in varchar,
                                                     object_name in varchar) as
query_string varchar(200);            
begin
    query_string := 'DROP ' || object_type || ' ' || prod_schema_name || '.' || object_name;
    dbms_output.put_line('Executing:');
    dbms_output.put_line(query_string);
    EXECUTE IMMEDIATE query_string;
end;
/

create or replace procedure add_cols_to_prod_table(dev_schema_name in varchar,
                                        prod_schema_name in varchar,
                                        tab_name in varchar) as
query_string varchar(200);
begin
    query_string := 'ALTER TABLE ' ||  prod_schema_name || '.' || lower(tab_name);
    for missing_col in (select distinct column_name, data_type
                        from all_tab_columns where owner = dev_schema_name
                        and table_name = tab_name  and (table_name, column_name) not in
                        (select table_name, column_name from all_tab_columns where owner = prod_schema_name)) loop
    query_string := query_string || ' ADD ' || missing_col.column_name || ' ' || missing_col.data_type;
    end loop;
    dbms_output.put_line('Executing:');
    dbms_output.put_line(query_string);
    EXECUTE IMMEDIATE query_string;

end;
/


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



/
