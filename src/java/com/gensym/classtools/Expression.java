package com.gensym.classtools;

public abstract class Expression extends JavaNode  { 
  protected Type expressionType;

  public Type getExpressionType() {
    return expressionType;
  }

  protected void setExpressionType(Type tpe) {
    expressionType = (Type) tpe.clone();
  }

  public boolean isConstantExpression() {
    boolean result = true;
    for (int i = 0; i < children.size(); i++) {
      JavaNode j = (JavaNode) children.elementAt(i);
      if (j instanceof Expression)
	result &= ((Expression) j).isConstantExpression();
    }
    return result;
  }
	
  // Default implementation of evaluating constants - recurse through the hierarchy and return
  // this
  public Expression evaluateConstantExpression() throws ClassException {
    for (int i = 0; i < children.size(); i++) {
      JavaNode j = (JavaNode) children.elementAt(i);
      if (j instanceof Expression)
	children.setElementAt(((Expression) j).evaluateConstantExpression(),i);	
    }
    return this;
  }
}
