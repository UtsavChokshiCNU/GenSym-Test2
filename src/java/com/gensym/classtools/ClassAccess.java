package com.gensym.classtools;

public final class ClassAccess extends InterfaceOrClassAccess
{
	
	 public ClassAccess(int flags) 
		 throws ClassException {
		 super(flags);
		 
		 boolean isAccessModifier = (flags & ACC_PROTECTED) != 0 || (flags & ACC_PRIVATE) != 0;
		 boolean isFieldModifier = (flags & ACC_VOLATILE) != 0 || (flags & ACC_TRANSIENT) != 0;
		 
		if (isAccessModifier || isFieldModifier
				|| (flags & ACC_INTERFACE) == 0 || (flags & ACC_NATIVE) != 0) {
			throw new ClassException("Invalid Access flags for a class");   
		}
	 }
}

