const
  n = 100;
  m = 10000;

var
  i, j: integer;
  x: text;
  
begin
  assign(x, 'disease.in');
  rewrite(x);
  writeln(x, n, ' ', m);
  for i := 0 to m-1 do begin
    for j := 0 to n-1 do
      if ( (i mod n) = j ) then write(x, '1 ') else write(x, '0 ');
    writeln(x, '1');
  end;
  close(x);
end.