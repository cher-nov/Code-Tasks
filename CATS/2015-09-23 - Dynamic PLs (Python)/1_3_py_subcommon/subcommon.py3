cnt = dict()

with open( "input.txt", 'r' ) as f:
    inp = f.readline()
    k = int( f.readline() )

for i in range( len(inp)-k ):
    sub = inp[i:i+k]
    cnt.update( {sub: cnt.setdefault(sub, 0) + 1} )

open( "output.txt", 'w' ).write( max( sorted(cnt), key=cnt.get) )
