module FFI_Help
  require File.join(File.dirname(__FILE__),'quick_struct_object')

  def define_cast_return(func,cls)
    @return_casts ||= {}
    @return_casts[func]=cls
  end
  
  def return_casts
    @return_casts
  end
  
  def check_return(ret,func)
    if ret.is_a?(Class)
      define_cast_return(func,ret)
      ret = :pointer
    end 
  end
  
  def get(getter,ret)
    sym = "#{@prefix}_get_"
    func = (sym+getter.to_s).to_sym
    check_return(ret,func)
    attach_function func,[:pointer],ret
  end

  def set(setter,args,ret=:void)
    if args.is_a? Array
      args.insert(0,:pointer)
    else
      args = [:pointer,args]
    end
    
    sym = "#{@prefix}_set_"
    func = (sym+setter.to_s).to_sym
    
    check_return(ret,func)
    attach_function func,args,ret
  end
  
  def prefix pre
    @prefix = pre
  end
  
  def f(fun_name,args,ret=:void)
    if !args
      args = [:pointer]
    elsif args.is_a? Array
      args.insert(0,:pointer)
    else
      args = [args]
    end
    
    sym = "#{@prefix}_"
    func = (sym+fun_name.to_s).to_sym
    
    check_return(ret,func)
    attach_function func,args,ret
  end
end
