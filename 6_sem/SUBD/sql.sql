create table t (
  f1 number,
		f2 varchar2(256)
);
		

select * from t;


declare 
  r t%rowtype;
begin
  for n in 0..5
		loop
		  insert into t (f1, f2)
				values (n*2, 3*n + 1);
		end loop;
		
		r.f1 := -1;
		r.f2 := -1;
		
		insert into t values r;
end;
	

