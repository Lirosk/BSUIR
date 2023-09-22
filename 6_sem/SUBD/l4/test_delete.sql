select * from students;

begin
  xml_package.process_xml_dml (
  '
  <Command>
  <Type>DELETE</Type>
  <Table>students</Table>
  <Where>
    <Conditions>
      <Condition>
        <Body>not id > 0</Body>
      </Condition>
    </Conditions>
  </Where>
  </Command>
  ');
end;