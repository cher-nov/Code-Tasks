//14.05.2015
//yes, it's awful

program supreme;
uses SysUtils;

type
  TDone = ( A_NEXT, A_DONE, A_FAIL );

var
  n, m, i, j, anscnt : Integer;
  TempColor, ColorsNum, CurColor : Integer;
  Colors, RowCounts, ColumnCounts : array of Integer;
  pic : array of array of Integer;
  used : array of array of Boolean;
  answer: AnsiString;
  done : TDone;

//returns filling color (1..1000000) if present or 0 otherwise
function FindFillColor( num: Integer; isRow: Boolean ): Integer;
var
  len, cur, now, cnt, maxcnt : Integer;
begin
  maxcnt := 0;
  if isRow then len := m else len := n;

  for cur := 0 to trunc( (len-1)/2.0 ) do begin
    cnt := 1;
    for now := cur+1 to len-1 do begin
      if isRow then begin
        if ( pic[num, cur] = pic[num, now] ) then cnt += 1;
      end else begin
        if ( pic[cur, num] = pic[now, num] ) then cnt += 1;
      end;
    end;

    if ( cnt = len ) then Exit(0); //exit if already simple
    if ( cnt > maxcnt ) then begin
      if isRow then Result := pic[num, cur]
               else Result := pic[cur, num];
      maxcnt := cnt;
    end;
  end;
  if ( maxcnt < trunc(len/2.0+1) ) then Exit(0); //exit if too hard
end;

function IsKnownColor( Color: Integer ): Boolean;
var
  k : Integer;
begin
  for k := 0 to ColorsNum-1 do
    if ( Colors[k] = Color ) then Exit(True);
  Result := False;
end;

begin

  AssignFile( Input, 'supreme.in' );
  Reset( Input );
  ReadLn( Input, n, m );

  SetLength( pic, n, m );
  for i := 0 to n-1 do
    for j := 0 to m-1 do
      Read( Input, pic[i,j] );

  CloseFile( Input );

  //let's create list of filling colors
  SetLength( Colors, n+m );
  ColorsNum := 0;
  for i := 0 to n-1 do begin
    TempColor := FindFillColor( i, True );
    if ( TempColor > 0 ) and not IsKnownColor( TempColor ) then begin
      Colors[ ColorsNum ] := TempColor;
      ColorsNum += 1;
    end;
  end;
  for j := 0 to m-1 do begin
    TempColor := FindFillColor( j, False );
    if ( TempColor > 0 ) and not IsKnownColor( TempColor ) then begin
      Colors[ ColorsNum ] := TempColor;
      ColorsNum += 1;
    end;
  end;

  //and let's process every color now
  SetLength( RowCounts, n );
  SetLength( ColumnCounts, m );
  SetLength( used, n, m );
  for CurColor := 0 to ColorsNum-1 do begin
    //counting color occurrences in every row and column
    for i := 0 to n-1 do begin
      for j := 0 to m-1 do begin
        if ( pic[i,j] = Colors[ CurColor ] ) then begin
          RowCounts[i] += 1;
          ColumnCounts[j] += 1;
        end;
        used[i,j] := False; //clearing matrix with already colored fields
      end;
    end;

    //trying to make picture simple by current color
    answer := ''; anscnt := 0;
    repeat
      done := A_DONE;

      for i := 0 to n-1 do begin
        if ( RowCounts[i] < m ) then begin
          if ( RowCounts[i] > trunc(m/2.0) ) then begin
            RowCounts[i] := m;
            for j := 0 to m-1 do
              if ( pic[i,j] <> Colors[ CurColor ] ) and not used[i,j] then begin
                ColumnCounts[j] += 1;
                used[i,j] := True;
              end;
            done := A_NEXT;
            answer += 'R ' + IntToStr(i+1) + LineEnding;
            anscnt += 1;
          end else begin
            if ( done = A_DONE ) then done := A_FAIL;
          end;
        end;
      end;

      for j := 0 to m-1 do begin
        if ( ColumnCounts[j] < n ) then begin
          if ( ColumnCounts[j] > trunc(n/2.0) ) then begin
            ColumnCounts[j] := n;
            for i := 0 to n-1 do
              if ( pic[i,j] <> Colors[ CurColor ] ) and not used[i,j] then begin
                RowCounts[i] += 1;
                used[i,j] := True;
              end;
            done := A_NEXT;
            answer += 'C ' + IntToStr(j+1) + LineEnding;
            anscnt += 1;
          end else begin
            if ( done = A_DONE ) then done := A_FAIL;
          end;
        end;
      end;

      if ( anscnt > 1000 ) then done := A_FAIL;
    until ( done <> A_NEXT );

    if ( done = A_DONE ) then
      //if our answer is good, we accept it
      break
    else begin
      //otherwise we clear everything to try next color
      for i := 0 to n-1 do RowCounts[i] := 0;
      for j := 0 to m-1 do ColumnCounts[j] := 0;
    end;
  end;

  AssignFile( Output, 'supreme.out' );
  Rewrite( Output );

  if (ColorsNum = 0) or ( done = A_FAIL ) then
    Write( Output, 'Poor Kazimir' )
  else begin
    WriteLn( Output, anscnt );
    Write( Output, answer );
  end;

  CloseFile( Output );

end.
  
