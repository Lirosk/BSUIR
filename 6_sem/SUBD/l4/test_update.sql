insert into groups (id, name, c_val) values (-3, '3', 0);
select * from groups;

delete from groups where id = 3;

begin
  xml_package.process_xml_dml(
  '
  <Command>
  <Type>UPDATE</Type>
  <Table>groups</Table>
  <SetCommands>
    <Set>id = -id</Set>
  </SetCommands>
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