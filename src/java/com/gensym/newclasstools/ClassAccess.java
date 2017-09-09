package com.gensym.newclasstools;

public final class ClassAccess extends InterfaceOrClassAccess
{
	
	 public ClassAccess(int flags) 
		 throws ClassException {
		 super(flags);
		if (((flags & ACC_PROTECTED) != 0)    ||
			((flags & ACC_PRIVATE) != 0)      ||
			((flags & ACC_VOLATILE) != 0)     ||
			((flags & ACC_TRANSIENT) != 0)    ||
			((flags & ACC_NATIVE) != 0)       ||
			((flags & ACC_INTERFACE) != 0))
			throw new ClassException("Invalid Access flags for a class");   	
	 }
}

