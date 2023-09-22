CREATE OR REPLACE TYPE string_array AS
    VARRAY(3) OF VARCHAR2(10);
    
    
CREATE OR REPLACE FUNCTION create_html (
    stamp          IN TIMESTAMP
) RETURN VARCHAR2 AS
    table_names string_array := string_array('table1', 'table2', 'table3');
    html_document   VARCHAR2(10000) := '
    <!DOCTYPE html>
    <html>
    <head>
        <title>Statistics</title>
    </head>
    <body>';
    operation_count NUMBER;
    sys_ref_c       SYS_REFCURSOR;
    operation_name  VARCHAR(20);
BEGIN
    FOR i IN 1..table_names.count LOOP
        html_document := html_document
                         || chr(10)
                         || '       <h1>'
                         || table_names(i)
                         || '</h1>'
                         || chr(10);
        OPEN sys_ref_c FOR 'SELECT operation, COUNT(*) FROM '
                           || table_names(i)
                           || '_audit '
                           || 'WHERE is_reverted=0 AND change_time <= TO_TIMESTAMP('''
                           || to_char(stamp)
                           || ''') GROUP BY operation';
                

        LOOP
            FETCH sys_ref_c INTO
                operation_name,
                operation_count;
            EXIT WHEN sys_ref_c%notfound;
            html_document := html_document
                             || '       <h2>'
                             || operation_name
                             || ':'
                             || operation_count
                             || '</h2>'
                             || chr(10);
        END LOOP;

        CLOSE sys_ref_c;
    END LOOP;

    html_document := html_document || '    </body>'
                                    || chr(10)
                                    || '    </html>';
    RETURN html_document;
    
END create_html;

/
