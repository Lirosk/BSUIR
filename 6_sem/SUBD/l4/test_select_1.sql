select * from students;

DECLARE
  cur          SYS_REFCURSOR;
  student_id   NUMBER;
  student_name VARCHAR(1000);
  group_id     NUMBER;
  group_name   VARCHAR(1000);
BEGIN
  cur := xml_package.process_xml_select('
		<Command>
		<QueryType>
		  SELECT
		</QueryType>
		<OutputColumns>
		  <Column>students.id</Column>
          <Column>students.name</Column>
		  <Column>students.group_id</Column>
          <Column>groups.name</Column>
		</OutputColumns>
		<Tables>
		  <Table>students</Table>
          <Table>groups</Table>
		</Tables>
        <Joins>
          <Join>
            <Type>INNER JOIN</Type>
            <Condition>groups.id = students.group_id</Condition>
          </Join>
        </Joins>
        <Where>
          <Conditions>
            <Condition>
              <Body>groups.c_val = 3</Body>
            </Condition>
          </Conditions>
        </Where>
		</Command>
		');
  LOOP
    
    FETCH cur
      INTO student_id, student_name, group_id, group_name;
						
				EXIT WHEN cur%notfound;
    dbms_output.put_line(' | id: ' || student_id || ' | name: ' ||
                         student_name || ' | group_id: ' || group_id ||
                         ' | group_name: ' || group_name || ' |');
  
  END LOOP;

END;