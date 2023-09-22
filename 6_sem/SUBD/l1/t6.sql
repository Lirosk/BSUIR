declare
 res number;
begin
	res := fee(5, -5);
	dbms_output.put_line(res);
end;

