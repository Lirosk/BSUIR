create or replace function own_func 
return varchar
is
  odd number := 0;
  even number := 0;
begin
  for c in (select * from MyTable)
  loop
    if (mod(c.val, 2) = 0) then
      even := even + 1;
    else
      odd := odd + 1;
    end if;
  end loop;
  
  if (odd = even) then
    return 'EQUAL';
  elsif  (even > odd) then
    return 'TRUE';
	else 
		return 'FALSE';
  end if;
end;
/