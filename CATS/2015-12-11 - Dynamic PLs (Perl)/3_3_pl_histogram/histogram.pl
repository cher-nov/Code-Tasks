use strict;
use warnings;
use List::Util 'max';

sub readln {
  my $ln = <STDIN>;
  chomp($ln);
  return $ln;
}

open( STDIN, '<', 'input.txt' );
my $count = readln;
my @nums = split( /\s+/, readln );

open( STDOUT, '>', 'output.txt' );
print( '......' x $count . ".\n" );

for( my $i = max(@nums); $i >= 0; $i-- ) {
  my $line = '';
  map{ 
    if ($_ <  $i) {
      $line .= '......';
    } elsif ($_ == $i) {
      $line .= '.+---+';
    } else {
      $line .= '.|###|';
    }
  } @nums;
  print( $line . ".\n" );
}

print( '-+---+' x $count . '-' );
