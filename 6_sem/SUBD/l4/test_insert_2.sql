delete from students where id < 1;
select * from students;


begin
  xml_package.process_xml_dml(
  '
  <Command>
  <Type>INSERT</Type>
  <Columns>
    <Column>students.id</Column>
    <Column>students.name</Column>
    <Column>students.group_id</Column>
  </Columns>
  <Table>students</Table>
  <Command>
    <QueryType>SELECT</QueryType>
    <OutputColumns>
      <Column>*</Column>
    </OutputColumns>
    <Tables>
      <Table>students2</Table>
    </Tables>
  </Command>
  </Command>
  ');
end;


