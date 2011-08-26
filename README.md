## Description
  Ruby Library to interface with Allen Bradley SLC5/05 logic controller
  and bindings to ABEL (abplc5)  [ABEL (abplc5)](http://sourceforge.net/projects/abplc5/) 
  
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
  
## Install
    libabplc5.so needs installed globaly
    abplc5 ships with the lib
    
    `cd abplc5`
    `sudo make`
    `make clean`
    `cd ..`

    `rake build`   Builds the lib
    `rake install` Installs the gem (rubygems needed)
    
    `rake test`    should pass
  
## License
  the mit license
  

