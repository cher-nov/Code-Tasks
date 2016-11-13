program task1;

procedure DoMax( var aa, bb, cc: Integer );
var
  swap: Integer;
begin
  if ( aa < bb ) then
    begin swap := aa; aa := bb; bb := swap; end;
  if ( aa < cc ) then
    begin swap := aa; aa := cc; cc := swap; end;
  if ( bb < cc ) then
    begin swap := bb; bb := cc; cc := swap; end;
end;

var
  a, b, c: Integer;
begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  Read( Input, a, b, c );
  CloseFile( Input );

  DoMax( a, b, c );

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  Write( Output, a*b );
  CloseFile( Output );
end.

