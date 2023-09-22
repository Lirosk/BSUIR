
drop sequence students3_pk_seq;
drop trigger students3_trigger;
drop table students3;

select * from students3;

insert into students3 (name) values ('1st');
insert into students3 (name) values ('2nd');


BEGIN
  xml_package.process_xml_dml('<Command>
    <Type>CREATE</Type>
    <Table>students3</Table>
    <Columns>
        <Column>
            <Name>id</Name>
            <Type>NUMBER</Type>
            <Constraints>
                <Constraint>NOT NULL</Constraint>
            </Constraints>
        </Column>
        <Column>
            <Name>name</Name>
            <Type>VARCHAR(100)</Type>
            <Constraints>
                <Constraint>NOT NULL</Constraint>
            </Constraints>
        </Column>
    </Columns>
    <TableConstraints>
        <PrimaryKey>
            <Columns>
                <Column>id</Column>
            </Columns>
        </PrimaryKey>
    </TableConstraints>
</Command>');
end;
