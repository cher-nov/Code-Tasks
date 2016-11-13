program mult_puzzle;

var
  cards: array of Integer;
  multmx: array of array of Integer;
  n, i, j, k, step, calc, minc: Integer;

begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  ReadLn( Input, n );

  SetLength( cards, n );
  for i := 0 to n-1 do Read( Input, cards[i] );
  CloseFile( Input );

  SetLength( multmx, n, n );
  for step := 2 to n-1 do begin
    for i := 0 to n-1 - step do begin // subtract one coz we're zero-based
      j := i + step;
      minc := MaxInt;
      for k := i + 1 to j - 1 do begin
        calc := multmx[i,k] + multmx[k,j] + cards[i] * cards[k] * cards[j];
        if ( calc < minc ) then minc := calc;
      end;
      multmx[i,j] := minc;
    end;
  end;

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  Write( Output, multmx[0,n-1] );
  CloseFile( Output );
end.

