program day4_task3;

type
  TEdge = record
    Num: Integer;
    EndVx: Integer;
  end;

var
  n, m, k, i, j : Integer;
  graph : array of array of TEdge;
  sizes, cycle : array of Integer;
  used : array of Boolean;
  fail : Boolean = False;
  clen : Integer = 0;

procedure Eulerian( vx: Integer = 0 );
var
  ii : Integer;
begin
  for ii := 0 to sizes[vx]-1 do
    if not used[ graph[vx][ii].Num ] then begin
      used[ graph[vx][ii].Num ] := True;
      Eulerian( graph[vx][ii].EndVx );
    end;

  clen += 1;
  SetLength( cycle, clen );
  cycle[clen-1] := vx;
end;

begin

  AssignFile( Input, 'input.txt' );
  Reset( Input );
  Read( n, m );

  SetLength( graph, n );
  SetLength( sizes, n );
  for k := 0 to m-1 do begin
    Read( i, j );
    i -= 1; j -= 1; //ZERO-BASED!!1

    sizes[i] += 1;
    SetLength( graph[i], sizes[i] );
    graph[i][ sizes[i]-1 ].Num := k;
    graph[i][ sizes[i]-1 ].EndVx := j;

    sizes[j] += 1;
    SetLength( graph[j], sizes[j] );
    graph[j][ sizes[j]-1 ].Num := k;
    graph[j][ sizes[j]-1 ].EndVx := i;
  end;

  //checking graph for eulerian cycle existence
  for i := 0 to n-1 do begin
    fail := ( sizes[i] mod 2 ) = 1;
    if fail then Break;
  end;

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );

  if not fail then begin
    SetLength( used,  m );
    Eulerian();
    for i := clen-1 downto 0 do
      Write( cycle[i]+1, ' ' ) 
  end else
    Write( '-1' );

  CloseFile( Output );

end.

