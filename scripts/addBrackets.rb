

file = open("opcodes.h", 'r')

file.each{|line|
  line.strip!
  if line == nil or line == ""
    next
  end
  lineArray = line.split ' '
  puts "[" + lineArray[1] + "]"
}
