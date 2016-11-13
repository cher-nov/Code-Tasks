//19.02.2015 (d.m.y)

program schools;

uses SysUtils;

type
  schnum = record
    num: LongWord;
    cnt: SmallInt;
  end;

var
  n, m, i, j: Integer;
  curn: LongWord; //good enough for school number, lol
  inp, rsl: AnsiString;
  outv: array of schnum;
  workf: Text;

begin

  //open file and read it
  assign( workf, 'schools.in' );
  reset ( workf );

  readln( workf, n );
  setlength( outv, n );

  for i := 1 to n do begin
    readln( workf, inp );

    //extracting school number from its name
    rsl := '';
    for j := 1 to Length(inp) do begin
      if inp[j] in ['0'..'9'] then rsl += inp[j]
       else if not (rsl = '') then break;
    end;
    curn := StrToInt(rsl);

    //checking school number and adding it to the list if unknown
    for j := 0 to m do begin
      if (j = m) then begin
        //if we haven't found it, we add it
        outv[j].num := curn;
        outv[j].cnt := 1;
        m += 1;
      end else if ( outv[j].num = curn ) then begin
        //otherwise we just increment the counter
        if ( outv[j].cnt = 5 ) then m -= 1;
        outv[j].cnt += 1;
        break;
      end;
    end;

  end;

  close(workf);

  //let's output result
  assign ( workf, 'schools.out' );
  rewrite( workf );

  writeln( workf, m );
  for i := 0 to n-1 do begin
    if outv[i].cnt in [1..5] then writeln( workf, outv[i].num );
  end;

  close(workf);

end.

