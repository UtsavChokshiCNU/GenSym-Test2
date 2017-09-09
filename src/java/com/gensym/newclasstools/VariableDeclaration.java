package com.gensym.newclasstools;

import java.util.Vector;

public class VariableDeclaration extends Statement {
  protected Type variableType;
  private Expression initialValue;
  protected String name;

  public String getName() {
    return name;
  }

  public VariableDeclaration(String name, Type type, 
			     Expression initialValue) 
       throws ClassException
  {	
    variableType = type;
    if (initialValue != null) {
      addJavaNode(new OperatorCall("=",
				   new Expression[] {new Variable(name,
								  type),
						       initialValue}));

    }
    this.name = name;
  }

  public VariableDeclaration(String name, Type descriptor) 
       throws ClassException
  {
    this(name, descriptor, null);
  }

  public static VariableDeclaration generateUniqueVariableDeclaration
   (Type type) throws ClassException
  {
    return 
      new VariableDeclaration(Label.gensym(),
                              type);
  }

  public Type getVariableType() {
    return variableType;
  }

  public Variable getVariable() throws ClassException {
    return new Variable(name, variableType);
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
    Statement continuation) 
      throws ClassException {
    super.emit(state, leaveOnStack, continuation);
    Vector instructions = state.instructions;  
    if (children.size() > 0) {
      ((OperatorCall) children.elementAt(0)).emit(state, false, continuation);
    }
  }

  @Override
  public String toString() {
      return "<VariableDeclaration, name = " + name +
             ", type = " + variableType +">";
  }
}
