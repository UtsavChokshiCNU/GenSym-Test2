package com.gensym.classtools;

class InterfaceMethodRefConstant extends MethodRefConstant {

    public InterfaceMethodRefConstant(ConstantPool pool, String className, String methodName, String descriptorName)
	   throws ClassException {
		super(CONSTANT_INTERFACE_METHOD_REF);
		checkForInits(methodName);
		init2(pool,className,methodName,descriptorName);
	}

	InterfaceMethodRefConstant(ConstantPool pool,int descriptor_index, int name_and_type_index) {
		super(CONSTANT_INTERFACE_METHOD_REF);
        init1(pool,descriptor_index,name_and_type_index);
	}

	protected InterfaceMethodRefConstant() {
		super(CONSTANT_INTERFACE_METHOD_REF);
	}

	private void checkForInits(String methodName) throws ClassException {
		if (methodName.equals("(init)") || methodName.equals("(clinit)"))
			throw new ClassException("Interface Method References cannot be constructors or static initialization methods");
	}

	@Override

	public Object clone(boolean clonePool) {
		if (cloneInProgress != null)
			return cloneInProgress;
		Constant clone = new InterfaceMethodRefConstant();		
		return cloneWork(clone,clonePool);
	}
}
