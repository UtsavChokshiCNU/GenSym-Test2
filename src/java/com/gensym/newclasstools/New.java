package com.gensym.newclasstools;

import java.util.Vector;

public class New extends Expression {
	
  private ClassConstant constant;
  /** 
   *Equivalent of new ClassName();<br>
   * i.e. the default constructor is assumed.
   */
  public New(Type classType) throws ClassException {	
    this(classType, new Type[]{}, new Expression[]{});
  }

  /**
   * Create a new node, specifying arguments to the constructor and
   * their types.
   * Example use: <br>
   * <pre><code>
   * New nw = new New(makeType("com.gensym.classtools.tests.TestClass"),
   *                  new Type[]{Type.INT_TYPE, Type.STRING_TYPE},
   *                  new Expression[]{new Value(12), new Value("Fred")});
   * </code></pre>
   */
  public New(Type classType, Type[] argumentTypes, Expression[] arguments)
         throws ClassException
  {	
    constant = new ClassConstant(classType);
    // we can use a target of null, since the emitter sets the
    // operandAlreadyOnTheStack flag which makes the target get ignored.
    addJavaNode(new MethodCall("<init>", classType, argumentTypes,
			       Type.VOID_TYPE, null, arguments,
			       MTH_CALL_SPECIAL));
  }
	
  @Override
  public Type getExpressionType() {
    return constant.getMyClass();
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
	    Statement continuation)
      throws ClassException
  {
    super.emit(state,leaveOnStack,continuation);
    Vector instructions = state.instructions;  
    instructions.addElement(Instruction.makeInstruction(opc_new,constant));
    // leaving onto the stack the instance that was created
    instructions.addElement(Instruction.makeInstruction(opc_dup));
    state.pushStack(2);
    MethodCall methodCall = (MethodCall) children.elementAt(0);
    state.operandAlreadyOnTheStack = true;
    methodCall.emit(state,true,continuation);
  }
}
