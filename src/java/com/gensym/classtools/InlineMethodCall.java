package com.gensym.classtools;

import java.util.Vector;

class InlineMethodCall extends Call 
implements RuntimeConstants
{

  private MethodInfo contents;
  private CodeAttribute cachedCode;
  private Type expressionType;
  private int startVarID;
 
  /**
   * the constructor for MethodCall allows the user to
   * create a JavaNode that will inline the contents of 
   * an already compiled method.  Note that argument
   * types need to be consistent.
   */
  public InlineMethodCall(MethodInfo methodInfo,
                          Expression[] arguments)
       throws ClassException
  {
    expressionType = Type.parseType(methodInfo.getDescriptor());
    Type[] argumentSpec = expressionType.getArgumentTypes();
    
    if (((arguments != null) && (arguments.length != 0)) ||
        (argumentSpec.length != 0) ||
        (! methodInfo.getAccess().isStatic())
	 )
      throw new ClassException("InlineMethodCall currently only supports inlining of static zero argument methods");

    if (! methodInfo.normalized)
      {
	methodInfo.toStdout(" ");
        throw new ClassException("Method required to be normalized for InlineMethodCall");
      }   
    contents = methodInfo;
    cachedCode = contents.getCodeAttribute();
  }

  @Override
  public Type getExpressionType() {
    return expressionType;
  }

  @Override
  public void generateConstants(ConstantPool pool) throws ClassException 
  {
    ConstantPool normals = (ConstantPool) contents.normalizedConstants;   
    pool.add(normals);
    contents.localize(pool);
  }

  @Override
  public boolean isConstantExpression() {
    return false;
  }

  @Override
  void generateVariableIds(EmitState state) 
       throws ClassException
  {
    startVarID = state.varID;

    // Theoretically could be smaller if
    // the use of 0 to represent this is identified
    state.varID = startVarID + cachedCode.getMaxLocals();
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation) 
       throws ClassException
  {
    int size, i;
    Instruction ins;

    // Super call to deal with Constants, variableIDs and
    // line numbers
    super.emit(state, leaveOnStack, continuation);
      
    // here it would be good to clone the instructions and the
    // exception table entries

    Vector instructs = cachedCode.getRawInstructions();
    Vector exceptionTable = cachedCode.getRawExceptionTable();

    // Create a separate emitState - just for the purpose of
    // adding labels to the instructions

    EmitState newState = 
      new EmitState(state.pool,
		    instructs,
		    exceptionTable,
		    null);
 
    newState.jumpId = state.jumpId;
    newState.tryId = state.tryId;

    // Add all labels for this code

    newState.addAllLabels(true, true);


    // Change all local variable references to be 
    // from startVarId


    // Add the instructions created by this process to the
    // existing state, including updating the jumpId and
    // tryId's

    size = instructs.size();
    Vector instructions = state.instructions;
    for (i = 0; i < size; i++)
      {
        ins = (Instruction) instructs.elementAt(i);
        instructions.addElement(ins);
      }
    state.tryId = newState.tryId;
    state.jumpId = newState.jumpId;

    int stack = cachedCode.getMaxStack();
    state.pushStack(stack);
    state.popStack(stack);
  }

  @Override
  public String toString() {
    return "<InlineMethodCall, class = " + contents.getClassName() + ", method = " + name 
      +  ", descriptor = " + getExpressionType() + ">";
  }
}
