
file1 = open(ARGV[0], 'r')
file2 = open(ARGV[1], 'r')

def toArray(file)
  returnArray = []
  file.each{|line|
    line.strip!
    if line == nil or line == ""
      next
    end
    returnArray << line
  }
  return returnArray
end

array1 = toArray(file1)
array2 = toArray(file2)

for i in (0..array1.length - 1)
  puts array1[i] + " " + array2[i]
end
