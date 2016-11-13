//26.02.2015 (d.m.y)
//let's try another way

program computers;

var
  TasksNum, i : Byte;
  MinDiff, Answer : Word;
  TaskTime : array of Word;

procedure DoSolution( Comp1, Comp2, Depth: Word );
var
  diff : Word;
begin

  if (Depth = TasksNum) then begin

    diff := Abs( Comp1-Comp2 );
    if diff < MinDiff then begin
      MinDiff := diff;
      if (Comp1 > Comp2) then Answer := Comp1 else Answer := Comp2;
    end;

  end else begin

    DoSolution( Comp1 + TaskTime[Depth], Comp2, Depth + 1 );
    DoSolution( Comp1, Comp2 + TaskTime[Depth], Depth + 1 );

  end;

end;

begin

  Assign( Input, 'input.txt' );
  Reset ( Input );

  Read( Input, TasksNum );
  SetLength( TaskTime, TasksNum );
  for i := 0 to TasksNum - 1 do
    Read( Input, TaskTime[i] );

  CloseFile( Input );
  MinDiff := 20000; //20 (max tasks) * 1000 (max time)
  DoSolution( 0, 0, 0 );

  Assign ( Output, 'output.txt' );
  Rewrite( Output );
  Write  ( Output, Answer );

  CloseFile( Output )

end.
