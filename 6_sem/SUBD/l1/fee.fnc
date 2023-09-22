create or replace function fee(salary in number, annual in number)
  return number is
  invalid_salary exception;
  invalid_annual exception;
begin
  if (salary < 0) then
    raise invalid_salary;
  elsif (annual < 0) then
    raise invalid_annual;
  end if;

  return(1 + annual / 100) * 12 * salary;
exception
  when invalid_salary then
    dbms_output.put_line('Invalid salary.');
    return - 1;
  when invalid_annual then
    dbms_output.put_line('Invalid annual.');
    return - 1;
end fee;
/
