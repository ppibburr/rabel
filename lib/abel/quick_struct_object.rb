module FFI_Help
  class QuickStructObject < FFI::Struct
    class << self
      alias :real_new :new
    end

    def self.set_prefix pre
      @prefix = pre
    end
      
    def self.set_namespace mod
      @namespace = mod
    end
    
    def self.namespace
      @namespace
    end
      
    def self.prefix
      @prefix
    end

    def method_missing s,*o
      if members.index s
         return self[s]
      else
        ns = self.class.namespace
        fun = "#{self.class.prefix}_#{s}"
        
        if ns.methods.index(fun)
          ptr = ns.send fun,self,*o
          if c=ns.return_casts[fun.to_sym]
            return c.new(ptr)
          end
                
          return ptr
        end
      end
      super
    rescue
      super
    end
  end
end
