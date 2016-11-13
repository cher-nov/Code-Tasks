//02.03.2015 (d.m.y)
//let's get dangerous

program carnumbers;

const
  USED = ' ';

type
  Alphabet = array[1..3] of Char;
  pAlphabet = ^Alphabet;

var 
  InputStr : AnsiString;
  Answers : array of AnsiString;
  Counter : Byte;
  SetNums, SetChars : Alphabet;

procedure Generate( ind: Byte = 1; str: String = '' );
var
  i : Byte;
  tmp : Char;
  abc : pAlphabet;
begin
  if (ind > 6) then begin
    //HERR SOME OUTPT
    for i := 0 to Counter do begin
      if (i = Counter) then begin
        Counter += 1;
        SetLength( Answers, Counter );
        Answers[i] := str;
      end else if ( Answers[i] = str ) then break; 
    end;
  end else begin
    if ind in [2..4] then abc := @SetNums else abc := @SetChars;
    for i := 1 to 3 do begin
      if not (abc^[i] = USED) then begin
        tmp := abc^[i]; abc^[i] := USED;
        Generate( ind+1, str+tmp );
        abc^[i] := tmp;
      end;
    end;
  end;
end;
  
begin

  AssignFile( Input, 'numbers.in' );
  Reset     ( Input );
  ReadLn    ( Input, InputStr );
  CloseFile ( Input );

  //let's create alphabets
  SetChars[1] := InputStr[1];
  SetNums [1] := InputStr[2];
  SetNums [2] := InputStr[3];
  SetNums [3] := InputStr[4];
  SetChars[2] := InputStr[5];
  SetChars[3] := InputStr[6];

  Generate();

  AssignFile( Output, 'numbers.out' );
  Rewrite   ( Output );

  WriteLn( Output, Counter );
  for Counter := 0 to Counter-1 do
    WriteLn( Output, Answers[Counter] );

  CloseFile( Output );

end.

