=begin 
/* Wrap allen bradley ethernet library (abel)
 * as a 'object' that can attach to and read data from a SLC5/05 logic controller
 * in a manner that provides OOP idioms suited to wrap with foriegn function interface (FFI)
 * targeting the language Ruby.
 * 
 * Matt Mesanko 07282011, tulnor@linuxwaves.com
 */
=end

require 'rubygems'
require 'ffi'
require File.join(File.dirname(__FILE__),'abel','ffi_help')

module ABEL
  require File.join(File.dirname(__FILE__),'abel','abel_comm_object')
  require File.join(File.dirname(__FILE__),'abel','abel_data_return')
  
  extend FFI_Help

  extend FFI::Library
  ffi_lib File.join(File.dirname(__FILE__),'abel','ABELCommObject.so')
  prefix :abel_comm_object
  
  get(:error,:short)
  get(:host,:string)
  get(:tns,:short)
  get(:commid,:long)
  get(:mode,:char)
  get(:device_type,:int)
  
  f(:new,:string,:pointer)
  f(:attach,nil)
  f(:close,nil)
  f(:read,[:string,:int],ABEL::DataReturn)
  
  prefix :abel_data_return
  f(:integer_at,[:int],:int)
  f(:float_at,[:int],:float)
  f(:new,nil,:pointer)  
  f(:is_float,nil,:bool)
  f(:is_integer,nil,:bool)
  
  get(:length,:int)
  get(:type,:int)
end
 
