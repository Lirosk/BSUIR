DECLARE
    cur          SYS_REFCURSOR;
    student_id   NUMBER;
    student_name VARCHAR(1000);
    group_id     NUMBER;
BEGIN
    cur := xml_package.process_xml_select('
		<Command>
        <QueryType>
            SELECT
        </QueryType>
        <OutputColumns>
          <Column>*</Column>
        </OutputColumns>
        <Tables>
          <Table>students</Table>
        </Tables>
        <Where>
          <Conditions>
            <Condition>
              <Body>not exists</Body>
              <Command>
              <QueryType>
                SELECT
              </QueryType>
              <OutputColumns>
                <Column>*</Column>
              </OutputColumns>
              <Tables>
                <Table>groups</Table>
              </Tables>
              <Where>
                <Conditions>
                  <Condition>
                    <Body>id = students.group_id</Body>
                  </Condition>
                </Conditions>
              </Where>
              </Command>
            </Condition>
          </Conditions>
        </Where>
        </Command>
		');
    LOOP
        FETCH cur INTO
            student_id,
            student_name,
            group_id;
        EXIT WHEN cur%notfound;
        dbms_output.put_line(' | id: '
                             || student_id
                             || ' | name: '
                             || student_name
                             || ' | group_id: '
                             || group_id
                             || ' |');

    END LOOP;

END;