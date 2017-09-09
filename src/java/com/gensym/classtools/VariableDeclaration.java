package com.gensym.classtools;

import java.util.Vector;

public class VariableDeclaration extends Statement {
  protected Type variableType;

  public VariableDeclaration(String name, String descriptor, 
			     Expression initialValue) 
       throws ClassException
  {	
    variableType  = Type.parseType(descriptor);
    addJavaNode(new OperatorCall("=",
				 new Expression[] {new Variable(name,
								descriptor),
						     initialValue}));
    this.name = name;
  }

  public VariableDeclaration(String name, String descriptor) 
       throws ClassException
  {
    variableType  = Type.parseType(descriptor);
    this.name = name;
  }

  public static VariableDeclaration generateUniqueVariableDeclaration
   (String descriptor) throws ClassException
  {
    return 
      new VariableDeclaration(Label.gensym(),
                              descriptor);
  }

  public Type getVariableType() {
    return variableType;
  }

  public Variable getVariable() throws ClassException {
    return new Variable(name,variableType.getReturnTypeString());
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
    Statement continuation) 
      throws ClassException {
    super.emit(state, leaveOnStack, continuation);
    Vector instructions = state.instructions;  
    if (!children.isEmpty()) {
      ((OperatorCall) children.elementAt(0)).emit(state, false, continuation);
    }
  }

  @Override
  public String toString() {
      return "<VariableDeclaration, name = " + name +
             ", type = " + variableType +">";
  }
}
