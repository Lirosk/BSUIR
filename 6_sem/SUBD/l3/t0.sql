create tablespace subd
datafile 'subd.dat'
size 20m
online;

drop user c##prod cascade;
CREATE USER c##prod
IDENTIFIED BY prod
default tablespace subd;

GRANT CREATE SESSION TO c##prod;
GRANT CREATE ANY TABLE TO c##prod;
GRANT CREATE ANY PROCEDURE TO c##prod;
GRANT CREATE ANY TRIGGER TO c##prod;
GRANT CREATE ANY SEQUENCE TO c##prod;
GRANT CREATE ANY VIEW TO c##prod;

DROP TABLE c##prod.customers;

CREATE TABLE c##prod.customers(
    id NUMBER NOT NULL,
    name VARCHAR(20),
    CONSTRAINT customer_pk PRIMARY KEY(id)
);

ALTER TABLE c##prod.customers
    ADD (
        huh NUMBER,
        huh2 NUMBER);


CREATE TABLE c##prod.to_delete(
    id NUMBER NOT NULL,
    name VARCHAR(20)
);


DROP TABLE c##prod.purchases;
DROP PROCEDURE c##prod.dummy_proc;
DROP FUNCTION c##prod.dummy_func;

DROP FUNCTION c##prod.to_delete_func;
CREATE OR REPLACE FUNCTION c##prod.to_delete_func
RETURN NUMBER
IS
BEGIN
    RETURN 0;
END;

CREATE TABLE c##prod.Ya_zdam(
    id NUMBER NOT NULL,
    name VARCHAR(20)
);



CREATE USER c##dev
IDENTIFIED BY dev
default tablespace subd;

GRANT CREATE SESSION TO c##dev;
GRANT CREATE ANY TABLE TO c##dev;
GRANT CREATE ANY PROCEDURE TO c##dev;
GRANT CREATE ANY TRIGGER TO c##dev;
GRANT CREATE ANY SEQUENCE TO c##dev;
GRANT CREATE ANY VIEW TO c##dev;

DROP TABLE c##dev.customers;

CREATE TABLE c##dev.customers(
    id NUMBER NOT NULL,
    name VARCHAR(20),
    CONSTRAINT customer_pk PRIMARY KEY(id)
);

ALTER TABLE c##dev.customers
    ADD (
        last_name VARCHAR(20),
        age NUMBER);


DROP TABLE c##dev.purchases;

CREATE TABLE c##dev.purchases(
    id NUMBER NOT NULL,
    customer_id NUMBER,
    name VARCHAR(20),
    price NUMBER,
    CONSTRAINT purchase_pk PRIMARY KEY(id),
    CONSTRAINT customer_fk FOREIGN KEY(customer_id) 
    REFERENCES c##dev.customers(id)
)

CREATE OR REPLACE PROCEDURE c##dev.dummy_proc
IS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Dummy');
END;

DROP FUNCTION c##dev.dummy_func;
CREATE OR REPLACE FUNCTION c##dev.dummy_func
RETURN NUMBER
IS
BEGIN
    RETURN 0;
END;

CREATE OR REPLACE PACKAGE c##dev.dummy_pack
IS
    FUNCTION huh RETURN VARCHAR2;
END;

CREATE OR REPLACE FUNCTION c##dev.ya_ne_zdam
RETURN NUMBER
IS
BEGIN
    RETURN 0;
END;
    
