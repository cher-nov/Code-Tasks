//13.02.2015 (d.m.y)

program equation;

var
  n, y, cnt: LongWord;
  workf: Text;
begin
  Assign( workf, 'equation.in' );
  Reset ( workf );
  Read  ( workf, n );
  Close ( workf );

  while (y+1)*(y+1) <= n+1 do begin
    if ( (n-y) mod (1+y) = 0 ) then cnt += 2;
    y += 1;
  end;
  if ( sqr(trunc(sqrt( n+1 ))) = n+1 ) then cnt -= 1;

  Assign ( workf, 'equation.out' );
  Rewrite( workf );
  Write  ( workf, cnt );
  Close  ( workf );
end.
