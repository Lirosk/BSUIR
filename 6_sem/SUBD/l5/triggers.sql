CREATE OR REPLACE TRIGGER table1_audit_trigger BEFORE
    DELETE OR INSERT OR UPDATE ON table1
    FOR EACH ROW
BEGIN
    CASE
        WHEN inserting THEN
            INSERT INTO table1_audit (
                operation,
                change_time,
                is_reverted,
                new_char_column,
                id_row
            ) 
												VALUES (
                'INSERT',
                current_timestamp,
                0,
                :new.char_column,
                :new.id
            );

        WHEN deleting THEN
            INSERT INTO table1_audit (
                operation,
                change_time,
                is_reverted,
                old_char_column,
                id_row
            ) VALUES (
                'DELETE',
                current_timestamp,
                0,
                :old.char_column,
                :old.id
            );

        WHEN updating THEN
            INSERT INTO table1_audit (
                operation,
                change_time,
                is_reverted,
                new_char_column,
                old_char_column,
                id_row
            ) VALUES (
                'UPDATE',
                current_timestamp,
                0,
                :new.char_column,
                :old.char_column,
                :old.id
            );

    END CASE;
END;

/


CREATE OR REPLACE TRIGGER table2_audit_trigger BEFORE
    DELETE OR INSERT OR UPDATE ON table2
    FOR EACH ROW
BEGIN
    CASE
        WHEN inserting THEN
            INSERT INTO table2_audit (
                operation,
                change_time,
                is_reverted,
                new_date_column,
                new_fk,
                id_row
            ) VALUES (
                'INSERT',
                current_timestamp,
                0,
                :new.date_column,
                :new.table1_fk,
                :new.id
            );

        WHEN deleting THEN
            INSERT INTO table2_audit (
                operation,
                change_time,
                is_reverted,
                old_date_column,
                old_fk,
                id_row
            ) VALUES (
                'DELETE',
                current_timestamp,
                0,
                :old.date_column,
                :old.table1_fk,
                :old.id
            );

        WHEN updating THEN
            INSERT INTO table2_audit (
                operation,
                change_time,
                is_reverted,
                new_date_column,
                old_date_column,
                old_fk,
                new_fk,
                id_row
            ) VALUES (
                'UPDATE',
                current_timestamp,
                0,
                :new.date_column,
                :old.date_column,
                :new.table1_fk,
                :old.table1_fk,
                :old.id
            );

    END CASE;
END;

/

CREATE OR REPLACE TRIGGER table3_audit_trigger BEFORE
    DELETE OR INSERT OR UPDATE ON table3
    FOR EACH ROW
BEGIN
    CASE
        WHEN inserting THEN
            INSERT INTO table3_audit (
                operation,
                change_time,
                is_reverted,
                new_num_column,
                new_fk,
                id_row
            ) VALUES (
                'INSERT',
                current_timestamp,
                0,
                :new.num_column,
                :new.table2_fk,
                :new.id
            );

        WHEN deleting THEN
            INSERT INTO table3_audit (
                operation,
                change_time,
                is_reverted,
                old_num_column,
                old_fk,
                id_row
            ) VALUES (
                'DELETE',
                current_timestamp,
                0,
                :old.num_column,
                :old.table2_fk,
                :old.id
            );

        WHEN updating THEN
            INSERT INTO table3_audit (
                operation,
                change_time,
                is_reverted,
                new_num_column,
                old_num_column,
                old_fk,
                new_fk,
                id_row
            ) VALUES (
                'UPDATE',
                current_timestamp,
                0,
                :new.num_column,
                :old.num_column,
                :new.table2_fk,
                :old.table2_fk,
                :old.id
            );

    END CASE;
END;

/
