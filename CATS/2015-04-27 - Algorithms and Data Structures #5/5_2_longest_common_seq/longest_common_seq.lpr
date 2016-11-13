program longest_common_seq;
uses Math;

{$LONGSTRINGS ON}

var
  lengths : array of array of Word;
  str1, str2 : String;
  seq : String = '';
  len1, len2, i, j : Integer;

begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  ReadLn( Input, str1 );
  ReadLn( Input, str2 );
  CloseFile( Input );

  len1 := Length(str1);
  len2 := Length(str2);
  SetLength( lengths, len1+1, len2+1 ); // +1 for zeroed row and column

  //this calculates matrix of optimal subsequences lengths
  for i := len1 downto 0 do begin
    for j := len2 downto 0 do begin
      //never forget about pascal strings indexing from one
      if ( (str1[i+1] = #0) or (str2[j+1] = #0) ) then
        lengths[i,j] := 0
      else if ( str1[i+1] = str2[j+1] ) then
        lengths[i,j] := lengths[i+1, j+1] + 1
      else
        lengths[i,j] := Max( lengths[i+1, j], lengths[i, j+1] );
    end;
  end;

  //this restores longest subsequence from matrix
  while ( (i < len1) and (j < len2) ) do begin
  	if ( str1[i+1] = str2[j+1] ) then begin
      seq += str1[i+1];
      i += 1;
      j += 1;
    end else begin
      if ( lengths[i+1,j] >= lengths[i,j+1] ) then i += 1 else j += 1;
    end;
  end;

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  Write( Output, seq );
  CloseFile( Output );
end.

