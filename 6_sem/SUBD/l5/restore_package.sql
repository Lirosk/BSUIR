create or replace package restore_package as
    procedure restore_data(required_time TIMESTAMP);
    procedure restore_data(seconds_shift NUMBER);
end restore_package;

/

create or replace package body restore_package as
    procedure restore_data(required_time TIMESTAMP) as
    begin
        restore_table1 (required_time);
        restore_table2 (required_time);
        restore_table3 (required_time);
    end;
    
    procedure restore_data(seconds_shift NUMBER) is
    shifted_date TIMESTAMP;
    begin
        shifted_date := current_timestamp + numToDSInterval(seconds_shift, 'second');
        restore_table1 (shifted_date);
        restore_table2 (shifted_date);
        restore_table3 (shifted_date);
    end;
end restore_package;
