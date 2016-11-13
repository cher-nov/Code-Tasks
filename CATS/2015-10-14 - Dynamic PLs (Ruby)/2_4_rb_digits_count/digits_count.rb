cnt = Array.new(10){0}
File.open('input.txt', 'r').each_with_index do |x, ind|
  next if ind == 0
  cnt[x.to_i] += 1
end
File.open('output.txt', 'w').write(cnt.rotate!(1).join(' '))