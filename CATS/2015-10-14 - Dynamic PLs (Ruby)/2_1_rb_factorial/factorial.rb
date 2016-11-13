out = ''
File.open('input.txt', 'r').read().to_i().downto(2) { |x| out += x.to_s() + '*' }
File.open('output.txt', 'w').write( eval( out+'1' ) )