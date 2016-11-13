def treefact(l,r)
  if l == r 
    return l
  end

  if r-l == 1 
    return l*r
  end

  mid = ( (l+r) / 2 ).to_int()
  return treefact(l, mid) * treefact(mid+1, r)
end

x = File.open('input.txt', 'r').read().to_i()
if x == 0
  x = 1
elsif not x === (1..2)
  x = treefact(1, x)
end

File.open('output.txt', 'w').write(x)
