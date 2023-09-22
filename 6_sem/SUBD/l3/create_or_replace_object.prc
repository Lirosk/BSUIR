create or replace procedure create_or_replace_object(dev_schema_name IN VARCHAR,
    prod_schema_name IN VARCHAR,
    obj_type IN VARCHAR,
    obj_name IN VARCHAR)
				AS
    query_string varchar(500) := '';
begin
  IF obj_type = 'TABLE' THEN
            query_string := 'CREATE TABLE ' 
                            ||  prod_schema_name
                            || '.' || 
                            lower(obj_name) || '(';
            FOR col IN (
                SELECT dev_table.column_name name, 
                        dev_table.data_type type, 
                        char_length 
                FROM dba_tab_columns dev_table
                WHERE dev_table.owner = dev_schema_name AND 
                dev_table.table_name = obj_name)
            LOOP
                IF col.type = 'VARCHAR2' THEN
                    query_string := query_string || 
                                    lower(col.name) || 
                                    ' ' || col.type || 
                                    '('|| col.char_length || 
                                    '), ';
                ELSE
                    query_string := query_string || 
                                    lower(col.name) || ' ' || 
                                    col.type || ', ';
                END IF;
            END LOOP;
            query_string := SUBSTR(query_string, 1, length(query_string) - 2);
            query_string := query_string || ')';
            DBMS_OUTPUT.PUT_LINE(
            '[TASK_3][DDL] ' ||
            query_string);
            EXECUTE IMMEDIATE query_string;
        ELSIF obj_type = 'PROCEDURE' OR obj_type = 'FUNCTION' THEN
            FOR src IN (
                SELECT line, text FROM dba_source
                WHERE owner = dev_schema_name AND name = obj_name) 
            LOOP
                IF src.line = 1 THEN
                    query_string := 
                    'CREATE OR REPLACE ' || 
                    REPLACE(
                    src.text, 
                    lower(obj_name),
                    prod_schema_name || '.' || lower(obj_name));
                ELSE
                    query_string := query_string || src.text;
                END IF;
            END LOOP;
            DBMS_OUTPUT.PUT_LINE(
            '[TASK_3][DDL] ' ||
            query_string);
            EXECUTE IMMEDIATE query_string;
        END IF;
end create_or_replace_object;
/
