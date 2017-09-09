package com.gensym.classtools;

public final class InterfaceAccess extends InterfaceOrClassAccess
{

  public InterfaceAccess(int flags) 
       throws ClassException
  {
    super(flags);
    boolean isFieldModifier = (flags & ACC_PROTECTED) != 0  ||
    							(flags & ACC_PRIVATE) != 0 ||
    							(flags & ACC_VOLATILE) != 0||
    							(flags & ACC_TRANSIENT) != 0;
    
    
    if (isFieldModifier || (flags & ACC_FINAL) != 0 ||
			(flags & ACC_INTERFACE) == 0 || (flags & ACC_NATIVE) != 0) {
      System.out.println("Failure to create interface access");
      throw new ClassException("Invalid Access flags for an interface");   
      
    }
  }
}

