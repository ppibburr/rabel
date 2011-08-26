require File.join(File.dirname(__FILE__),'..','lib','abel')

obj = ABEL::CommObject.new("127.0.0.1")
obj.attach

if obj.get_error == -3 # connection refused
  puts "passed"
  exit(0)
end

puts "failed"
exit(1)


