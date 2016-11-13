n = File.open('input.txt', 'r').read().to_i();
out = File.open('output.txt', 'w')
for i in 1..n
  for j in 1..n
    for k in 1..n
      out.write(((i+j+k).modulo(n)+1).to_s+' ')
    end
    out.write("\n");
  end
end