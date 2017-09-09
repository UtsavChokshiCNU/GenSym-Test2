package com.gensym.newclasstools;

import java.util.Vector;

/**
 *  ClassRef is only used as one of the arguments to the instanceof operator
 *  call.
 */
public class ClassRef extends Atom {
  ClassConstant constant;
  private Type classType;

  public ClassRef(Type classType) throws ClassException {
    // Have to provide full classname when providing an array name
    this.classType = classType;
  }

  public String getClassName() {
    return classType.getClassName();
  }

  @Override
  public boolean isConstantExpression() {
    return false;
  }

  @Override
  public String toString() {
    return "<ClassRef, type = " + expressionType + ">";
  }
}
