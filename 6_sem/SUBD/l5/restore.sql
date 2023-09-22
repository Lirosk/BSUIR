CREATE OR REPLACE PROCEDURE restore_table1 (
    restore_until TIMESTAMP
) AS
BEGIN
    delete from table1;
    
    FOR audit_row IN (
        SELECT
            operation,
            new_char_column,
            id_row,
            change_time
        FROM
            table1_audit
        WHERE
            change_time <= restore_until
            AND is_reverted = 0
    ) LOOP
        CASE audit_row.operation
            WHEN 'UPDATE' THEN
                dbms_output.put_line('UPDATE TABLE1 SET char_column = '
                                     || audit_row.new_char_column
                                     || ' WHERE ID = '
                                     || audit_row.id_row);

                    UPDATE table1
                    SET char_column = audit_row.new_char_column
                    WHERE id = audit_row.id_row;

            WHEN 'DELETE' THEN
                dbms_output.put_line('DELETE FROM table1 WHERE id = ' || audit_row.id_row);
                
                DELETE FROM table1 WHERE id = audit_row.id_row;

            WHEN 'INSERT' THEN
                dbms_output.put_line('INSERT INTO TABLE1(id, char_column) VALUES ('
                                     || audit_row.id_row
                                     || ', '
                                     || audit_row.new_char_column
                                     || ')');

                INSERT INTO table1(id, char_column) VALUES (audit_row.id_row, audit_row.new_char_column);
        END CASE;
    END LOOP;

    UPDATE table1_audit
    SET
        is_reverted = 1
    WHERE
        change_time > restore_until;

END restore_table1;

/

CREATE OR REPLACE PROCEDURE restore_table2 (
    restore_until TIMESTAMP
) AS
BEGIN
    delete from table2;
    
    FOR audit_row IN (
        SELECT
            operation,
            new_date_column,
            new_fk,
            id_row,
            change_time
        FROM
            table2_audit
        WHERE
            change_time <= restore_until
            AND is_reverted = 0
    ) LOOP
        CASE audit_row.operation
            WHEN 'UPDATE' THEN
                dbms_output.put_line('UPDATE TABLE2 SET date_column = '
                                     || audit_row.new_date_column
                                     || ', '
                                     || 'table1_fk = '
                                     || 'audit_row.new_fk'
                                     || ' WHERE ID = '
                                     || audit_row.id_row);

                    UPDATE table2
                    SET date_column = audit_row.new_date_column,
                        table1_fk = audit_row.new_fk
                    WHERE id = audit_row.id_row;

            WHEN 'DELETE' THEN
                dbms_output.put_line('DELETE FROM table2 WHERE id = ' || audit_row.id_row);
                
                DELETE FROM table2 WHERE id = audit_row.id_row;

            WHEN 'INSERT' THEN
                dbms_output.put_line('INSERT INTO INTO table2(id, date_column, table1_fk) VALUES ('
                                     || audit_row.id_row
                                     || ', '
                                     || audit_row.new_date_column
                                     || ', '
                                     || audit_row.new_fk
                                     || ')');

                INSERT INTO table2(id, date_column, table1_fk) VALUES (audit_row.id_row, audit_row.new_date_column, audit_row.new_fk);
        END CASE;
    END LOOP;

    UPDATE table2_audit
    SET
        is_reverted = 1
    WHERE
        change_time > restore_until;

END restore_table2;

/

CREATE OR REPLACE PROCEDURE restore_table3 (
    restore_until TIMESTAMP
) AS
BEGIN
    delete from table3;
    
    FOR audit_row IN (
        SELECT
            operation,
            new_num_column,
            new_fk,
            id_row,
            change_time
        FROM
            table3_audit
        WHERE
            change_time <= restore_until
            AND is_reverted = 0
    ) LOOP
        CASE audit_row.operation
            WHEN 'UPDATE' THEN
                dbms_output.put_line('UPDATE TABLE3 SET date_column = '
                                     || audit_row.new_num_column
                                     || ', '
                                     || 'table1_fk = '
                                     || 'audit_row.new_fk'
                                     || ' WHERE ID = '
                                     || audit_row.id_row);

                    UPDATE table3
                    SET num_column = audit_row.new_num_column,
                        table2_fk = audit_row.new_fk
                    WHERE id = audit_row.id_row;

            WHEN 'DELETE' THEN
                dbms_output.put_line('DELETE FROM table3 WHERE id = ' || audit_row.id_row);
                
                DELETE FROM table3 WHERE id = audit_row.id_row;

            WHEN 'INSERT' THEN
                dbms_output.put_line('INSERT INTO INTO table3(id, num_column, table2_fk) VALUES ('
                                     || audit_row.id_row
                                     || ', '
                                     || audit_row.new_num_column
                                     || ', '
                                     || audit_row.new_fk
                                     || ')');

                INSERT INTO table3(id, num_column, table2_fk) VALUES (audit_row.id_row, audit_row.new_num_column, audit_row.new_fk);
        END CASE;
    END LOOP;

    UPDATE table3_audit
    SET
        is_reverted = 1
    WHERE
        change_time > restore_until;

END restore_table3;

/
