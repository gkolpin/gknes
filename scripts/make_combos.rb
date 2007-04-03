

file = open("opcode_map.h", 'r')

array = ['I', 'Z', 'ZX', 'A', 'AX', 'AY', 'IX', 'IY']

file.each {|line|
  line.strip!

  if line == nil or line == ""
    next
  end
  
  lineArray = line.split " "
  if lineArray.length != 3
    next
  end

  splitString = lineArray[1]

  array.each{|el|
    puts("(" + splitString + ", " + el + ")")
  }
}
