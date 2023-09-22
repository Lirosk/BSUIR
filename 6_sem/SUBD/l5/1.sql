drop table table1;
drop table table2;
drop table table3;


CREATE TABLE table1 (
    id      NUMBER PRIMARY KEY,
    char_column VARCHAR(20)
);

CREATE TABLE table2 (
    id        NUMBER PRIMARY KEY,
    date_column   DATE,
    table1_fk NUMBER,
    CONSTRAINT fk_table2_table1 FOREIGN KEY ( table1_fk )
        REFERENCES table1 ( id )
            ON DELETE CASCADE
);

CREATE TABLE table3 (
    id        NUMBER PRIMARY KEY,
    num_column   NUMBER,
    table2_fk NUMBER,
    CONSTRAINT fk_table3_table2 FOREIGN KEY ( table2_fk )
        REFERENCES table2 ( id )
            ON DELETE CASCADE
);
