CREATE TABLE table1_audit (
    operation VARCHAR(100),
    change_time timestamp,
    is_reverted number(1),
    old_char_column varchar(20),
    new_char_column varchar(20),
    id_row number
);

CREATE TABLE table2_audit (
    operation VARCHAR(100),
    change_time timestamp,
    is_reverted number(1),
    old_date_column date,
    new_date_column date,
    old_fk number,
    new_fk number,
    id_row number
);

CREATE TABLE table3_audit (
    operation VARCHAR(100),
    change_time timestamp,
    is_reverted number(1),
    old_num_column number,
    new_num_column number,
    old_fk number,
    new_fk number,
    id_row number
);