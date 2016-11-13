//16.02.2015
//I WANT YOU NEVER TO BE
 
program disease;
 
uses SysUtils;
 
var
  n, j, inp, yesc, negc, unkwc : ShortInt;
  m, i, cnt : SmallInt;
  pos : array of set of Byte; //oh you
  neg, tmp, yes, unkw : set of Byte;
  workf : Text;
  yess, negs, unkws: AnsiString;
 
begin
 
  //open file
  Assign( workf, 'disease.in' );
  Reset ( workf );
 
  //reading input data
  Read( workf, n, m );
  SetLength( pos, m );
 
  for i := 1 to m do begin
    //reading list of infections
    for j := 1 to n do begin
      Read( workf, inp );
      if (inp = 1) then tmp += [j];
    end;
 
    //reading and processing analysis result
    Read( workf, inp );
    if (inp = 0) then begin
      neg += tmp;
    end else begin
      pos[cnt] := tmp;
      cnt += 1;
    end;
 
    tmp := [];
  end;

  Close( workf );

  //now we subtract negative analyzes from every positive
  for i := 0 to cnt-1 do begin
    pos[i] -= neg;
 
    //DAMN, WHY I CAN'T DETERMINE EXACT NUMBER OF ELEMENTS IN THE SET
    //BY A SIMPLE FUNCTION? so I forced to use this goddamned shit instead
    inp := 0; //let's use this currently unused var as a counter of elements below
    for j := 1 to n do
      if j in pos[i] then inp += 1;
 
    //let's make a decision about this analysis
    case inp of
      0 :  break;          //empty set - error
      1 :  yes  += pos[i]; //single element - exactly known result
      //many elements - result is undetermined
    end;
  end;
  
  //output result
  Assign ( workf, 'disease.out' );
  Rewrite( workf );
  if (inp > 0) or (cnt = 0) then begin

    //calculating set of unknown results
    unkw := [1..n] - yes - neg;
 
    //CALCULATIN' EXACT NUMBERS OF ELEMENTS AGAIN
    //OF COURSE, I ADORE THIS SHIT, HOW ELSE
    for j := 1 to n do begin
      if j in yes then begin
        yesc += 1;
        yess += ' ' + IntToStr(j);
      end else
      if j in neg then begin
        negc += 1;
        negs += ' ' + IntToStr(j);
      end else
      if j in unkw then begin
        unkwc += 1;
        unkws += ' ' + IntToStr(j);
      end;
    end;
     
    //let's write them out and just forget this nightmare then
    WriteLn( workf, negc,  negs );
    WriteLn( workf, yesc,  yess );
    Write  ( workf, unkwc, unkws );

  end else begin
    Write( workf, 'Incorrect' ); //VERY MOODILY, LET'S CRY TOGETHER
  end;
 
  Close( workf ); //but who cares?
 
end. //I KANT BILIV

