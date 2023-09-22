create or replace procedure add_cols_to_dev_table(dev_schema_name in varchar,
    prod_schema_name in varchar,
    tab_name in varchar)
				AS
    query_string varchar(500);
begin
   query_string := 'ALTER TABLE ' ||
                        dev_schema_name || '.' ||
                        lower(tab_name);
        FOR missing_col IN(
            SELECT DISTINCT column_name, data_type
            FROM dba_tab_columns
            WHERE OWNER = prod_schema_name AND 
            table_name = tab_name AND 
            (table_name, column_name) NOT IN (
                SELECT table_name, column_name
                FROM dba_tab_columns
                WHERE OWNER = dev_schema_name))
                LOOP
                    query_string := query_string || 
                                    ' ADD ' || missing_col.column_name || 
                                    ' ' || missing_col.data_type;
                END LOOP;
        DBMS_OUTPUT.PUT_LINE(
        '[TASK_3][DDL] ' ||
        query_string);
        EXECUTE IMMEDIATE query_string;
end add_cols_to_dev_table;
/
