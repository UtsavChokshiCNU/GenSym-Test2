package com.gensym.classtools;

import java.util.Vector;

public class InterfaceMethodRef extends MethodRef {
		InterfaceMethodRefConstant constant;

		public InterfaceMethodRef(String className, String methodName, String descriptorName)
			throws ClassException {
				super(className,methodName,descriptorName);
		}

		@Override

		public int getWhere() throws ClassException {
			if (constant == null) 
				throw new ClassException("Attempt to retrieve constantPool index for InterfaceMethodRef which has not yet generated a constant");
			return constant.getWhere();
		}

		@Override

		public void generateConstants(ConstantPool cp) throws ClassException {
			constant = (InterfaceMethodRefConstant)
				cp.getPool(cp.add(new InterfaceMethodRefConstant(cp,className,methodName,descriptor),
										 true));
		}

}




