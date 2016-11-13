program substr_kmp;

{$LONGSTRINGS ON}

{ this is Knuth-Morris-Pratt algorithm, slightly optimized for
  searching only first occurrence of substring and for using
  O(T+1) of memory instead of O(T+S), where T is for text
  length, and S is same, but for substring
  30.05.2015 }

function PosKMP( str, text: String ): SizeInt;
var
  lenstr, lentext, i, k : SizeInt;
  procstr : String;
  prefixf : array of SizeInt;
begin
  Result := -1;
  lenstr := Length( str );
  lentext := Length( text );
  if ( lenstr > lentext ) then Exit( Result );

  procstr := str + #12 + text; // #12 - FORM FEED control char
  SetLength( prefixf, 1+lentext ); //one position is for separator
  prefixf[0] := 0;

  for i := 1 to lentext do begin
    k := prefixf[i-1];
    while (k > 0) and ( procstr[k+1] <> procstr[lenstr+1+i] ) do begin
      k := prefixf[k-1];
    end;
    if ( procstr[k+1] = procstr[lenstr+1+i] ) then begin
      k += 1;
      if ( k = lenstr ) then Exit(i-lenstr+1); { //
        substring is found, +1 is for one-based index }
    end; 
    prefixf[i] := k;
  end;
end;

var
  haystack, needle : String;
begin
  AssignFile( Input, 'input.txt' );
  Reset( Input );
  ReadLn( Input, haystack );
  ReadLn( Input, needle );
  CloseFile( Input );

  AssignFile( Output, 'output.txt' );
  Rewrite( Output );
  Write( Output, PosKMP( needle, haystack ) );
  CloseFile( Output );
end.

