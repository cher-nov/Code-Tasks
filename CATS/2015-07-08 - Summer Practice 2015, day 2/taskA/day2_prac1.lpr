program day2_prac1;

uses Math;

var
  R, x1, y1, x2, y2, dx1, dy1, dx2, dy2 : Double; //good enough
  a, b, c, D, t : Double;

begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  Read( Input, R, x1, y1, dx1, dy1, x2, y2, dx2, dy2 );
  CloseFile( Input );

  a := sqr(dx2 - dx1) + sqr(dy2 - dy1);
  b := 2.0*(dx2 - dx1)*(x2 - x1) + 2.0*(dy2 - dy1)*(y2 - y1);
  c := sqr(x2 - x1) + sqr(y2 - y1) - 4.0*sqr(R);

  if (a = 0) or (b = 0) then
    t := -1.0
  else begin
    D := sqr(b) - 4.0*a*c;
    t := -b / (2.0*a);
    if (D > 0) then
      t := Min( t + sqrt(D)/(2.0*a), t - sqrt(D)/(2.0*a) )
    else if (D < 0) then
      t := -1.0;
  end;

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  if (t > 0) then Write( Output, t ) else Write( Output, '-1' );
  CloseFile( Output );
end.

