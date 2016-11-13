program day4_task1;

type
  state = ( S_NOT, S_NOW, S_DONE );

var
  graph : array of array of Integer;
  done : array of state;
  sort : array of Integer;
  n, m, a, b, i, j, sorted : Integer;
  err : Boolean = False;

function DFS( vx: Integer ): Boolean;
var
  len, ii, num : Integer;
begin
  if ( done[vx] = S_DONE ) then Exit( False );
  done[vx] := S_NOW;
  len := High( graph[vx] );
  if ( len > -1 ) then begin
    for ii := 0 to len do begin
      num := graph[vx][ii];
      if ( done[num] = S_NOW ) then
        Exit( True )
      else
        if DFS( num ) then Exit( True );
    end;
  end;
  done[vx] := S_DONE;
  sorted += 1;
  sort[sorted] := vx+1;
  Result := False;
end;

begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  Read( n, m );

  SetLength( graph, n );
  for i := 0 to m-1 do begin
    Read( a, b );
    a -= 1; //never forget about zero based indices
    j := Length( graph[a] );
    SetLength( graph[a], j+1 );
    graph[a][j] := b-1;
  end;

  CloseFile( Input );
  SetLength( done, n );
  for i := 0 to n-1 do
    done[i] := S_NOT;

  SetLength( sort, n );
  sorted := -1;
  AssignFile( Output, 'output.txt' );
  Rewrite( Output );

  for i := 0 to n-1 do begin
    err := DFS(i);
    if err then Break;
  end;

  if not err then
    for i := sorted downto 0 do Write( sort[i], ' ' )
  else
    Write( '-1' );
  CloseFile( Output );

end.

