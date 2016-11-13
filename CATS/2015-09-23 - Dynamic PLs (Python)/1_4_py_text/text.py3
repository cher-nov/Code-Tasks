maxl, *strs = open( "text.in", 'r' ).read().split()
maxl = int(maxl)
out = open( "text.out", 'w' )
ln = 0
rsl = ''

for s in strs:
    ln += len(s)
    if ln > maxl:
        if rsl != '':
            rsl = rsl[:-1] + '\n';
        ln = len(s);
    rsl += s + ' ';
    ln += 1;

out.write(rsl[:-1]);
out.close();
