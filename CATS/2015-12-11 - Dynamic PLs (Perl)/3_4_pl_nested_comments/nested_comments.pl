use strict;
use warnings;

open( STDIN, '<', 'input.txt' );
my $code = do{ local $/; <STDIN> };

my $braces = 0;
my $result = '';
foreach my $part ( split /(\/\*|\*\/)/s, $code, -1 ) {
  if ($part eq '/*') {
    $braces++;
  } elsif ($part eq '*/') {
    if ($braces > 0) {$braces--;} else {$result .= $part;}
  } else {
    if ($braces == 0) {$result .= $part;}
  }
}

open( STDOUT, '>', 'output.txt' );
print($result);
