package com.gensym.classtools;

import java.util.Vector;

public class New extends Expression {
	
  /** 
   *Equivalent of new ClassName();<br>
   * i.e. the default constructor is assumed.
   */
  public New(String className) throws ClassException {	
    ClassRef classRef = new ClassRef(className);
    // Check to see if <init> ()V is defined for this class
    MethodRef methodRef =  new MethodRef(className,"<init>","()V");
    MethodCall methodCall = new MethodCall(methodRef,MTH_CALL_SPECIAL);
    addJavaNode(classRef);
    addJavaNode(methodCall);
  }

  /**
   * Create a new node from a Method Call on an <init> method.<br>
   * Example use: <br>
   * <pre><code>
   * MethodRef methodRef = new MethodRef("Lcom/gensym/classtools/New;","<init>","()V");		  
   * MethodCall methodCall = new MethodCall(methodRef,MTH_CALL_SPECIAL);
   * New nw = new New(methodCall);
   * </code></pre>
   */
  public New(MethodCall methodCall) throws ClassException {	
    // Check to see if this is indeed an <init> method
    ClassRef classRef = 
      new ClassRef(methodCall.getClassName());
    addJavaNode(classRef);
    addJavaNode(methodCall);
  }
	
  @Override
  public Type getExpressionType() {
    return ((Expression) children.elementAt(0)).getExpressionType();
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
	    Statement continuation)
      throws ClassException
  {
    super.emit(state,leaveOnStack,continuation);
    ClassRef classRef  = (ClassRef) children.elementAt(0);
    classRef.generateConstants(state.pool);
    int classWhere = classRef.getWhere();
    Vector instructions = state.instructions;  
    instructions.addElement(Instruction.makeInstruction(opc_new,classWhere));
    // leaving onto the stack the instance that was created
    instructions.addElement(Instruction.makeInstruction(opc_dup));
    state.pushStack(2);
    MethodCall methodCall = (MethodCall) children.elementAt(1);
    state.operandAlreadyOnTheStack = true;
    methodCall.emit(state,true,continuation);
    state.operandAlreadyOnTheStack = false;
  }
}
