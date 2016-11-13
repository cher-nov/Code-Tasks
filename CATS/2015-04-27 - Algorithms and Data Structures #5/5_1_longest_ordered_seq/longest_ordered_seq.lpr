program longest_ordered_seq;

{$LONGSTRINGS ON}

uses SysUtils;

const
  MinInt = -MaxInt-1;

function binsearch( var vec: array of Integer; num: Integer ): Integer;
var
  left, right, mid : Integer;
begin
  left := 0;
  right := High(vec);
  while ( left <= right ) do begin
    mid := (left+right) div 2;
    if ( num > vec[mid] ) then left := mid+1 else right := mid-1;
  end;
  Result := Left;
end;

var
  n, i, j, len : Integer;
  seq, mins, pos, prev : array of Integer;
  answer : String = '';

begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  ReadLn( Input, n );

  SetLength( seq, n );
  for i := 0 to n-1 do
    Read( Input, seq[i] );
  CloseFile( Input );

  SetLength( mins, n+1 );
  SetLength( pos,  n+1 );
  SetLength( prev, n );

  mins[0] := MinInt;
  for i := 1 to n do mins[i] := MaxInt;
  pos[0] := -1;
  len := 0;

  //calculating dynamic
  for i := 0 to n-1 do begin
    j := binsearch( mins, seq[i] );
    if ( ( mins[j-1] < seq[i] ) and ( seq[i] < mins[j] ) ) then begin
      mins[j] := seq[i];
      pos[j] := i;
      prev[i] := pos[j-1];
      if ( j > len ) then len := j;
    end;
  end;

  //restoring elements indexes
  j := pos[len];
  while (j <> -1) do begin
    answer := IntToStr(j+1) + ' ' + answer;
    j := prev[j];
  end;

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  WriteLn( Output, len );
  Write( Output, answer );
  CloseFile( Output );
end.

