package com.gensym.newclasstools;

import java.util.Vector;

public class FieldRef extends Atom 
{
  FieldRefConstant constant;
  private boolean staticRef = false;
  private boolean thisRef = false;
  private final boolean trace = false;
  
  /** A reference to a field. This is interpreted as a static reference if staticref
   * is true.  Otherwise this is interpreted a an instance field reference on "this".
   */
  public FieldRef(Type classType, String fieldName, Type fieldType, boolean staticRef) 
      throws ClassException
  {
    this.staticRef = staticRef;
    expressionType = fieldType;
    constant = new FieldRefConstant(classType, fieldName, fieldType);
  }
  
  /** A reference to a field. If this is emitted it will emit as an instance
   * field reference on "this".
   */
  public FieldRef(Type classType, String fieldName, Type fieldType) 
      throws ClassException
  {		
    this(classType, fieldName, fieldType, false);
  }
  
  /** A reference to a field on an object, given by exp.
   *  Class containing the object is given by classType.
   */
  public FieldRef(Expression exp, Type classType, String fieldName, Type fieldType) 
      throws ClassException
  {
    addJavaNode(exp);
    constant = new FieldRefConstant(classType, fieldName, fieldType);
    expressionType = fieldType;
  }
  
  public String getFieldName() {
    return constant.getName();
  }
  
  public Type getFieldType()
  {
    return constant.getFieldType();
  }

  /** Returns the type of the class in which the field is defined.
   *
   */
  public Type getFieldClass() {
    return constant.getMyClass();
  }

  public boolean isStaticRef() {
    return  staticRef;
  }
  
  @Override
  public boolean isConstantExpression() {
    // Should be conditional on whether the field is final or not. 
    return false;	
  }
  
  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation) 
      throws ClassException
  {
    super.emit(state,leaveOnStack,continuation);
    Vector instructions = state.instructions;
    Expression nextElement;
    // Case where field is a reference to a field on "this "
    if ((children.size() == 0) && (! staticRef)) {
      state.pushStack();
      Instruction ins = Instruction.makeInstruction(opc_aload_0);
      instructions.addElement(ins);	
    }
    // Case where field is a reference to a field on a specified object
    else {
      if (children.size() > 0)
	((Expression) children.elementAt(0)).emit(state,leaveOnStack,continuation);
    }
    Instruction ins;
    if (staticRef)
      ins = Instruction.makeInstruction(opc_getstatic, constant);
    else {
      state.popStack();
      ins = Instruction.makeInstruction(opc_getfield, constant);
    }
    Type tpe = expressionType;
    if((tpe.isDoubleType() || tpe.isLongType()))  {
      state.pushStack(2);		
    }
    else state.pushStack();
    if (trace)	
      System.out.println("Instruction for field get" + ins);
    instructions.addElement(ins);
  }
  
  @Override
  public String toString() {
    return "<FieldRef, className = " + getFieldClass() + ", fieldName = " + getFieldName() 
      + ", type = " + getFieldType() + ", static = " + staticRef;
  }
}
