module ABEL
  class CommObject < FFI_Help::QuickStructObject
    class Type
      SLC5 = 3
      PLC5 = 1
      PLC5250 = 2
      MICRO = 4
    end  
    
    set_namespace ABEL
    set_prefix :abel_comm_object
    layout :comm1,:pointer,
    :host,:string
    
    def ok?
      get_error == 0 and self[:comm1].address != 0
    end
    
    def self.new(host)
      ptr = FFI::MemoryPointer.new :pointer
      ptr = ABEL.abel_comm_object_new(host)
      real_new(ptr)
    end
    
    def read_integers file,offset,len
      raise if file !~ /^n[0-9]+/
      
      address = "#{file}:#{offset}"
      rv = self.read address,len

      raise("Expected DataReturn of type DataReturn::Type::INTEGER") unless rv.is_integer

      ary = []      
      for i in 1..rv.get_length
        ary << rv.integer_at(i-1)
      end
      
      return ary
    end
    
    def read_integer file,offset
      read_integers(file,offset,1)[0]
    end
    
    def read_floats file,offset,len
      raise if file !~ /^f[0-9]+/
      ary = []
      for i in 1..len
        address = "#{file}:#{offset}"
        rv = self.read address,1

        raise("Expected DataReturn of type DataReturn::Type::FLOAT") unless rv.is_float
    
        for i in 0..rv.get_length-1
          ary << rv.float_at(i)
        end       
        offset = offset + 1
      end

      return ary
    end
    
    def read_float file,offset
      read_floats(file,offset,1)[0]
    end    
  end
end
