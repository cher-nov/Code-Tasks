f = open( "input.txt", 'r' )
dct = dict()
for n in range( int(f.readline()) ):
    lst = dict()
    for k in range( int(f.readline()) ):
        fish = f.readline()
        lst.update( {fish: lst.get(fish, 0) + 1} )
    list( map( lambda x: dct.update({x: lst[x] if (x not in dct) or (dct[x] < lst[x]) else dct[x]}), lst.keys() ) )

open( "output.txt", 'w' ).write( str( sum(dct.values()) ) )
