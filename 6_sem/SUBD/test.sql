declare
  xml_rec xml_record := xml_record();
		cur SYS_REFCURSOR;
		student_id number;
		student_name number;
		student_group_id number;
		group_id number;
		group_name varchar(1000);
begin 
  cur := xml_package.process_xml_select(
		'
		<Command>
		<QueryType>
		  SELECT
		</QueryType>
		<OutputColumns>
		  <Column>students.id</Column>
				<Column>students.name</Column>
				<Column>students.group_id</Column>
		</OutputColumns>
		<Tables>
		  <Table>students</Table>
		</Tables>
		</Command>
		');
		loop
		fetch cur into student_id, student_name, student_group_id;
		exit when cur%notfound;
		
		dbms_output.put_line(student_id || ' ' || student_name || ' ' || student_group_id);
		end loop;
end;
