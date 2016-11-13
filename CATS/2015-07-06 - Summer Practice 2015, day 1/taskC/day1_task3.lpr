program day1_task3;

uses Math;

var
  x1, y1, r1, x2, y2, r2 : Double;
  s, h, a, dist, sub1, sub2 : Double; // dist = sub1 + sub2

begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  Read( Input, x1, y1, r1, x2, y2, r2 );
  CloseFile( Input );

  dist := sqrt( sqr(x2-x1) + sqr(y2-y1) );
  if ( dist > abs(r1-r2) ) then begin
    sub1 := ( sqr(r1) - sqr(r2) + sqr(dist) ) / (2*dist);
    sub2 := dist - sub1;
    if ( dist < r1+r2 ) then begin
      h := sqrt( sqr(r1) - sqr(sub1) );
      a := 2*arctan2(h, sub1);
      s := ( sqr(r1) * a/2 ) - ( h/2 * sub1 ) * 2;
      a := 2*arctan2(h, sub2);
      s += ( sqr(r2) * a/2 ) - ( h/2 * sub2 ) * 2;
    end else
      s := 0;
  end else
    s := pi * sqr( min(r1, r2) );

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  Write( Output, s:0:2 );
  CloseFile( Output );
end.

