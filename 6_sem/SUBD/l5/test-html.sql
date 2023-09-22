declare
    html_doc VARCHAR2(10000);
begin
    html_doc := create_html(TO_TIMESTAMP('25.05.22 13:05:49'));
    dbms_output.put_line(html_doc);
end;
