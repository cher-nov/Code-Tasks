queue = ( 1..File.open('input.txt', 'r').read().to_i() ).to_a()
while queue.length > 1
  queue.push( queue.shift() * queue.shift() )
end
if queue.length == 0
  queue.push(1)
end
File.open('output.txt', 'w').write(queue.pop())
