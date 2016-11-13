foo, *values = map( int, open( "input.txt", 'r' ).read().split() );
open( "output.txt", 'w').write( str( sum(values)-max(values) ) );
