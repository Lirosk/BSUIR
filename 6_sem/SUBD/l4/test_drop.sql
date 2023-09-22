select * from students3;

begin
    xml_package.process_xml_dml(
    '<Command>
        <Type>DROP</Type>
        <Table>students3</Table>
    </Command>
				');
end;
