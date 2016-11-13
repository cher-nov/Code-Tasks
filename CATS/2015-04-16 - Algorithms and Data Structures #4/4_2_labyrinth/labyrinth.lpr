//14.06.2015
//let it burns
program labyrinth;

{$LONGSTRINGS ON}

const
  CHAR_PATH = '.';
//CHAR_WALL = '#';

type
  TDir = ( DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT );

  PVertex = ^TVertex;
  TVertex = record
    Link : array[TDir] of PVertex;
    Dist : Integer; //shortest distance from start
  end;

  PQueueNode = ^TQueueNode;
  TQueueNode = record
    Vertex : PVertex;
    Next   : PQueueNode;
  end;

  PQueue = ^TQueue;
  TQueue = record
    First : PQueueNode;
    Last  : PQueueNode;
  end;

  procedure QueueVertex( Queue: PQueue; Vertex: PVertex; Dist: Integer );
  begin
    if ( Vertex = nil ) then Exit;
    if ( Vertex^.Dist > 0 ) then Exit;

    if ( Queue^.First = nil ) then begin
      New( Queue^.First );
      Queue^.Last := Queue^.First;
    end else begin;
      New( Queue^.Last^.Next );
      Queue^.Last := Queue^.Last^.Next;
    end;

    Queue^.Last^.Vertex := Vertex;
    Queue^.Last^.Next := nil;
    Vertex^.Dist := Dist;
  end;

  function DequeueVertex( Queue: PQueue ): PVertex;
  var
    next : PQueueNode;
  begin
    Result := Queue^.First^.Vertex;
    next := Queue^.First^.Next;
    Dispose( Queue^.First );
    Queue^.First := next;
  end;

var
  vrstart, vrexit : PVertex;
  Map : array of array of PVertex;
  x, y, len, xstart, ystart, xexit, yexit : Integer;
  row : String;
  BFSQueue : TQueue;

function LinkToAnother( xx, yy: Integer; Dir: TDir ): Boolean;
var
  lx, ly : Integer;
  ldir : TDir;
begin
  case Dir of
    DIR_UP:    begin lx := xx; ly := yy-1; ldir := DIR_DOWN;  end;
    DIR_DOWN:  begin lx := xx; ly := yy+1; ldir := DIR_UP;    end;
    DIR_LEFT:  begin ly := yy; lx := xx-1; ldir := DIR_RIGHT; end;
    DIR_RIGHT: begin ly := yy; lx := xx+1; ldir := DIR_LEFT;  end;
  end;

  Result := True;
  if ( lx < 0 ) or ( lx >= len ) then Result := False else
    //if X of another vertex is out of map edges
  if ( ly < 0 ) or ( ly >= len ) then Result := False else
    //if Y of another vertex is out of map edges
  if ( Map[lx,ly] = nil ) then Result := False;
    //if we run against wall or vertex that is not loaded yet

  if Result then begin
    Map[xx,yy]^.Link[ Dir] := Map[lx,ly];
    Map[lx,ly]^.Link[ldir] := Map[xx,yy];
  end else
    Map[xx,yy]^.Link[Dir] := nil;
end;

begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  ReadLn( Input, len, xstart, ystart, xexit, yexit );
  xstart -= 1; ystart -= 1; //because our indices
  xexit  -= 1; yexit  -= 1; //are zero-based

  //building graph
  SetLength( Map, len, len );
  for y := 0 to len-1 do begin
    ReadLn( Input, row );
    for x := 0 to len-1 do begin
      if ( row[x+1] = CHAR_PATH ) then begin
        New( Map[x,y] );
        LinkToAnother( x, y, DIR_UP    );
        LinkToAnother( x, y, DIR_DOWN  );
        LinkToAnother( x, y, DIR_LEFT  );
        LinkToAnother( x, y, DIR_RIGHT );
        Map[x,y]^.Dist := 0;
        if ( x = xstart ) and ( y = ystart ) then vrstart := Map[x,y];
        if ( x = xexit  ) and ( y = yexit  ) then vrexit  := Map[x,y];
      end else
        Map[x,y] := nil;
    end;
  end;
  
  CloseFile( Input );

  //breadth-first search (BFS)
  BFSQueue.First := nil;
  BFSQueue.Last := nil;
  while ( vrstart <> vrexit ) do begin
    QueueVertex( @BFSQueue, vrstart^.Link[DIR_UP],    vrstart^.Dist+1 );
    QueueVertex( @BFSQueue, vrstart^.Link[DIR_DOWN],  vrstart^.Dist+1 );
    QueueVertex( @BFSQueue, vrstart^.Link[DIR_LEFT],  vrstart^.Dist+1 );
    QueueVertex( @BFSQueue, vrstart^.Link[DIR_RIGHT], vrstart^.Dist+1 );
    vrstart := DequeueVertex( @BFSQueue );
  end;

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  Write( Output, vrexit^.Dist );
  CloseFile( Output );

  //freeing all graph vertices
  for y := 0 to len-1 do
    for x := 0 to len-1 do
      if ( Map[x,y] <> nil ) then Dispose( Map[x,y] );
end.

