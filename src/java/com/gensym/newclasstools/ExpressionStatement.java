package com.gensym.newclasstools;

import java.util.Vector;

public class ExpressionStatement extends Statement {
  private boolean noop = false;

  public ExpressionStatement (Expression exp) throws ClassException {
    if (exp instanceof OperatorCall) { 
      if (! ((OperatorCall) exp).isExpressionStatement())
	throw new ClassException("Invalid ExpressionStatement");
    }
    else if (!(exp instanceof MethodCall)
	     // & !(exp instanceof InlineMethodCall) 
	     & !(exp instanceof New) 
	     & !(exp instanceof NewArray))	
      throw new ClassException("Invalid ExpressionStatement");
    addJavaNode(exp);
  }

  public ExpressionStatement() {
    noop = true;
  }

  public boolean isNoopStatement()
  {
    return noop;
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
	    Statement continuation) 
       throws ClassException
  {
    //System.out.println("Emitting Expression " + children.elementAt(0) + " as a statement; noop is " + noop);
    if (! noop)
      ((Expression) children.elementAt(0)).emit(state,false,continuation);
  } 
}
