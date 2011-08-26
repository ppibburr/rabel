## Description
  Ruby Library to interface with Allen Bradley SLC5/05 logic controller
  and bindings to ABEL (abplc5)  [ABEL (abplc5)] 
  
  matt mesanko (c) 2011 <tulnor@linuxwaves.com>
  
## Synopsis
  require 'abel'
  
  comm = ABEL::CommObject.new('192.1.168.20')
  
  comm.attach
  
  if comm.ok?
  
    comm.read_integer("n7",0) #=> 1979 (or whatever)
  
  end 
  
## Features
  Read/Write data to SLC5/05 proccessors
  Implement Human Machine Interfaces
  Data Logging
  
## License
  the mit license
  
[ABEL (abplc5]: http://sourceforge.net/projects/abplc5/
