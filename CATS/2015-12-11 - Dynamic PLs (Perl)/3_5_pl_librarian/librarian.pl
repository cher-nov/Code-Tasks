use strict;
use warnings;

sub readln {
  my $ln = <STDIN>;
  chomp($ln);
  return $ln;
}

open( STDIN, '<', 'input.txt' );

my %themes;
for( my $num_subj = <STDIN>; $num_subj > 0; $num_subj-- ) {
  my $subject = readln;
  for( my $num_book = <STDIN>; $num_book > 0; $num_book-- ) {
    my $book = readln;
    for( my $num_themes = <STDIN>; $num_themes > 0; $num_themes-- ) {
      my $theme = readln;
      $themes{$theme}[0] = $subject;
      push( @{$themes{$theme}[1]}, $book );
    }
  }
}

open( STDOUT, '>', 'output.txt' );
for( my $num_need = <STDIN>; $num_need > 0; $num_need-- ) {
  my $theme = readln;
  print(
    "Topic: " . $theme ."\n".
    "Subject: " . $themes{$theme}[0] ."\n".
    "Books:\n" . join( "\n", @{$themes{$theme}[1]} ) . "\n"
  );
}
