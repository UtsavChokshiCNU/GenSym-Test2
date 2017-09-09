package com.gensym.classtools;

import java.util.Vector;
 
public class ClassRef extends Atom {
  ClassConstant constant;
  private String className;

  public ClassRef(String className) throws ClassException {
    // Have to provide full classname when providing an array name
    if (className.indexOf(SIGC_ARRAY) != -1)
      expressionType = Type.parseType(className);
    else expressionType = Type.parseType(Type.classDescriptor(className));
    this.className = className;
  }

  public String getClassName() {
    return className;
  }

  public int getWhere() throws ClassException {
    if (constant == null) 
      throw new ClassException("Attempt to retrieve constantPool index for ClassRef which has not yet generated a constant");
    return constant.getWhere();
  }

  @Override

  public boolean isConstantExpression() {
    return false;
  }

  @Override

  public void generateConstants(ConstantPool cp) throws ClassException {
    constant = (ClassConstant)
      cp.getPool(cp.add(new ClassConstant(cp,className),
			true));
  }

  @Override

  public String toString() {
    return "<ClassRef, type = " + expressionType + ">";
  }
}
