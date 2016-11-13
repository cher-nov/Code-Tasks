program hotkeys;
   
var
  Used : set of Char;
  Captions : array of AnsiString;
  CaptNum, MinSum, MaxCount : Integer;
  Answer, Solution : array of Integer;

procedure Solve( const num : Integer = 0; const sum : Integer = 0;
  const cnt : Integer = 0 );
var
  i : Integer;
  WordUsed : set of Char;
begin
  if (MaxCount = CaptNum) and (MinSum = CaptNum) then Exit;
  if (sum > MinSum) and (MinSum > 0) then Exit;
  if (cnt+CaptNum-num < MaxCount) then Exit;
   
  if (num = CaptNum) then begin
    if (cnt > MaxCount) or (sum < MinSum) then begin
      Solution := Copy( Answer, 0, CaptNum );
      MinSum := sum;
      MaxCount := cnt;
    end;
  end else begin
    WordUsed := [];
    for i := 1 to Length( Captions[num] ) do begin
      if not ( Captions[num][i] in Used ) and 
         not ( Captions[num][i] in WordUsed ) then begin
        Include( Used, Captions[num][i] );
        Include( WordUsed, Captions[num][i] );
        Answer[num] := i;
        Solve( num+1, sum+i, cnt+1 );
        Answer[num] := 0;
        Exclude( Used, Captions[num][i] );
      end;
    end;
    Solve( num+1, sum+i+1, cnt );
  end;
end;

begin
   
  AssignFile( Input, 'input.txt' );
  Reset     ( Input );
   
  ReadLn( Input, CaptNum );
  SetLength( Captions, CaptNum );
  SetLength( Answer, CaptNum );
  for CaptNum := 1 to CaptNum do
    ReadLn( Input, Captions[ CaptNum-1 ] );
   
  CloseFile( Input );
   
  Solve();

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  for CaptNum := 0 to CaptNum-1 do begin
    if (Solution[CaptNum] > 0) then
      Insert( '&', Captions[CaptNum], Solution[CaptNum] );
    WriteLn( Output, Captions[CaptNum] );
  end;
  CloseFile( Output );
   
end.
