n = File.open('input.txt', 'r').read().to_i()
out = 1
(n-3).step(1, -4) { |x| out *= x*(x+1)*(x+2)*(x+3) }
File.open('output.txt', 'w').write( out * 2.step(n.modulo(4), 1).inject(1, :*) )