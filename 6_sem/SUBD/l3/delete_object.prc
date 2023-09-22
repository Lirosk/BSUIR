create or replace procedure delete_object(prod_schema_name IN VARCHAR,
    object_type IN VARCHAR,
    object_name IN VARCHAR)
				AS
    query_string varchar(500);   
begin
  query_string := 'DROP ' ||
                        object_type || ' ' || 
                        prod_schema_name || '.' || 
                        object_name;
        DBMS_OUTPUT.PUT_LINE(
        '[TASK_3][DDL] ' ||
        query_string);
        EXECUTE IMMEDIATE query_string;
end delete_object;
/
