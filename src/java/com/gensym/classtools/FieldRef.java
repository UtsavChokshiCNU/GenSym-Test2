package com.gensym.classtools;

import java.util.Vector;

public class FieldRef extends Atom 
{
  FieldRefConstant constant;
  private String className;
  private String fieldName;
  private String descriptor;
  private boolean staticRef = false;
  private boolean thisRef = false;
  private final boolean trace = false;
  
  /** A reference to a field. If this is emitted it will emit as an instance
   * field reference on "this".
   */
  public FieldRef(String className,String fieldName,String descriptor) 
      throws ClassException
  {
    this.className =  className;
    initA(fieldName,descriptor);
  }
  
  /** A reference to a field. This is interpreted as a static reference if staticref
   * is true.  Otherwize this is interpreted a an instance field reference on "this".
   */
  public FieldRef(String className,String fieldName,String descriptor,boolean staticref) 
      throws ClassException
  {		
    this.className =  className;
    initA(fieldName,descriptor);
    staticRef = staticref;
  }
  
  
  /** A reference to a field on an object 
   */
  public FieldRef(Expression exp, String fieldName, String descriptor) 
      throws ClassException
  {
    addJavaNode(exp);
    String classDescriptor = exp.getExpressionType().getReturnTypeString();
    className = Type.className(classDescriptor);
    initA(fieldName,descriptor);
  }
  
  private void initA(String name, String descriptor) throws ClassException {
    fieldName = name;
    this.descriptor = descriptor;
    expressionType = Type.parseType(descriptor);
  }
  
  public int getWhere() throws ClassException {
    if (constant == null) 
      throw new ClassException("Attempt to retrieve constantPool index for FieldRef which has not yet generated a constant");
    return constant.getWhere();
  }
  
  public String getFieldName() {
    return fieldName;
  }
  
  public String getDescriptor()
  {
    return descriptor;
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
  void generateConstants(ConstantPool cp) throws ClassException {
    constant = (FieldRefConstant)
      cp.getPool(cp.add(new FieldRefConstant(cp,
					     className,
					     fieldName,
					     descriptor),
			true));
  }
  
  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation) 
      throws ClassException
  {
    super.emit(state,leaveOnStack,continuation);
    Vector instructions = state.instructions;
    Expression nextElement;
    // Case where field is a reference to a field on "this "
    if ((children.isEmpty()) && (! staticRef)) {
      state.pushStack();
      Instruction ins = Instruction.makeInstruction(opc_aload_0);
      instructions.addElement(ins);	
    }
    // Case where field is a reference to a field on a specified object
    else {
      if (!children.isEmpty())
	((Expression) children.elementAt(0)).emit(state,leaveOnStack,continuation);
    }
    int index = constant.getWhere();
    Instruction ins;
    if (staticRef)
      ins = Instruction.makeInstruction(opc_getstatic,index);
    else {
      state.popStack();
      ins = Instruction.makeInstruction(opc_getfield,index);
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
    return "<FieldRef, className = " + className + ", fieldName = " + fieldName 
      + ", type = " + descriptor + ", static = " + staticRef;
  }
}
