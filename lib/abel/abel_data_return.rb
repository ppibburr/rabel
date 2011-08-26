module ABEL
  class DataReturn < FFI_Help::QuickStructObject
    class Type
      INTEGER = 0
      FLOAT = 1
    end
    
    set_namespace ABEL
    set_prefix :abel_data_return
    layout :type,:pointer,:len,:int,:num,:pointer,:flt,:pointer
  end
  
  def self.new *o
    real_new *o
  end
end
