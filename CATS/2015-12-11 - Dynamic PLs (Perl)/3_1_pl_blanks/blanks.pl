use strict;
use warnings;

sub readln {
  my $ln = <STDIN>;
  chomp($ln);
  return $ln;
}

sub min {
  ( $_[0] < $_[1] )
  ? $_[0] : $_[1];
}

open( STDIN, '<', 'input.txt' );
my $blank = readln;
my @names = split( ' ', readln );

my %data;
for ( my $i = <STDIN>; $i > 0; $i-- ) {
  my $key = readln;
  $data{$key} = readln;
}

my $out = $blank;
for my $name (@names) {
  $blank =~ m/(_+)/g;
  my $val = $data{$name};
  my $len = min( length($1)-2, length($val) );
  substr($out, $-[0]+1, $len) = substr($val, 0, $len);
}

open( STDOUT, '>', 'output.txt' );
print($out);


