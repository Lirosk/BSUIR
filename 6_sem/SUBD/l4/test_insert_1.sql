delete from groups where id = -1;
select * from groups;

begin
  xml_package.process_xml_dml(
  '
  <Command>
    <Type>INSERT</Type>
    <Columns>
      <Column>groups.id</Column>
      <Column>groups.name</Column>
      <Column>groups.c_val</Column>
    </Columns>
    <Table>
      groups
    </Table>
    <Values>
      <Value>-1</Value>
      <Value>''-1''</Value>
      <Value>-1</Value>
    </Values>
  </Command>
  ');
end;